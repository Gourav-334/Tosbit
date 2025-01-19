# SYNTAX EXECUTION



## 0. Description:

```c
void syntaxParser(char username[]);
```

- This documentation is regarding ***syntax_parser.h*** & ***syntax_parser.c***.
- Purpose of this library is to execute the designed automata to parse user commands & give corresponding appropriate answer.


## 1. General:

- Wait for user to input.
- Analyze
- If problem found:
    - Return error with cause.
- Else:
    - Execute


## @ Comment @

- Until its just space, keep skipping the characters.
- If $@$ appears, open the comment.


## open db db_name

- Open file `cache\\databases.tosbit` in read mode.
- Start reading each character one-by-one.
- Append the characters to buffer.
- If a 0 is encountered for the first time, append it.
- If again a 0 is encountered immediately after previous one, append it & decrypt whole string.
- Match the decrypted string to user entered DB name.
- If they match then terminate, else empty buffer & continue with upcoming characters.
- If EOF reached & match not found yet, DB doesn't exist.


## show struct table_name

- First of all, ban using `"`, `[`, `]` for users in Tosbit.

```json
{
    "fetch": ["fetch", "fetch"],
    "fetch": ["fetch", "fetch"],

    ...

    "fetch": ["fetch", "fetch"]
}
```

- If `database` is an empty string:
    - Print error saying database doesn't exist.
- Else if string is not empty:
    - Open `data\\db_name\\table_name\\details.json` in read mode.
        - Keep reading until you encounter an `"`.
        - Then keep printing the characters **attribute name** until `"` is encountered.
        - Again keep reading until you encounter an `"`.
        - Then keep printing the characters as **last attribute's data type** until `"` is encounter.
        - Again keep reading until you encounter an `"`.
        - Then keep printing the characters as **last attribute's key type** until `"` is encounter.
        - If `]` is encountered & then immediately after it `\n` is encountered, then break from loop.


## show all db / show all tables

```json
{
	"databases": [
		"db1",
		"db2",
        ...
        "dbn"
	]
}
```

- Open `data\\databases.json` in read mode.
- Start reading each character one-by-one.
- When `"` is encountered 3rd time, turn `reading` ON, empty buffer.
- Until EOF not reached:
    - Append characters to buffer until another `"` appears.
    - When `"` appears again, turn `reading` OFF, print buffer & keep walking until another `"` appears.


## make table Desk [string name, int age, float score, bool status]

### Syntax:

```
make table Desk[]

make table Desk[int]

make table Desk[int num]

make table Desk[int num, string]

make table Desk[int num, string code]

make table Desk[int num, int num]
```



## Attribute Parser


### Function:

```c
void attributeParser();
```


### Semantic checking:

```
[string age, int age]
```

- Start with parsing `(`.
- Keep parsing until a non-space charater comes.
- Then keep parsing & storing occuring string characters to buffer until a space occurs.
- Then check if this string matches to any of the Tosbit data types.
- If the data type doesn't match, empty buffer, return error & break.
- If they match, keep parsing until a non-space character appears.
- Now keep parsing & storing the characters as attribute name until a space appears.
- Stop at `)`.


### Creating table:

```json
{
	"tables": [
	]
}
```

- If there is no error in previous stage, proceed.
- Open `data\\db_name\\tables.json` in read & write mode.
- Keep reading with count of bytes until a `]` & `\n` are encountered consecutively.
- Now move the pointer by the number of bytes counted minus 4.
- And insert `,\n\t\"Table_name\"\n\t]\n}`.
- Exit & close the file.


### Storing configuration:

```json
{
	"name": ["string", "unique"],
	"age": ["int", "regular"]
}
```

- Now open `data\\db_name\\tbl_name\\details.json` in write mode.
- Append `{\n\t` to file.
- Keep parsing until a non-space appears.
- Then keep parsing & storing occuring string characters in dataType buffer until a space occurs.
- Continue parsing the string characters after space until `,` or `)` occurs.
- Store the fetched string in attribute buffer.
- Append `"Attribute": ["DataType", "unique"]` to file.
- If its a `,`, then append `,\n\t` & continue.
- Else if its a `]`, then append `\n}`.


### Setting up row environment:

```json
{
	"rows": [
	]
}
```

- Open `data\\db_name\\tbl_name\\rows.json` in write & append mode.
- Append `{\n\t"rows": [\n\t]\n}` to file.



## make db Office

### Basic:

```json
{
    "tables": [
    ]
}
```

1. Simply create a directory with name of database using `mkdir`.
2. Then open the directory & make a file named `tables.json` there.
3. Open `tables.json` in write mode & insert `{\n\t\"tables\": [\n\t]\n}` in it.


### Listing database name:

```json
{
    "databases": [
    ]
}
```

1. Open `data\\databases.json` in read & write mode.
2. Keep reading with count of bytes until a `]` & `\n` are encountered consecutively.
3. Now move the pointer by the number of bytes counted minus 4.
4. If number of `\"` is more than 2, insert `,\n\t\"Table_name\"\n\t]\n}`. Else insert `\n\t\"Table_name\"\n\t]\n}`.
5. Exit & close the file.



