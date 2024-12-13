# Lesson 2: Variables, Data Types, and Basic Input/Output

**Objectives:**

- Understand C’s primitive data types and variable declarations.
- Learn how to use format specifiers with `printf` and `scanf`.
- Understand the difference between Python’s dynamic typing and C’s static typing.
- Practice reading user input and printing formatted output.

---

## 1. Recap from Lesson 1

In the first lesson, you learned how to write, compile, and run a simple C program that printed “Hello, World!”. Now, we’ll expand on this by working with variables and user input.

---

## 2. Variables and Static Typing

In Python, variables can hold any type of data without explicit declarations. In C, you must explicitly declare each variable with a specific type before using it. This is called **static typing**. Once a variable is declared with a certain type, it can only hold values of that type (unless you use casting, which we’ll discuss later).

### Common Primitive Data Types in C

- **int**: Used for integers (e.g., `42`, `-5`).
- **float** and **double**: Used for floating-point numbers (e.g., `3.14`, `-2.71828`).
- **char**: Holds a single character (e.g., `'A'`, `'z'`). Internally, `char` is just a small integer type representing a character’s code.

**Example Declarations:**

```c
int age = 25;        // An integer variable
double pi = 3.14159; // A double-precision floating-point variable
char grade = 'A';    // A character variable
```

You can declare multiple variables of the same type in a single statement:

```c
int x = 0, y = 10, z = -5;
```

**Important:** Variables must be declared before use. C does not allow you to assign a new variable on the fly as Python does.

---

## 3. Printing Variables with `printf`

In Lesson 1, you learned `printf("Hello, World!\n");`. For printing variables, we use **format specifiers** that tell `printf` how to interpret and display each variable’s value.

**Common Format Specifiers:**

- `%d` or `%i`: Print an integer.
- `%f`: Print a floating-point number.
- `%c`: Print a single character.
- `%s`: Print a string (we’ll cover strings in detail in a future lesson).

**Examples:**

```c
int count = 5;
double price = 19.99;
char initial = 'J';

printf("Count: %d\n", count);
printf("Price: %f\n", price);
printf("Initial: %c\n", initial);
```

By default, `%f` prints many decimal places for floating-point values. You can format it to a certain number of decimals, for example `%.2f` prints two decimal places:

```c
printf("Price: %.2f\n", price); // Prints: Price: 19.99
```

---

## 4. Reading User Input with `scanf`

Unlike Python’s `input()` function, C uses `scanf` to read input. `scanf` also uses format specifiers to determine the type of data to read. You must provide the **address** of the variable (`&variable`) so `scanf` knows where to store the entered value.

**Examples:**

```c
int age;
printf("Enter your age: ");
scanf("%d", &age);
printf("You entered: %d\n", age);
```

Here, `"%d"` tells `scanf` to read an integer and store it in `age`. The `&` (address-of) operator is crucial—without it, `scanf` wouldn’t know where to write the input.

**Reading Other Types:**

```c
double temperature;
printf("Enter the temperature: ");
scanf("%lf", &temperature); // %lf for double
printf("Temperature is: %.1f\n", temperature);

char ch;
printf("Enter a character: ");
scanf(" %c", &ch); // The space before %c helps skip any leftover whitespace
printf("You entered: %c\n", ch);
```

**Note:** For strings, you’ll typically use `scanf("%s", stringVariable);`, but strings and arrays need more explanation, so we’ll handle them in future lessons.

**Important Tips for `scanf`:**

- Always provide the address of the variable (`&var`).
- Be mindful that `scanf` stops reading at whitespace for `%s` and can potentially cause overflow if the input is longer than your buffer. We’ll address safer input methods later.

---

## 5. Differences from Python

- **Static vs. Dynamic Typing**:
  In Python, you can write `x = 5` and later `x = "Hello"` without issues. In C, if `x` is an `int`, you cannot assign a string to it later. You must decide the type upfront.

- **Memory Management**:
  Variables in C directly relate to memory. Understanding this will become more important as we delve into pointers and arrays.

- **No Built-in Input Prompting**:
  In Python, `input()` can convert types automatically. In C, you must specify exactly what type you expect and handle conversions yourself.

---

## 6. Example Program: Interactive Greeting

Let’s write a small program that reads the user’s name (just a single word for now), age, and then prints a greeting.

**Code Example:**

```c
#include <stdio.h>

int main(void) {
    char name[20];  // a char array of length 20 to store the name
    int age;

    printf("Enter your first name: ");
    scanf("%19s", name);  // %19s ensures we don't write beyond name's buffer

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Hello, %s! You are %d years old.\n", name, age);

    return 0;
}
```

**What’s Happening Here?**

- We declared `char name[20]` to store the user’s input. This means `name` can hold up to 19 characters plus a terminating `'\0'` character that marks the end of a string in C.
- We used `scanf("%19s", name)` to protect against writing more characters than the array can hold.
- `%s` prints the string, `%d` prints the integer age.

Try compiling and running this program:

```bash
gcc -o greeting greeting.c
./greeting
```

Enter your name and age, and see the output.

---

## 7. Practice Exercises

1. **Simple Math Operations**:
   Prompt the user for two integers, read them with `scanf`, and print their sum, difference, product, and quotient (for the quotient, use `float` or `double` to show decimals):

   ```c
   Enter two integers: 10 3
   Sum: 13
   Difference: 7
   Product: 30
   Quotient: 3.3333
   ```

2. **BMI Calculator**:
   Prompt the user for their weight (in kg, a floating-point) and height (in meters, also floating-point), then calculate and print their BMI.

   ```c
   Enter weight (kg): 70
   Enter height (m): 1.75
   Your BMI is: 22.86
   ```

   Use `double` for the calculations and `%.2f` to format the output.

3. **Experiment with Different Format Specifiers**:
   Try printing an integer using `%f` or a double using `%d`. Observe the warnings and the incorrect output. This will help you understand why using correct format specifiers is crucial.

---

## 8. What’s Next?

You have learned how to declare variables, use basic data types, and interactively read from and write to the terminal. As you continue, you’ll discover more complex data types like arrays, pointers, and structs, and learn to build larger, multi-file programs.

**In the next lessons**, we’ll dive deeper into:

- Control structures (`if`, `else`, `while`, `for`, `switch`) to make decisions and repeat actions.
- More on how memory works in C, how to handle strings safely, and basic error checking.

---

### End of Lesson 2

*You’ve laid another important stepping stone in your journey to mastering C. Move on to Lesson 3 once you’re comfortable with variables, data types, and basic I/O.*
