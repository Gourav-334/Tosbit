# DATABASE OPERATIONS


## New Contraints!

- Entities can't have spaces in them.
- Always keep the function name, its return type, parameters & core callings in it.


## 0. Description:

- `databases_operations.c` as a source file aims at providing functions which are called for applying various operations on a database.
- It contains complex algorithms that are called if parsing found error-free syntax.


## 1. `expandFeedback()`

### **1.1 Introduction:**
```c
void extendFeedback(char message[]);
```
- Purpose of this function is to allocate size & append a message to string `feedback`.
- Parameter `message` represents the string to be appended to `feedback`.

### **1.2 Algorithm:**
1. If the `feedback` is empty, allocate `1` byte of memory to it first (for string terminator).
2. Then expand the memory pointed by the size of message to be appended.
3. Append the message.


## 2. `clearEntity()`

### **2.1 Introduction:**
```c
void clearEntity(char *str);
```
- This function's purpose is to serve as a shortcut to use `memset()` for some fixed strings.
- Parameter `str` represents the string identifier for the string to be cleared.

### **2.2 Algorithm:**
1. Match the argument string `str` to the conditions.
2. Empty the string using `memset()` as per the matching value.
3. If none mathces, tell user about that.


## 3. `checkDbExistence()`

### **3.1 Introduction:**
```c
int checkDbExistence(int msg);
```
- This function is used for checking if a database exists or not.
- Parameter `msg` is passed as `TRUE` for acknowledging user on terminal about its existence, or `FALSE` for not.

### **3.2 Algorithm:**
1. Open `data/{DATABASE_NAME}/tables.tosbit` in `r` mode.
2. If it opens, return `TRUE`.
3. Else if it doesn't opens, return `FALSE`.
4. If `msg` is `TRUE`, also tell user if database actually exists or not.


## 4. `checkTableExistence()`

### **4.1 Introduction:**
```c
int checkTableExistence(int msg);
```
- This function is used for checking if a table exists or not in a opened database.
- Parameter `msg` is passed as `TRUE` for acknowledging user on terminal about its existence, or `FALSE` for not.

### **4.2 Algorithm:**
1. First check if a database is opened or not.
2. Open `data/databases.tosbit` in `r` mode.
3. If it opens, return `TRUE`.
4. Else if it doesn't opens, return `FALSE`.
5. If `msg` is `TRUE`, also tell user if table actually exists or not in currectly opened database.


## 5. `tableStructure()`

> **<u>NOTE</u>:** Dots (`.`) in many tosbit file sample in this file represent spaces.

### **5.1 Introduction:**
```c
void tableStructure();
```
- This function prints the structure of a table (its attributes, data types & keys).

### **5.2 Command:**
```tosbit
SHOW STRUCT tbl_name
```

### **5.3 Algorithm:**
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

> **<u>NOTE</u>:**
> - Some additions were made to many codes for adjusting table size if they are larger than required.
> - This is because the table size is determined by the largest values they contain.
> - These values are stored in `metadata.tosbit` & updates when its corresponding data are read.


## 6. `allDatabases()`

### **6.1 Introduction:**
```c
void allDatabases();
```
- This function prints the name of all databases.

### **6.2 Command:**
```tosbit
SHOW ALL DB
```

### **6.3 Algorithm:**
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

> **<u>NOTE</u>:** Function `allTables()` has the same algorithm, so I haven't discussed that over here.


## 8. `makeTable()`

### **8.1 Introduction:**
```c
void makeTable();
```
- This function makes the table as per user's request.

### **18.2 Command:**
```tosbit
MAKE TABLE tbl_name
```

