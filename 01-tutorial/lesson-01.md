# Lesson 1: Introduction to C and Setting Up Your Environment

**Objectives:**

- Understand what C is and why it’s used for systems programming.
- Set up a development environment for compiling and running C code.
- Write, compile, and run your first C program.

---

## 1. What is C?

C is a low-level, general-purpose programming language that dates back to the early 1970s. Despite its age, it remains one of the most widely used languages in systems programming and embedded systems. Here’s why:

- **Close to the Metal**: C allows you to work directly with memory and hardware resources. This gives you fine-grained control over performance and resource usage—critical in systems-level code such as operating systems, drivers, and embedded firmware.
- **Portability**: Properly written C code can be compiled on a wide range of hardware and operating systems without significant changes.
- **Influence on Other Languages**: Many popular languages (like C++, Objective-C, Rust, Go) build upon concepts introduced or popularized by C. Learning C provides a deep foundation that will improve your understanding of how computers and other languages work under the hood.

By learning C, you’ll not only gain the ability to write powerful, efficient programs but also develop a much deeper understanding of how software interacts with hardware.

---

## 2. Setting Up Your Environment

To get started, you need a C compiler and a code editor. Most commonly, you’ll use GCC or Clang. Both are free and widely available. On Linux or macOS, you may already have a compiler installed or can easily install one. On Windows, you can use something like **MinGW-w64** or **WSL** (Windows Subsystem for Linux).

**Recommended Setups:**

- **Linux (Ubuntu/Debian):**

    ```bash
    sudo apt-get update
    sudo apt-get install build-essential
    ```

    This installs GCC and Make, providing a straightforward environment out of the box.

- **macOS:**
    Install Apple’s command-line tools. In the Terminal:

    ```bash
    xcode-select --install
    ```

    This gives you `clang` by default.

- **Windows:**

  - **Option 1: MinGW-w64**: Download from [https://www.mingw-w64.org/](https://www.mingw-w64.org/) and add it to your PATH.
  - **Option 2: Windows Subsystem for Linux (WSL)**: Install a Linux distro from the Microsoft Store, then use the same commands as Linux.

**Editors and IDEs:**

- You can start with a text editor like **Visual Studio Code** or **Sublime Text**.
- If you prefer an IDE, consider **CLion** (commercial) or **Code::Blocks** (free).

**Verifying Your Compiler Installation:** Open a terminal or command prompt and type:

```bash
gcc --version
```

or

```bash
clang --version
```

You should see version information. If not, re-check your installation steps.

---

## 3. Understanding the Structure of a C Program

A minimal C program looks like this:

```c
#include <stdio.h>

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
```

**Key Points:**

- `#include <stdio.h>`: A **preprocessor directive** that includes the standard input/output library header, which lets you use `printf`.
- `int main(void)`: The starting point of every C program. `main()` returns an integer status code to the operating system, with `0` typically meaning success.
- `printf("Hello, World!\n");`: Prints text to the standard output (usually your terminal).
- `return 0;`: Indicates the program ended successfully.

---

## 4. Compiling and Running Your First C Program

1. **Create a Source File**:
    Use your chosen editor to create a file named `hello.c`, and paste in the code from above.

2. **Compile the Code**:
    Open a terminal in the directory containing `hello.c` and run:

    ```bash
    gcc -o hello hello.c
    ```

    - `gcc` is the compiler.
    - `-o hello` specifies the name of the output file (the executable).
    - `hello.c` is your source code file.

    If successful, this will produce an executable file named `hello` (on Windows, `hello.exe`).

3. **Run the Program**:

    ```bash
    ./hello
    ```

    You should see:

    ```bash
    Hello, World!
    ```

**Troubleshooting**:

- If you get a “command not found” error, ensure GCC or Clang is installed and on your PATH.
- If compilation fails, check for typos in your code.

---

## 5. Common Errors and How to Solve Them

- **Missing Semicolons**: Each statement in C must end with a semicolon.
- **Mismatched Braces**: Ensure every `{` has a corresponding `}`.
- **Case Sensitivity**: C is case-sensitive. `main` and `Main` are not the same function name.

When errors occur, GCC will give you a line number and a message. Don’t get frustrated—carefully read the error messages and fix the issues.

---

## 6. Practice and Homework

**Suggested Tasks:**

1. Experiment with `printf`: try printing different messages, numbers, and newline characters (`\n`).
2. Compile and run the program multiple times to get comfortable with the edit-compile-run cycle.
3. Explore basic data types: try declaring an `int` and printing it out with `printf("%d", myInt);`.

**Stretch Exercise:**

- Write a program that prints your name and a brief message. For example:

    ```c
    #include <stdio.h>

    int main(void) {
        printf("My name is Alice, and I’m learning C!\n");
        return 0;
    }
    ```

Compile and run this. Experiment by changing the message and observe how the output changes.

---

## 7. What’s Next?

You’ve successfully compiled and run your first C program! Understanding how to set up your environment and work through the basic edit-compile-run cycle lays the groundwork for all future lessons.

**In the next lessons**, we’ll dive deeper into data types, variables, and control structures. We’ll also learn about C’s standard libraries and how to read input from the user.

---

### End of Lesson 1

Great job getting started! Proceed to Lesson 2 once you feel confident with these basics.
