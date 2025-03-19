# UTILITY BOX


## 0. Description:

- This file is regarding ***utility_box.h*** & ***utility_box.c***.
- The primary role of this library is to provide basic utility functions to other libraries.
- Many will notice most functions here to be deprecated & using underscores in function naming.
- As the project progressed, we changed the naming convention to camel casing for more readability.
- The deprecated functions can be easily implemented without functions, being one liners or two.
- Other reason for deprecation is the unnecessary returning or strict parameter types.
- Despite all this, these are used since its inception but will be replaced soon to reduce ambiguity.


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


## 3. `charappend()` (deprecated)

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


## 4. `const_charappend()` (deprecated)

### **4.1 Introduction:**
```c
void const_charappend(char str[], const char addition);
```
- Used for appending constant character to a string.
- `str` is the target string.
- `addition` is the character to append.

### **4.2 Algorithm:**
1. Move pointer to the base of last character.
2. Make this base as offset of character to be appended.
3. Insert the character right there.


## 5. `newline_remover()`

### **5.1 Introduction:**
```c
void newline_remover(char str[]);
```
- Removes the newline from the end of the string (if any).
- `str` is the string to remove newline from.

### **5.2 Algorithm:**
1. Check if the last character of the string is a newline character.
2. If yes, move to the offset of last character.
3. Remove the newline character.


## 6. `frontchar_remover()` (deprecated)

### **6.1 Introduction:**
```c
void frontchar_remover(char str[]);
```
- Removes the first character from a string & shifts rest of them to left by `1` byte.
- `str` is the target string.

### **6.2 Algorithm:**
1. Move to the offset of first character.
2. Remove that first character.
3. Move the pointer forward by `1` byte.


## 7. `flush_stdin()` (deprecated)

### **7.1 Introduction:**
```c
void flush_stdin();
```
- Flushes the standard input buffer which otherwise might interfere with input processes.

### **7.2 Algorithm:**
1. While end of line (`\n`) is not read, keep reading characters from input buffer.


## 8. `binary_print()` (deprecated)

### **8.1 Introduction:**
```c
void binary_print(char str[], int size);
```
- Prints whole string with `\n` as `$`.
- `str` is the target string to print.

### **8.2 Algorithm:**
1. Move to the offset of first character of string.
2. Start reading each character one by one.
3. Print `-` for each character.
4. Print `$` for each newline character.


## 9. `str_shift()` (untested)

### **9.1 Introduction:**
```c
void str_shift(char str[], int start, int end, int direction, int steps);
```
- Used for shifting a string to certain direction & certain steps (or bytes).
- `str` is the target string.
- `start` is the target leftmost byte.
- `end` is the target rightmost byte.
- `direction` is whether to move bytes toward left (`-1`) or right (`1`).
- `steps` is the number of bytes to move it by.

### **9.2 Algorithm:**
1. Know direction & steps to move.
2. Move the cursor to start index.
3. Copy the character to the choosen direction by choosen steps.
4. Continue with next character.
5. Repeat until end index reaches.
6. As per the direction, fill the characters upto start/end with `0`.


## 10. `illegalChars()`

### **10.1 Introduction:**
```c
int illegalChars(char arr[], char chars[]);
```
- Detects if unrequired (illegal) characters are there in a string.
- `arr` is the string with each unrequired characters.
- `chars` is the target string.

### **10.2 Algorithm:**
1. Uses brute force approach to check if any illegal character is present in array.
2. **<u>Brute force algorithm</u>:** Using two nested `for` loops for matching purposes.
3. **<u>Illegal character</u>:** Character which must not be present in a string as per program maker's rule.


## 11. `illegalChar()`

### **11.1 Introduction:**
```c
int illegalChar(char character, char chars[]);
```
- Check if an illegal character is present in a string.
- `character` is the character to search.
- `chars` is the target string.

### **11.2 Algorithm:**
1. Apply linear search on the `chars` to find `character`.


## 12. `reachedEOF()`

### **12.1 Introduction:**
```c
int reachedEOF(FILE *fptr);
```
- A safer alternative to using `feof()`.
- `fptr` is the pointer to target file.

### **12.2 Algorithm:**
1. Read the next byte from current position.
2. If `feof()` returns `TRUE`, end of file is reached.
3. Else if `feof()` returns `FALSE`, end of file is not reached yet.
4. In either cases, move the cursor backward by `1` byte.


## 13. `newFile()`

### **13.1 Introduction:**
```c
int newFile(FILE *fptr);
```
- Checks if a file is new (no bytes written).
- `fptr` is the pointer to file which checks presence of the file.

### **13.2 Algorithm:**
1. Calculate its position at start of file.
2. Claculate its position at end of file.
3. If both are same, then its a new file.
4. Else its an old one.


## 14. `spaceRemover()`

### **14.1 Introduction:**
```c
void spaceRemover(char str[]);
```
- Removes spaces from both the ends of the string.
- `str` is the target string.

### **14.2 Algorithm:**
1. Start reading from 0th index of string until the pointer reaches a symbol (not a whitespace).
2. Mark this index as `start`.
3. Now start reading from end of the string until it reaches a symbol too.
4. When encountered, mark this index as `end`.
5. Now copy character between `start` & `end` to the target variable.


## 15. `itoa()`

### **15.1 Introduction:**
```c
char *itoa(int x, char *ascii);
```
- Used for converting an integer into ASCII string.
- `x` is the integer.
- `ascii` is a global string for temporary storage.

### **15.2 Algorithm:**
1. Format the string `ascii` to store integer `x` as a string.
2. Return the string `ascii`.


## 16. `addTerminator()` (deprecated)

### **16.1 Introduction:**
```c
char *addTerminator(char *str);
```
- Appends string terminator to a string.
- `str` is the target string.

### **16.2 Algorithm:**
1. Append `\0` to the index equal to string's length.
2. Return the string.


## 17. `printRaw()`

### **17.1 Introduction:**
```c
void printRaw(char *str);
```
- Prints a string in raw form.
- Targetting special characters like `\n`, `\t`, `\a` etc.
- `str` is the target string.

### **17.2 Algorithm:**
1. Use curly braces to show clear separation from rest of the data on screen.
2. Use switch-cases to print the special characters as it is (might involve multiple characters).
3. For example, `\n` can be printed as `\\n` to print literally `\n` on screen.

---