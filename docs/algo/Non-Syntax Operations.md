# NON-SYNTACTICAL OPERATIONS


## Record Log

```c
void recordLog();
```

### Algorithm:

1. Open `data/logs/details.json` in `r+` mode.
2. Move `14` bytes forward from start.
3. Now fetch upcoming bytes to `buffer` until `,` appears.
4. Convert `buffer` to integer `folders` & empty `buffer`.
5. Now move `11` bytes forward from current position.
6. Now fetch upcoming bytes to `buffer` until `,` appears.
7. Convert `buffer` to integer `files` & empty the `buffer`.
8. Now move `10` bytes forward from current position.
9. Now fetch upcoming bytes to `buffer` until `,` appears.
10. Convert `buffer` to integer `logs` & empty the `buffer`.
11. If `folders` is `0`, increment value of `folders`, `files` & `logs` ---(1).
12. Create folder `data/logs/logset{FOLDERS}` & `data/logs/logset{FOLDERS}/logs{FILES}.json`.
13. Else if `files` is `100` & `logs` is `1000`, increment value of `folders`, set `files` & `logs` to `1`. ---(1).
14. Else if `files` is `100` & `logs` is not `1000`, increment value of `logs` ---(1).
15. Else if `files` is not `100` & `logs` is `1000`, increment value of `files` & set `logs` to `1` ---(1).
16. Else if `files` is not `100` & `logs` is not `1000`, increment value of `logs` ---(1).
17. Overwrite `data/logs/details.json` file with new details.
18. Save the path to log file accordingly.
19. Fetch & pipe current time to `time`.
20. Open `data/logs.json` in `r+` mode.
21. If doesn't opens, then display appropriate message & stop the process.
22. Move `6` bytes back from EOF.
23. Read next byte forward.
24. If its `[`, insert `\n\t\t`.
25. Else for `{`, insert `,\n\n\t\t`.
26. Now insert `{\n\t\t\t"serial": {LOGS},\n\t\t\t"UTC": "{TIME}",\n\t\t\t"location": "{LOC}"\n\t\t\t"author": {USERNAME},\n\t\t\t"command": "{COMMAND}"\n\t\t}`.
27. Close all file descriptors.


### Clustering:

$$ 1\;log\;file\;=\;1000\;records $$
$$ 1\;log\;folder\;=\;100\;log\;files $$