### **8.3 Algorithm:**
1. First check if the table already exists in current database, using `checkDbExistence()`.
2. Check if table's name is larger than existing ones by fetching `metadata.tosbit` in `r` mode inside database folder.
3. If yes, then overwrite the number in `metadata.tosbit` with new length.
4. Append name of table to `table.tosbit` at `data/{DB_NAME}/{TABLE_NAME}/` & write `TABLE_MAX_LEN-strlen(table)` spaces.
5. Create `details.tosbit`, `metadata.tosbit` & `rows.tosbit` in same directory.
6. Write `10,10,6.` as default in `metadata.tosbit` (see meaning in `../represent/File System.md`).
7. For each character in `buffer`, do the following.
8. Open `details.tosbit` in `w` mode.
9. Skip until spaces are there.
10. Append upcoming characters to `dataType` until space appears.
11. Again skip until spaces are there.
12. Append upcoming characters to `attribute` until space appears.
13. Check in `attributeQueue` if the attribute name is repeated & raise error if repeated.
14. Queue the current attribute to `attributeQueue`.
15. Check if unique key have appeared through a flag `uniqueKey` & deny multiple of them.
16. Check if the current attribute is of `media` type but declared as unique.
17. Write attribute name to `details.tosbit`, then write `ATTR_MAX_LEN-strlen(attribute)` spaces & write a `,`.
19. Write data type name next, then write `DATATYPE_MAX_LEN-strlen(dataType)` spaces & write a `,`.
20. Write key name next, then write `KEY_MAX_LEN-strlen(key)` spaces & write a `,`.
21. Then write `strlen(attribute)` as default largest attribute value in table by default.
22. If more attributes are there, write `\n` next.

>**<u>NOTE</u>:** For any mismatch in  the middle of the process, remember the delete the table by writing first character as `\t` in `tables.tosbit`.


## 9. `makeDb()`

### **9.1 Introduction:**
```c
void makeDb();
```
- This function as the name says, is used for creating a database.

### **18.2 Command:**
```tosbit
MAKE DB db_name
```

### **9.3 Algorithm:**
1. Check if database exists or not.
2. If yes, acknowledge user with an error.
3. Else if not, open `metadata.tosbit` in `r+` mode.
4. Overwrite data if `strlen(database)` is more than what's written there.
5. Append the name of database at the end of `databases.tosbit` & write `DB_MAX_LEN-strlen(database)`.
6. Create directory by database's name & write `tables.tosbit` & `metadata.tosbit` in it.
7. Write `6.` as default in `metadata.tosbit` (for `Tables` as default largest length when printing).


## 10. `checkDataType()`

### **10.1 Introduction:**
```c
void checkDataType();
```
- DFA-based parser to scan what data types were used to create attributes for a table.

### **10.2 Algorithm:**
- Check at `../charts/Data Parser.drawio`.


## 11. `deleteTable()`

### **11.1 Introduction:**
```c
void deleteTable(int msg);
```

### **11.2 Command:**
```tosbit
DELETE TABLE tbl_name
```

### **11.3 Algorithm:**
1. Open `tables.tosbit` in `r+` mode.
2. Match each character of `table` to each character read from `tables.tosbit`.
3. If all matches until a space or `\n` appears or EOF is reached, go to the start of line & write `\t`.
4. Else if any mismatch is found inbetween, move by `tableLength - currLineCharsRead`.
5. If EOF reached, stop the process & return appropriate error message.
6. Else if its `\n`, continue the process iteration.

> **<u>NOTE</u>:** Again, function `deleteTable()` has the same algorithm, so I haven't discussed that over here.


## 12. `clearTable()`

### **12.1 Introduction:**
```c
void clearTable();
```
- This one clears whole table of its rows.

### **12.2 Command:**
```tosbit
CLEAR TABLE tbl_name
```

### **12.2 Algorithm:**
1. Check if database is opened or not.
2. If no, return error.
3. Else if yes, navigate to the table's directory.
4. Open `rows.tosbit` in `w` mode & close it.
5. Remove all media files stored as zip there.


## 13. `clearDb()`

### **13.1 Introduction:**
```c
void clearDb();
```

