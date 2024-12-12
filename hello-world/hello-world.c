#include <stdio.h>
#include <stddef.h>

/*
 * We define our message as a macro. We'll XOR each character with a key
 * at compile time to create a static encoded array. At runtime, we'll decode
 * the array before printing. This is purely a demonstration of cleverness.
 */

#define MESSAGE          "Hello, world!\n"
#define KEY              0x5A /* Arbitrary XOR key */
#define LEN(str)         (sizeof(str) - 1U)

/*
 * Create an encoded version of MESSAGE at compile time:
 * We rely on compound literals and a for-like construct using macros.
 */

#define ENCODED_MESSAGE_ARRAY \
    { ENCODE_CHAR(0), ENCODE_CHAR(1), ENCODE_CHAR(2), ENCODE_CHAR(3), \
      ENCODE_CHAR(4), ENCODE_CHAR(5), ENCODE_CHAR(6), ENCODE_CHAR(7), \
      ENCODE_CHAR(8), ENCODE_CHAR(9), ENCODE_CHAR(10),ENCODE_CHAR(11),\
      ENCODE_CHAR(12),ENCODE_CHAR(13) }

/* We know MESSAGE is "Hello, world!\n" which is 14 chars including '\n' */
_Static_assert(LEN(MESSAGE) == 14, "Message length must match macros below.");

/* Helper macro: XOR a single character at compile time */
#define ENCODE_CHAR(i) ((unsigned char)((MESSAGE[i]) ^ KEY))

static unsigned char encoded_msg[LEN(MESSAGE)] = ENCODED_MESSAGE_ARRAY;

static void decode_and_print(void)
{
    /* Decode in place */
    for (size_t i = 0; i < LEN(MESSAGE); i++) {
        encoded_msg[i] ^= KEY;
    }

    /* Now encoded_msg is the original string */
    /* Use puts for simplicity; it appends a newline, but we already have one. */
    /* To avoid double newline, we can use fputs instead. */
    fputs((const char *)encoded_msg, stdout);
}

int main(void)
{
    decode_and_print();
    return 0;
}
