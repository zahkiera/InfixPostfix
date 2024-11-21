# Infix to Postfix Expression

This C++ application allows users to input mathematical expressions in infix notation, convert them to postfix notation, and evaluate the result. It uses a custom templated Stack class to handle the operations of conversion and evaluation.

### Features

- **Infix to Postfix Conversion**: The program reads an infix expression (e.g., 3 + 5 * (2 + 1)) and converts it to postfix notation (e.g., 3 5 2 1 + * +).
- **Expression Evaluation**: After conversion, the postfix expression is evaluated using a stack, handling operations like addition, subtraction, multiplication, division, exponents, and modulus.
- **Error Handling**: Includes checks for invalid characters, operator precedence, and parentheses matching, ensuring robust and reliable operation.
- **Flexible Stack Implementation**: A templated Stack class that supports both character and numerical data types, making it reusable for different types of expressions.

### Functionality

1. **Input**: The user is prompted to enter a mathematical expression in infix notation.
**Conversion**: The input is processed to convert the expression from infix to postfix notation using operator precedence and parentheses handling.
2. **Evaluation**: The program evaluates the postfix expression using a stack, applying the appropriate operations.
3. **Output**: The program displays the postfix expression and the evaluated result.