### **13.2 Command:**
```tosbit
CLEAR DB db_name
```

### **13.3 Algorithm:**
1. Check if database exists or not.
2. If not, return error to user.
3. Else if yes, remove its directory from `data/`.
4. Then recreate that directory with `tables.tosbit` & `metadata.tosbit` in it.
5. Fill `metadata.tosbit` with default value i.e. `6.`.


## 14. `typeParser()`

### **14.1 Introduction:**
```c
void typeParser();
```
- Parses a value for its given attribute.
- Other than `string` & `media`, rest of the data types use DFA-based parser.

### **14.2 Algorithm:**
#### STRING
1. Keep reading the value in the `buffer` but consider the size as per the limit.
#### MEDIA
1. Prompt user to enter path for the media file (no limitation on extension or size of file).
2. Acknowledge user that the file is being compressed.
3. Compress the file at its location.
4. Copy the compressed file to `data/{DB_NAME}/{TABLE_NAME}/`.
5. Remove the original compressed file from the provided path.
6. Print the actual size of file on screen & the compressed size of it using pipe.


## 15. `pushRows()`

### **15.1 Introduction:**
```c
void pushRows();
```
- Pushes a row to the end of the table.

### **15.2 Command:**
```tosbit
PUSH TO tbl_name.(1, Gourav, 7.8)
```

### **15.3 Algorithm:**
1. Check if database is opened or not.
2. If not, throw error to user.
3. Else if yes, check if table even exists or not.
4. If not, throw an error to user.
5. Else if it does exist, proceed further with given procedures.
6. Open `details.tosbit` in `r+` mode.
7. Also open `rows.tosbit` in `r+` mode.
8. Know the number of arguments passed through count of total commas.
9. Know actual total arguments by skipping `ATTR_MAX_LEN+1+DATATYPE_MAX_LEN+1+KEY_MAX_LEN+1+2` until end of file is reached.
10. As per it, provide proper feedback if insufficient or too much arguments are passed.
11. Move file pointer back to the starting.
12. Do the following for each argument.
13. Keep reading characters in `buffer` into `value` until a comma appears.
14. Now read characters from `details.tosbit` to `attribute` until space or comma appears.
15. For space appearing, skip by `ATTR_MAX_LEN-1-strlen(attribute)+1` (`+1` for comma).
16. Now read upcoming characters to `dataType` until space or comma appears.
17. For space appearing, skip by `DATATYPE_MAX_LEN-1-strlen(attribute)+1` (`+1` for comma).
18. Now read upcoming characters to `key` until space or comma appears.
19. For space appearing, skip by `KEY_MAX_LEN-1-strlen(attribute)+1` (`+1` for comma).
20. Now check if the passed argument is holding data type constraints or not.
21. Keep reading upcoming characters as numbers into `metaBuff` (largest value for an attribute) until space or `\n` comes.
22. If it was a space, skip forward by `1` byte (to reach `\n`).
23. If the value of current attribute is greater than the existing one (stored in `metaBuff`), then `2` bytes backward.
24. Overwrite the data with new one.
25. And if that is single-digited (`<10`), then write a whitespace too.
26. Skip forward by `1` byte to skip `\n` or reach end of file otherwise.
27. Queue all the recently fetched attribute, data type & key.
28. Follow step **13-27** until you are done with all arguments.
29. Close the file pointer safely.
30. If there are no rows stored in `rows.tosbit`, skip to end of file & insert an `\n`.
31. For each argument in `valueQueue`, do the following.
32. Write the current value in `valueQueue` to the file.
33. If it's boolean, write whitespace for `5-strlen(currentValue)` times.
34. Else write whitespace for `(VALUE_MAX_LEN-1)-strlen(currentValue))` times.
35. If this argument is not the last one, add a comma afterwards.
36. Follow step 32-35 until no argument is left.
37. Close the opened file pointer for `rows.tosbit`.
38. Free all the memory occupied by queues.


