# UTILITY BOX

## 0. Description:

- This file is regarding ***utility_box.h*** & ***utility_box.c***.
- The primary role of this library is to provide basic utility functions to other libraries.


## 1. `strappend()` (deprecated)

### **1.1 Introduction:**
```c
void strappend(char str[], char *addition);
```
- Appends a string to another string.
- `str` is the target string.
- `addition` is the string to append.

### **1.2 Algorithm:**
1. Move pointer to the base of last character.
2. Make this base as offset of string to be appended.
3. Insert the string right there.


## 2. `constrappend()` (deprecated)

### **2.1 Introduction:**
```c
void constrappend(char str[], const char *addition);
```
- Used for adding a constant string to another string.
- `str` is the target string.
- `addition` is the string to append.

### **2.2 Algorithm:**
1. Move pointer to the base of last character.
2. Make this base as offset of string to be appended.
3. Insert the string right there.


## 3. `charappend()`

### **3.1 Introduction:**
```c
void charappend(char str[], char addition);
```
- Used for appending a character to string.
- `str` is the target string.
- `addition` is the character to append.

### **3.2 Algorithm:**
1. Move pointer to the base of last character.
2. Make this base as offset of character to be appended.
3. Insert the character right there.


## 4. `const_charappend()`

### **4.1 Introduction:**
```c
void const_charappend(char str[], const char addition);
```
- Used for appending constant character to a string.
- `str` is the target string.
- `addition` is the character to append.

### **Algorithm:**
1. Move pointer to the base of last character.
2. Make this base as offset of character to be appended.
3. Insert the character right there.


## 5. `newline_remover()`

### **Introduction:**
```c
void newline_remover(char str[]);
```
- Removes the newline from the end of the string (if any).
- `str` is the string to remove newline from.

### **Algorithm:**
1. Check if the last character of the string is a newline character.
2. If yes, move to the offset of last character.
3. Remove the newline character.


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