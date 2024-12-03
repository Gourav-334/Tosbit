# SYNTAX EXECUTION



## 0. Description:

```
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

$$ \_*@\_*(STRING)\_*@\_* $$

- Until its just space, keep skipping the characters.
- If @ appears, open the comment.


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

```
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
    - 
        - Keep reading until you encounter an `"`.
        - Then keep printing the characters **attribute name** until `"` is encounter.
        - Again keep reading until you encounter an `"`.
        - Then keep printing the characters as **last attribute's data type** until `"` is encounter.
        - Again keep reading until you encounter an `"`.
        - Then keep printing the characters as **last attribute's key type** until `"` is encounter, without `\` being immediately previous to it.
        - If `]` is encountered & then immediately after it `\n` is encountered, then break from loop.