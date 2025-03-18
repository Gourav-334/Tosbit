# ENGINE


## 0. Description

- This file is regarding the source file `engine.c`.
- The purpose of engine is to assemble all components at common place & power the terminal from there for Tosbit.
- Its the central place where rest of the files are imported & run.


## 1. `main()`

### **1.1 Introduction:**
```c
int main(int argc, char **argv[]);
```
- The entry point for it to run on terminal, as all the **C** programs.
- `argc` is the count of total arguments passed when running the executable for engine.
- `argv` is the array of all those passed arguments.

### **1.2 Algorithm:**
1. Call `profileManager()` to authenticate user.
2. Ask user if it wants to connect with an external server.
3. If yes, ask for server information like port, IP, host name & host password etc.
4. Then set the connection.
5. If no, then call `syntaxParser()` for command loop.

---
