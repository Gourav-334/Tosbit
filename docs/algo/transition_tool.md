# TRANSITION TOOL



## 0. Description:

- This documentation is regarding ***transition_tool.h*** & ***transition_tool.c***.
- Its purpose is to provide functionalities for DFA-based operations.


## 1. `changeState()`:

### **1.1 Introduction:**
```c
int changeState(char input, char symbols[], char transition[], int *state, int dump);
```
- Used for changing state of DFA for an input symbol.
- `input` is the input symbol.
- `symbols` holds various symbols as a single string.
- `transition` is a virtual array (string with numbers separated by commas), representing various states mapped to corresponding symbols in previous parameter.
- `state` is the current state.
- `dump` is the state to dump at when none of the condition matches.

### **1.2 Algorithm:**
1. Receive the `input` and `state`.
2. Go through each character in `symbols`.
3. When the character matches `input`, take note of its index number.
4. Now traverse through array `transition`.
5. Count the coma when they appear & keep reading until the number of commas is same as the index number of `input` in `symbols`.
6. When they are equal, keep storing each character in another array `str` until another comma appears.
7. When coma appears, set value of `state` as that.


## 2. `breakValue()`

### **2.1 Introduction:**
```c
void breakValue(int *state, int breakState, int *brk);
```
- Used for breaking from the loop at a certain state.
- `state` is the current state.
- `breakState` is the state to break at.
- `brk` is the variable telling if to break from parsing or not.

### **2.2 Algorithm:**
1. Check if `state` is equal to `breakState`.
2. If yes, set `brk` to `TRUE`.
3. Else just return.


## 3. `appendState()`

### **3.1 Introduction:**
```c
void appendState(int *state, int breakState, char *target, char value);
```
- Used for appending a character to a string at a certain state.
- `state` is the current state.
- `breakState` is the state to append at.
- `target` is the target string to which we want to append.
- `value` is the value of character we want to add to `target`.

### **3.2 Algorithm:**
1. Check if `state` is equal to `breakState`.
2. If yes, set append `value` to `target`.
3. Else just return.


## 4. `limitChecker()`

### **4.1 Introduction:**
```c
void limitChecker(char *target, int limit, int *state, int newState, int *brk);
```
- Used for checking if limit for a string has reached.
- `target` is the string to check limit of.
- `limit` is the string's length limit.
- `state` is the current state.
- `newState` is the state to assign if limit is crossed.
- `brk` is the variable telling if to break from parsing or not.

---
