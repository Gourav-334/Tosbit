# SYNTAX EXECUTION



## 0. Description:

```c
void syntax_parser(char username[]);
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