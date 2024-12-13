#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdalign.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <unistd.h>
#include <immintrin.h>    // For SSE2 intrinsics
#include <sys/mman.h>
#include <errno.h>

// Attempt a C23 feature (if supported):
#if __STDC_VERSION__ >= 202300L
typedef _BitInt(64) bigint_t; // Just to show off usage, not really needed.
#else
typedef unsigned long long bigint_t;
#endif

// A trivial XOR key for "Hello, World!\n"
static const unsigned char xor_key = 0xAA;

// We'll store our encoded string in a custom section (implementation-defined).
// On ELF systems, we can create a custom section named ".rodata.hello"
__attribute__((section(".rodata.hello"), aligned(16)))
static const unsigned char encoded_string[] = {
    // "Hello, World!\n" XORed with 0xAA
    // 'H' = 0x48, 0x48 ^ 0xAA = 0xE2
    // 'e' = 0x65, 0x65 ^ 0xAA = 0xCF
    // 'l' = 0x6C, 0x6C ^ 0xAA = 0xC6
    // 'l' = 0x6C, 0x6C ^ 0xAA = 0xC6
    // 'o' = 0x6F, 0x6F ^ 0xAA = 0xC5
    // ',' = 0x2C, 0x2C ^ 0xAA = 0x86
    // ' ' = 0x20, 0x20 ^ 0xAA = 0x8A
    // 'W' = 0x57, 0x57 ^ 0xAA = 0xFD
    // 'o' = 0x6F, 0x6F ^ 0xAA = 0xC5
    // 'r' = 0x72, 0x72 ^ 0xAA = 0xD8
    // 'l' = 0x6C, 0x6C ^ 0xAA = 0xC6
    // 'd' = 0x64, 0x64 ^ 0xAA = 0xCE
    // '!' = 0x21, 0x21 ^ 0xAA = 0x8B
    // '\n'= 0x0A, 0x0A ^ 0xAA = 0xA0
    0xE2, 0xCF, 0xC6, 0xC6, 0xC5, 0x86, 0x8A, 0xFD,
    0xC5, 0xD8, 0xC6, 0xCE, 0x8B, 0xA0, 0x00
};

// We'll store the decoded string in a thread-local buffer just for fun.
_Thread_local char decoded_buffer[sizeof(encoded_string)] = {0};

// Use an atomic flag to ensure we only decode once.
static _Atomic int decoded_flag = ATOMIC_VAR_INIT(0);

// A function that decodes the string using SSE2 or fallback:
static void decode_string(void) {
    // We can try a vectorized XOR using SSE2 if available.
    // We'll assume the length is small enough to do this trivially.
    // Length: 14 + 1 = 15 bytes total, zero-terminated.
    const __m128i key_vector = _mm_set1_epi8((char)xor_key);
    __m128i data = _mm_load_si128((const __m128i *)encoded_string);
    data = _mm_xor_si128(data, key_vector);
    _mm_store_si128((__m128i *)decoded_buffer, data);

    // Ensure null termination even if SSE wrote beyond intended termination.
    decoded_buffer[sizeof(encoded_string)-1] = '\0';
}

// We can also demonstrate inline assembly for no real reason:
__attribute__((noinline))
static void force_memory_fence(void) {
#if defined(__x86_64__)
    __asm__ __volatile__("mfence" ::: "memory");
#else
    atomic_thread_fence(memory_order_seq_cst);
#endif
}

// A constructor that decodes our string at startup.
__attribute__((constructor))
static void init_hello(void) {
    // Set the atomic flag if not set, decode on first init.
    int expected = 0;
    if (atomic_compare_exchange_strong(&decoded_flag, &expected, 1)) {
        decode_string();
        force_memory_fence();
    }
}

// For added complexity, define a structure with a flexible array member
// (just to store "Hello, World!\n" at runtime, even though we already have it).
typedef struct {
    size_t length;
    char data[];
} dynamic_string;

// Allocate a dynamic_string on the heap:
static dynamic_string *build_dynamic_copy(const char *restrict str) {
    size_t len = strlen(str);
    dynamic_string *ds = malloc(sizeof(*ds) + len + 1);
    if (!ds) {
        perror("malloc");
        return NULL;
    }
    ds->length = len;
    memcpy(ds->data, str, len+1);
    return ds;
}

// Just another useless function pointer to show calling via a function pointer:
typedef void (*print_fn_t)(const char *);

// We'll have a function that prints using write() instead of printf:
static void raw_print(const char *str) {
    size_t len = strlen(str);
    ssize_t w = write(STDOUT_FILENO, str, len);
    (void)w; // ignore errors for brevity
}

// Another function that prints using standard I/O:
static void stdio_print(const char *str) {
    fputs(str, stdout);
}

// We'll pick a printer based on something arbitrary (like environment variable).
static print_fn_t select_printer(void) {
    const char *env = getenv("HELLO_STYLE");
    if (env && strcmp(env, "raw") == 0) {
        return raw_print;
    }
    return stdio_print;
}

// To show off VLAs, let's make a pointless transformation:
static void to_uppercase_vla(const char *in, char *out) {
    size_t len = strlen(in);
    // VLA for demonstration:
    char tmp[len+1];
    for (size_t i = 0; i < len; i++) {
        char c = in[i];
        if (c >= 'a' && c <= 'z') {
            c = (char)(c - 'a' + 'A');
        }
        tmp[i] = c;
    }
    tmp[len] = '\0';
    memcpy(out, tmp, len+1);
}

// This destructor just prints a message to stderr to show it exists:
__attribute__((destructor))
static void cleanup_hello(void) {
    fprintf(stderr, "[DEBUG] Cleanup complete.\n");
}

int main(void) {
    force_memory_fence(); // Overkill memory fence.
    // At this point, decoded_buffer should hold the decoded "Hello, World!\n"
    print_fn_t printer = select_printer();

    // Construct a dynamic copy just to waste resources:
    dynamic_string *ds = build_dynamic_copy(decoded_buffer);
    if (!ds) {
        return EXIT_FAILURE;
    }

    // Make a pointless uppercase version:
    // We'll allocate another dynamic_string for uppercase form:
    dynamic_string *upper = malloc(sizeof(*upper) + ds->length + 1);
    if (!upper) {
        free(ds);
        return EXIT_FAILURE;
    }
    upper->length = ds->length;
    to_uppercase_vla(ds->data, upper->data);

    // Just print the original version:
    printer(ds->data);

    // And then print the uppercase version to show we can do more:
    printer(upper->data);
    printer("\n");

    free(upper);
    free(ds);

    return EXIT_SUCCESS;
}
