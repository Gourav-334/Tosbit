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