## 16. `selectionParser()`

### **16.1 Introduction:**
```c
void selectionParser();
```
- DFA-based parser to parse the arguments passed for `SELECT` command & extract arguments to queue.

### **16.2 Algorithm:**
- Check at `../charts/Nested DFA.drawio`.


## 17. `allRows()`

### **17.1 Introduction:**
```c
void allRows();
```
- Used for printing all the rows in a table to screen.

### **17.2 Algorithm:**
```tosbit
SELECT tbl_name.(@)
```
>**<u>NOTE</u>:** The markings below as `---(1)` or `---(2)` etc denote that a line with same numbers falls under same block of loop.
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

>**<u>NOTE</u>:** Console-table was later made self-adjustable like other commands, adjusting itself when table larger than required is noticed.


## 18. `updateAll()`

### **18.1 Introduction:**
```c
void updateParser();
```
- Updates all the rows as per the value requested with their respective attributes.

### **18.2 Command:**
```tosbit
UPDATE tbl_name.(sno=1, name=Gourav, score=7.8)
```

### **18.3 Algorithm:**
#### details.tosbit
```tosbit
$sno............................,int...,unique.,4.\n
name............................,string,regular,6.\n
score...........................,int...,regular,5.
```
#### rows.tosbit:
```tosbit
1...............................,Ali.............................,65.............................\n
2...............................,Rishab..........................,80.............................
```
#### Macro steps:
1. Check for table's existence.
2. Extract each attribute's name, data type, key type, largest lenght & mark if update needed.
3. Reject whole operation if a unique or file attribute is involved.
4. Evaluate each attribute for its correct data type.
5. With reference to all extracted attributes & their marking, update their values.

#### Micro steps:
1. Check for table's existence.
2. Open `db_name/tbl_name/details.tosbit` in `r` mode.
3. While EOF not reached, follow the instructions below.
4. Keep reading the upcoming characters & appending them to `attribute` until a space or `,` appears.
5. Queue the attribute to `attributeQueue`. ---(1)
6. If this attribute matches to anyone in `argumentQueue`, queue `yes` to marker queue. ---(1)
7. Else queue `no` to marker queue. ---(1)
8. Move FD by `(ATTR_MAX_LEN+1)-characterRead` bytes. ---(1)
9. Keep reading the upcoming characters & appending them to `dataType` until a space or `,`. ---(1)
10. Queue the data type to `dataTypeQueue`. ---(1)
11. Move FD by `(DATATYPE_MAX_LEN+1)-characterRead` bytes. ---(1)
12. Keep reading the upcoming characters & appending them to `key` until a space or `,`. ---(1)
13. Queue the key to `keyQueue`. ---(1)
14. If current mark is `yes` & data type doesn't match, reject whole operation with error. ---(1)
15. Else if current mark is `yes` & key is either unique or file, reject whole operation with error. ---(1)
16. Move FD by `(KEY_MAX_LEN+1)-characterRead` bytes. ---(1)
17. Keep reading the upcoming characters & appending them to `largestValue` until a space or `\n`. ---(1)
18. Queue the largest value to `largestValueQueue`. ---(1)
19. Move FD by `(2+1)-characterRead` bytes. ---(1)
20. After this loop, open `db_name/tbl_name/rows.tosbit` in `r+` mode.
21. While EOF not reached, follow the instructions below.
22. If data type is marked `Yes`, overwrite with what's at node `iter % value.n` of `value`.
23. Write space for `ATTR_MAX_LEN-charsPrinted` times for non-booleans & for `5-charsPrinted` times for booleans. ---(1)
24. Else if data type is marked `No`, skip `ATTR_MAX_LEN` bytes for non-booleans & for `5` times for booleans.
25. Move FD by `1` byte.
26. Increment `iter` by `1`.
27. Empty all the queues created & used.

---