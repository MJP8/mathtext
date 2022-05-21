# MathText
**An easy compiler and documentary for a new and simple programming language.**

---
## Documentary
### Basic math
#### `write`
The `write` statement is used to display an number, `true`, or `false`.
- **`write 143`**: This statement is pretty clear; it obviously displays "143".
- **`write true`, `write false`**: These also are clear.
- **`write var_name`**: This statement writes the value of variable `var_name`. See [Variables](#Variables).
- **`write 1 + 1`**: prints the sum of 1 + 1. See [Operators](#Operators).
#### Operators
The opererators are
- `+` for addition,
- `-` for subtraction,
- `/` for division,
- and `*` for multiplication.
### Variables
Variables are pretty simple in MathText. To create a variable write `var var_name = 123.456`, and to read one write `write var_name`.
### Interpreter Guide
#### Error handling
If you had code, say like this:
```
write 2 + 2
var test : wrong
write 3 * 3
```
the interpreter would output:
```
4
Error at line 2
```
