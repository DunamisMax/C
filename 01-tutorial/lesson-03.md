# Lesson 3: Control Structures – Conditionals and Loops

**Objectives:**

- Understand relational and logical operators.
- Learn how to use `if`, `else if`, `else`, and `switch` statements to make decisions.
- Explore looping constructs (`while`, `for`, `do-while`) to repeat actions.
- Gain insight into common control flow patterns to handle various programming scenarios.

---

## 1. Recap of Lessons 1 and 2

So far, you’ve learned how to:

- Write, compile, and run a simple C program (Lesson 1).
- Declare variables, understand basic data types, and use `printf`/`scanf` for I/O (Lesson 2).

You’ve created interactive programs that take input and produce output. However, these programs always followed a simple, linear path. In this lesson, we’ll add logic to branch and loop, allowing more interesting and flexible behavior.

---

## 2. Relational and Logical Operators

To make decisions, you need to compare values. C provides relational and logical operators to form conditions:

**Relational Operators**:

- `==` Equal to
- `!=` Not equal to
- `>`  Greater than
- `<`  Less than
- `>=` Greater than or equal to
- `<=` Less than or equal to

**Logical Operators**:

- `&&` Logical AND (true if both operands are true)
- `||` Logical OR (true if at least one operand is true)
- `!`  Logical NOT (true if operand is false)

**Examples**:

```c
int a = 5, b = 10;
(a == b)    // false
(a < b)     // true
(a != b)    // true
(a >= 5)    // true

int x = 7;
(x > 0 && x < 10) // true if x is between 1 and 9
(x < 5 || x > 20) // true if x is less than 5 or greater than 20
!(x == 7)         // false, since x == 7 is true and ! flips it
```

---

## 3. `if`, `else if`, and `else` Statements

**Syntax**:

```c
if (condition) {
    // Code runs if condition is true
} else if (other_condition) {
    // Runs if first condition was false and other_condition is true
} else {
    // Runs if none of the above conditions are true
}
```

**Example**:

```c
#include <stdio.h>

int main(void) {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    if (num > 0) {
        printf("%d is positive.\n", num);
    } else if (num < 0) {
        printf("%d is negative.\n", num);
    } else {
        printf("You entered zero.\n");
    }

    return 0;
}
```

**Explanation:**

- The program checks if `num > 0`. If true, it prints that the number is positive.
- If not, it checks `num < 0`.
- If neither is true, it must be zero.

---

## 4. The `switch` Statement

For multiple discrete values of a single variable, `switch` can be cleaner than multiple `if` statements.

**Syntax**:

```c
switch (expression) {
    case value1:
        // Code for when expression == value1
        break;
    case value2:
        // Code for value2
        break;
    default:
        // Code if no case matches
        break;
}
```

**Example**:

```c
#include <stdio.h>

int main(void) {
    int choice;
    printf("Enter a number (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("You chose option 1.\n");
        break;
    case 2:
        printf("You chose option 2.\n");
        break;
    case 3:
        printf("You chose option 3.\n");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }

    return 0;
}
```

**Notes:**

- `break;` prevents fall-through. Without `break`, execution continues into the next case.
- `default:` runs if no other case matches, similar to `else`.

---

## 5. Loops: `while`, `for`, and `do-while`

Loops allow you to repeat actions multiple times.

### `while` Loop

**Syntax**:

```c
while (condition) {
    // loop body
}
```

The loop runs as long as `condition` is true. If it starts false, the loop body never executes.

**Example**:

```c
int count = 1;
while (count <= 5) {
    printf("Count: %d\n", count);
    count++;
}
```

This will print `Count: 1` through `Count: 5`.

### `for` Loop

A `for` loop is often used when you know how many times you need to iterate.

**Syntax**:

```c
for (initialization; condition; increment) {
    // loop body
}
```

**Example**:

```c
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}
```

This prints the numbers 0 to 9 on one line.

### `do-while` Loop

Similar to `while`, but guarantees the loop runs at least once before checking the condition.

**Syntax**:

```c
do {
    // loop body
} while (condition);
```

**Example**:

```c
int num;
do {
    printf("Enter a number (positive to continue, negative to stop): ");
    scanf("%d", &num);
} while (num >= 0);
```

This loop asks for input repeatedly until a negative number is entered.

---

## 6. Breaking Out of Loops and Skipping Iterations

- **`break;`** immediately exits the closest `while`, `for`, or `switch` structure.
- **`continue;`** skips the rest of the current loop iteration and continues with the next iteration.

**Example using `continue`**:

```c
for (int i = 1; i <= 10; i++) {
    if (i == 5) {
        continue; // Skip printing 5
    }
    printf("%d ", i);
}
```

This prints 1 2 3 4 6 7 8 9 10, skipping 5.

---

## 7. Example Program: Summation and Averaging

Let’s write a program that:

1. Asks the user how many numbers they want to sum.
2. Reads each number in a `for` loop.
3. Calculates the total sum and the average.

**Code Example**:

```c
#include <stdio.h>

int main(void) {
    int n;
    printf("How many numbers do you want to sum? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid count.\n");
        return 0;
    }

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int value;
        printf("Enter number %d: ", i);
        scanf("%d", &value);
        sum += value;
    }

    double average = (double)sum / n;
    printf("Sum = %d, Average = %.2f\n", sum, average);

    return 0;
}
```

**Key Points:**

- If `n` is not positive, the program skips the loop.
- We cast `sum` to `double` before dividing by `n` to get a floating-point average.
- The loop runs exactly `n` times, reading and adding each number.

---

## 8. Practice Exercises

1. **Guessing Game**:
   Ask the user to guess a secret number between 1 and 10. Use a `while` or `for` loop to let them guess multiple times. If they guess correctly, print a success message and break out of the loop. If they run out of guesses, reveal the number.

2. **Multiplication Table**:
   Prompt the user for a number, then use a `for` loop to print its multiplication table (e.g., for `5`, print `5x1=5`, `5x2=10`, …, `5x10=50`).

3. **Menu System**:
   Display a simple menu using `switch`:

   ```c
   1. Print Hello
   2. Print Goodbye
   3. Exit
   ```

   Use a `do-while` loop to repeatedly show the menu until the user chooses `3` to exit.

---

## 9. What’s Next?

With control structures, you can now:

- Make decisions (`if`, `else`, `switch`).
- Repeat tasks (`while`, `for`, `do-while`).
- Exit loops early (`break`) or skip to the next iteration (`continue`).

**In the next lessons**, we will explore:

- More about memory, arrays, and how to handle strings safely.
- Functions: how to break down your code into reusable pieces.
- Structs and more complex data structures.

---

### End of Lesson 3

*You’ve added an essential tool to your toolkit: control over program flow. Once you’re comfortable making decisions and using loops, move on to Lesson 4 to learn about arrays and further data handling.*