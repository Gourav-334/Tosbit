# UTILITY BOX

## 0. Description:

- This documentation is regarding ***utility_box.h*** & ***utility_box.c***.
- The primary role of this library is to provide service through basic utility functions to other libraries.


## 1. String Append:

```c
void strappend(char str[], char *addition);
```

- Move pointer to the base of last character.
- Make this base as offset of string to be appended.
- Insert the string right there.


## 2. Constant String Append:

```c
void constrappend(char str[], const char *addition);
```

- Move pointer to the base of last character.
- Make this base as offset of string to be appended.
- Insert the string right there.


## 3. Character Append:

```c
void charappend(char str[], char addition);
```

- Move pointer to the base of last character.
- Make this base as offset of character to be appended.
- Insert the character right there.


## 4. Constant Character Append:

```c
void const_charappend(char str[], const char addition);
```

- Move pointer to the base of last character.
- Make this base as offset of character to be appended.
- Insert the character right there.


## 5. Newline Remover:

```c
void newline_remover(char str[]);
```

- Check if the last character of the string is a newline character.
- If yes, move to the offset of last character.
- Remove the newline character.


## 6. Front Character Remover:

```c
void frontchar_remover(char str[]);
```

- Move to the offset of first character.
- Remove that first character.
- Move the pointer forward by 1 byte.


## 7. FLush Standard Input:

```c
void flush_stdin();
```

- Flushes the standard input buffer which otherwise might interfere with input processes.


## 8. Binary Print:

```c
void binary_print(char str[], int size);
```

- Move to the offset of first character of string.
- Start reading each character one by one.
- Print `-` for each character.
- Print `$` for each newline character.


## 9. String Shifter:

```c
void str_shift(char str[], int start, int end, int direction, int steps);
```

- Know direction & steps to move.
- Move the cursor to start index.
- Copy the character to the choosen direction by choosen steps.
- Continue with next character.
- Repeat until end index reaches.
- As per the direction, fill the characters upto start/end with `0`.


## 10. Illegal Characters

```c
int illegalChars(char arr[], char chars[]);
```

- Uses brute force approach to check if any illegal character is present in array.
- **<u>Brute force algorithm</u>:** Using two nested `for` loops for matching purposes.
- **<u>Illegal character</u>:** Character which must not be present in a string as per program maker's rule.


## 11. Space Remover:

```c
void spaceRemover(char str[]);
```

- Start reading from 0th index of string until the pointer reaches a symbol (not a whitespace).
- Mark this index as `start`.
- Now start reading from end of the string until it reaches a symbol too.
- When encountered, mark this index as `end`.
- Now copy character between `start` & `end` to the target variable.

---