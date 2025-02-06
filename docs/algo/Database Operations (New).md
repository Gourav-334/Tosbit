# DATABASE OPERATIONS (NEW)


## New Contraints!

- Entities can't have spaces in them.
- Always keep the function name, its return type, parameters & core callings in it.


## `checkDbExistence()`

1. Open `data/{DATABASE_NAME}/tables.tosbit` in `r` mode.
2. If it opens, return `true`.
3. Else if it doesn't opens, return `false`.


## `checkTableExistence()`

1. Open `data/{DATABASE_NAME}/{TABLE_NAME}/details.tosbit` in `r` mode.
2. If it opens, return `true`.
3. Else if it doesn't opens, return `false`.


## `tableStructure()`

```tosbit
10,10,6.
```

1. Open `data/{DATABASE_NAME}/{TABLE_NAME}/metadata.tosbit` in `r` mode.
2. Fetch first two bytes from `metadata.tosbit` & convert it to integer for being the largest attribute length.
3. Move FD by one byte.
4. Fetch next two bytes from `metadata.tosbit` & convert it to integer for being the largest data type length.
5. Fetch next two bytes from `metadata.tosbit` & convert it to integer for being the largest key length.

```tosbit
name............................,string,unique.,5.\n
age.............................,int...,regular,4.
```

6. Open `data/{DATABASE_NAME}/{TABLE_NAME}/details.tosbit` in `r` mode.
7. Print `+`, then `-` for the largest attribute length.
8. Print `+`, then `-` for the largest data type length.
9. Print `+`, then `-` for the largest key length, then print `+\n`.
10. Print `|Attributes`, then space for `largestAttrLen - 10` times.
11. Print `|Data Types`, then space for `largestDataTypeLen - 10` times.
12. Print `|Keys`, then space for `largestKeyLen - 4` times, then `|\n`.
13. Print `+`, then `-` for the largest attribute length.
14. Print `+`, then `-` for the largest data type length.
15. Print `+`, then `-` for the largest key length, then print `+\n`.
16. Until EOF not reached, do the following ---(1).
17. Print `|`, then whatever appears in `details.json` until a space or `,` is read, then space for `largestAttrLen - recentlyPrintedAttrLen` times.
18. If a space was read, move FD forward by `MAX_ATTR_LEN - (recentlyPrintedAttrLen + 2)` bytes.
19. Print `|`, then whatever appears in `details.json` until a space or `,` is read, then space for `largestDataTypeLen - recentlyPrintedDataTypeLen` times.
20. If a space was read, move FD forward by `MAX_DT_LEN - (recentlyPrintedDataTypeLen + 2)` bytes.
21. Print `|`, then whatever appears in `details.json` until a space or `,` is read, then space for `largestKeyLen - recentlyPrintedKeyLen` times.
22. If a space was read, move FD forward by `MAX_KEY_LEN - (recentlyPrintedKeyLen + 4)` bytes.
23. Print an `|\n`.
24. Else if an `\n` was read, continue the process.
25. After the whole process, follow the given instructions below.
26. Print `+`, then `-` for the largest attribute length.
27. Print `+`, then `-` for the largest data type length.
28. Print `+`, then `-` for the largest key length, then print `+\n`.


## `allDatabases()`

```tosbit
db1.............................\n
db2.............................\n
mydb............................
```

1. Open `data/metadata.tosbit` in `r` mode.
2. Keep reading bytes until space appears or EOF is reached & convert it to integer as `largestDbLen`.
3. Open `data/databases.tosbit` in `r` mode.
4. Print `+`, then `-` for the largest database length, then print `+\n`.
5. Print `|Databases`, then space for `largestDbLen - 10`, then print `|\n`.
6. Print `+`, then `-` for the largest database length, then print `+\n`.
7. Print `|`.
8. Do the following until EOF not reached or process not stopped.
9. Read & print bytes from `databases.tosbit` until a space or `,` is not encountered.
10. Print `|\n`
11. If a space was encountered, move FD forward by `((MAX_DB_LEN-1) - recentlyPrintedChars) + 2` ---(1).
12. If next byte is `\n`, repeat the process.
13. Else if EOF is reached, stop the process.
14. After the process is done, follow the instructions below.
15. Print `+`, then `-` for the largest database length, then print `+\n`.