## delete table Desk

```json
{
	"tables": [
		"tintin",
		"polar",
		"conductor",
		"rambo"
	]
}
```


### File removal:

1. Remove directory `data/db_name/tbl_name`.


### Name removal:

1. Open the file `data/db_name/tables.json` in read & write mode.
2. Start reading & storing character to `data/cache.tosbit` in disk.
3. After reading the second `\"`, reading mode gets ON.
4. Only if reading mode is ON, follow the following algorithms.
5. When two `\t` are encountered consecutively, mark first `\t`'s position as `head`.
6. Find for a `\"`.
7. When found, store everything in buffer until another `\"` appears.
8. When it appears, check if the characters in buffer match the requested table name.
9. If it matches, search for two consecutive `\t` again & mark second one as `tail` & load everything until `head` into the cache. Then store everything from `tail` to the EOF.
10. Else if not found, repeat the loop.
11. After all this has been done, open `data/db_name/tables.json` in write mode.
12. Now copy all bytes from `data/cache.tosbit` to `data/db_name/tables.json`.
13. Now remove `data/cache.tosbit`.



## Push Parser


### Involved files:

- `data/db_name/tbl_name/details.json` (Read)
- `data/db_name/tbl_name/rows.json` (Write)


### details.json (Read)

```json
{
	"name": ["string", "unique"],
	"age": ["int", "regular"]
}
```


### rows.json (Write)

```json
{
	"rows": [
		{
			"name": "name7",
			"age": "7"
		},

		{
			"name": "name8",
			"age": "8"
		}
	]
}
```


### Buffer parsing objectives:

- Check if exact number of  passed.
- Check if correct data types are passed.
- Check proper spacing & grammar.
- For successful checks, insert data to table.


### Check Unique Value:

$$ totalVars\;=\;commaCount\;+\;1 $$

1. Move `14` bytes from start of the `rows.json` file.
2. Do the following until EOF not reached or duplicate value not found.
3. Empty `value2`.
4. Set value of `invCount` to `0`.
5. Go `1` byte forward.
6. Break if EOF reached.
7. Else, move `3` bytes forward.
8. Move until `invCount` is not equal to `((currArg-1)*4)+3`.
9. Now start adding the upcoming bytes to `value2` until a `"` appears.
10. If `value` & `value2` are equal, show appropriate error.
11. Else, continue with following.
12. Keep reading until its not equal to `totalArg*4`.
13. Set `invCount` to `0`.
14. Move fd forward by `4` bytes.
15. If next character is `,`, move forward by `4` bytes & repeat the process.
16. Else if its `\n`, stop the process.
17. Otherwise show appropriate message for file corruption & stop the process.


### Buffer parsing:

#### **CHECKING NUMBER OF ARGUMENTS**
1. Open `data/db_name/tbl_name/details.json` in read mode.
2. Also open `data/db_name/tbl_name/rows.json` in read & write mode.
3. Keep reading characters from buffer.
4. On each appearance of `,` in `buffer`, increament the value of `commaCount`.
5. Keep reading each byte from `details.json` one-by-one.
6. On each appearance of `"`, increament value of `invCount`.
7. Compare `commaCount` & `invCount/6`, then print appropriate feedback on error.
8. Set value of `invCount` back to `0`.

#### **DATA TYPE CHECKING**
9. Set fd of `data/db_name/tbl_name/details.json` to start of file.
10. Empty `attribute`, `dataType`, `key` & `value`.
11. Keep reading `details.json` until a `"` has been read.
12. Add upcoming bytes to `attribute` until another `"` appears.
13. Start reading again until a `"` is received.
14. Now, keep adding upcoming bytes to `dataType` until a `"` appears.
15. Keep reading until next `"` is encountered.
16. Now, keep adding upcoming bytes to `key` until a `"` appears.
17. Keep reading & appending bytes from `buffer` to `value` until a `,` appears (don't include `,`).
18. For `unique` `key`, check if duplicate value exists or not (`checkUnique()`).
19. If not, pass the value for being checked by automaton as per its `dataType`.

#### **WRITE DATA**
20. Else if it stops on accept state, modify the `value` removing whitespaces.
21. Then reach `6` bytes before the EOF in `rows.json`.
22. If next character is `}`, insert `,`.
23. Then insert `\n\n\t\t{\n\t\t\t"ATTRIBUTE": "VALUE"` for first value.
24. Move `3` bytes forward in `details.json`.
25. Keep reading until `}` or `"` appears.
26. For `}`, add `\n\t\t}\n\t]\n}` in `rows.json`.
27. Else for `[`, add `,\n\t\t\t` in `rows.json`.
28. If next character `"`, repeat the process for next attribute.
29. Close both the file pointers.

### Algorithmic challenges:

- Complex file operations
- Multiple automata
- Extreme looping & flow control
- Multiple counters
