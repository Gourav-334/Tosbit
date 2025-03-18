# SYNTAX PARSER


## 1. `syntaxParser()`

### **1.1 Introduction:**
```c
void syntaxParser(char username[], char *user_cmd, int serverConn);
```
- Syntax parser as most know, parses the passed command to databases & feedbacks on wrong grammar.
- If grammar is found to be correct, the control is passed to `database_operations.c` for further action.
- It uses ***Deterministic Finite Automata*** for unambiguously parsing the command.
- Though it might be mistaken for ***Pushdown Automata*** for parallelly storing data during parsing.
- Reference in `../charts/Main Automaton.drawio`.
- `username` is the fetched username from local client-side.
- `user_cmd` is the command to database entered by user.
- `serverConn` tells if a request for connecting to server is passed.

### **1.2 Algorithm:**
1. Start the infinite input-output loop.
2. Clean the user command - `command`.
3. Receive command from the user.
4. Start the timer for measuring command execution time.
5. Set the `serverMode` as per what was `serverConn` passed as.
6. If `feedbackSize` is more than `0`, free `feedback`.
7. Start parsing command with DFA.
8. Stop reading the next byte in command.
9. After this process (halted or complete parsing), check the stopped state.
10. Store feedback accordingly or execute function accordingly (using switch-cases).
11. Reset `state` to `0`.
12. Stop the clock & add the output to `feedback`.
13. Print the feedback to screen.
14. If it was a run using `interpret()` without takeover, continue the loop.
15. Else break out.


## 2. `attributeParser()`

### **2.1 Introduction:**
```c
void attributeParser();
```
- Parses the attributes passed for making a table.
- Also uses DFA-based parser (reference in `../charts/Attribute Parser.drawio`).

### **2.2 Algorithm:**
1. Parse the `buffer` using DFA.
2. Set `state2` back to `0`.

---
