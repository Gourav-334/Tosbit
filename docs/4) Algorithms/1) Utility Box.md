# UTILITY BOX

## 0. Description:

- This documentation is regarding ***utility_box.h*** & ***utility_box.c***.
- The primary role of this library is to provide service through basic utility functions to other libraries.


## 1. String Append:

```
void strappend(char str[], char *addition);
```

- Move pointer to the base of last character.
- Make this base as offset of string to be appended.
- Insert the string right there.


## 2. Constant String Append:

```
void constrappend(char str[], const char *addition);
```

- Move pointer to the base of last character.
- Make this base as offset of string to be appended.
- Insert the string right there.


## 3. Character Append:

```
void charappend(char str[], char addition);
```

- Move pointer to the base of last character.
- Make this base as offset of character to be appended.
- Insert the character right there.


## 4. Constant Character Append:

```
void const_charappend(char str[], const char addition);
```

- Move pointer to the base of last character.
- Make this base as offset of character to be appended.
- Insert the character right there.


## 5. Newline Remover:

```
void newline_remover(char str[]);
```

- Check if the last character of the string is a newline character.
- If yes, move to the offset of last character.
- Remove the newline character.


## 6. Front Character Remover:

```
void frontchar_remover(char str[]);
```

- Move to the offset of first character.
- Remove that first character.
- Move the pointer forward by 1 byte.


## 7. FLush Standard Input:

```
void flush_stdin();
```

- Flushes the standard input buffer which otherwise might interfere with input processes.


## 8. Binary Print:

```
void binary_print(char str[], int size);
```

- Move to the offset of first character of string.
- Start reading each character one by one.
- Print `-` for each character.
- Print `$` for each newline character.


## 9. Space Remover:

```
void remove_spaces(char str[]);
```

- Read each character of a string.
- If a space is encountered, mark its index & move until any character isn't encountered.
- When character is found, fill the marked space with this character & set that character's place as 0.
- If the array ends finding a character, keep nulling each space with 0, moving backward until a character is found.


## 10. String Shifter:

```
void str_shift(char str[], int start, int end, int direction, int steps);
```

- Know direction & steps to move.
- Move the cursor to start index.
- Copy the character to the choosen direction by choosen steps.
- Continue with next character.
- Repeat until end index reaches.
- As per the direction, fill the characters upto start/end with `0`.


## 11. Illegal Characters

```
int illegalChars(char arr[], char chars[]);
```

- Uses brute force approach to check if any illegal character is present in array.
- **<u>Brute force algorithm</u>:** Using two nested `for` loops for matching purposes.
- **<u>Illegal character</u>:** Character which must not be present in a string as per program maker's rule.
