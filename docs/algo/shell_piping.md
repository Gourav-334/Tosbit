# SHELL PIPING


## 0. Description

- This file is regarding header `shell_piping.h` & source file `shell_piping.c`.
- Purpose of this pair is to provide facility with functions which requires piping output from shell.


## 1. `recordLog()`

### **1.1 Introduction:**
```c
void recordLog(char username[], char command[]);
```
- This function records log for an executed command.
- `username` is the passed username for log purpose.
- `command` is the command that user executed for the instance.

### **1.2 Algorithm:**
1. Open `logs/details.json` in `r` mode.
2. Move forward by `14` bytes.
3. Read all upcoming characters into `smallBuff` until a comma appears.
4. Store integer value of `samllBuff` as `folders`.
5. Clear `smallBuff`.
6. Move forward by `11` bytes.
7. Read all upcoming characters into `smallBuff` until a comma appears.
8. Store integer value of `samllBuff` as `files`.
9. Move forward by `10` bytes.
10. Read all upcoming characters into `smallBuff` until a `\n` appears.
11. Store integer value of `samllBuff` as `logs`.
12. Close the pointer to file.
13. If number of folders are `0`, do the following.
14. Increment the values of `folders`, `files` & `logs`. ---(1)
15. Create a new log folder with suffix as `1`. ---(1)
16. Create a log file in it with suffic `1`. ---(1)
17. Make a empty JSON list in that log file. ---(1)
18. Else if `files` is `100` & `logs` is less than `1000`, increment `logs` by `1`.
19. Else if `files` is less than `100` & logs is `1000`, do the following.
20. Increment files by `1`.
21. Set `logs` to `1`.
22. Create a new log file with incremented suffix.
23. Else if `files` is less than `100` & logs is less than `1000`, increment the `logs` by `1`.
24. Overwrite `details.json` with new data.
25. Pipe the command for getting current UST time.
26. Move `6` bytes backward from end in latest log file.
27. Get the next character.
28. If this character is `[`, write `\n\t\t`.
29. Else if its `}`, write `,\n\n\t\t`.
30. Remove newline character from the end of `largeBuff` (to store a log instance).
31. Write the formatted `largeBuff` with log instance to latest log file.
32. Close the file pointer.


## 2. `getLocation()`

### **2.1 Introduction:**
```c
void getLocation();
```
- Used for fetching currect location & store it through piping.

### **2.2 Algorithm:**
1. Pipe the location to string `loc`.
2. Close the pipe pointer.

---
