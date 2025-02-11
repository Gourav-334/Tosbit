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


## `deleteTable()`

1. Open `tables.tosbit` in `r+` mode.
2. Match each character of `table` to each character read from `tables.tosbit`.
3. If all matches until a space or `\n` appears or EOF is reached, go to the start of line & write `\t`.
4. Else if any mismatch is found inbetween, move by `tableLength - currLineCharsRead`.
5. If EOF reached, stop the process & return appropriate error message.
6. Else if its `\n`, continue the process iteration.


## `showRows()`

```tosbit
SHOW Desk.(sno,name,score) WHERE (sno>5 & score=7.00)
```

### Columns:

#### ALL

```tosbit
@
```
1. Open `db_name/tbl_name/details.tosbit` in `r` mode.
2. While EOF not reached, follow the instructions below.
3. Move FD forward by `(MAX_ATTR_LEN-1)+1+(DT_MAX_LEN-1)+1+(KEY_MAX_LEN-1)+1`.
4. Fetch the upcoming bytes to `largestAttributeS` until a space of `\n` or EOF approaches.
5. Convert `largestAttributeS` to `sizeQueue`.
6. If a space was encountered, move FD forward by one byte.
7. Now, for number of elements in `sizeQueue` follow the instructions given below.
8. Print `+` & then `-` for current queue element (in integer) times.
9. After that, print `+\n`.
10. Move FD to start of file.
11. Until not reached EOF, follow the instructions given below.
12. Print `|`.
13. Keep printing readings from `details.tosbit` until a space or `,` is encountered.
14. If a space was encountered, move FD by `(MAX_ATTR_LEN-1)+1+(DT_MAX_LEN-1)+1+(KEY_MAX_LEN-1)+1+2-recentlyReadChars+1` bytes.
15. After this process, print `|\n`.
16. Again, for number of elements in `sizeQueue` follow the instructions given below.
17. Print `+` & then `-` for current queue element (in integer) times.
18. After that, print `+\n`.
19. Sum the integer values of all strings in queue as `rowLength` & then add number of queue elements to it (to include commas).
20. Open `db_name/tbl_name/rows.tosbit` in `r` mode.
21. Until EOF not reached, follow the instructions given below.
22. Read next character from file. ---(1)
23. If this character is `\t`, move FD forward by `rowLength+1` & continue to next iteration. ---(1)
24. Else, move FD backward by one byte. ---(1)
25. For number of elements in `sizeQueue`, do the following. ---(1)
26. Print `|` & then readings from file `for` {integer value of current queue element} times.
27. Move FD forward by one byte & continue.
28. After that process, print `|\n` & increment `rowCount` for stats. ---(1)
29. And after everything, for number of elements in `sizeQueue` follow the instructions given below.
30. Print `+` & then `-` for current queue element (in integer) times.
31. After that, print `+\n`.
32. Print the stat information for number of rows afterwards.

>**<u>NOTE</u>:** Make this console-table self-adjustable too with readings.

#### SELECTIVE

```tosbit
sno, name, score
```
