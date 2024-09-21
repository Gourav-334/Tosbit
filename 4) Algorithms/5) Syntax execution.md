# SYNTAX EXECUTION


## General

- Wait for user to input.
- Analyze
- If problem found:
    - Return error with cause.
- Else:
    - Execute


## Comments

- Until its just space, keep skipping the characters.
- If @ appears, open the comment.


## open db db_name;

- Open file `cache\\databases.tosbit` in read mode.
- Start reading each character one-by-one.
- Append the characters to buffer.
- If a 0 is encountered for the first time, append it.
- If again a 0 is encountered immediately after previous one, append it & decrypt whole string.
- Match the decrypted string to user entered DB name.
- If they match then terminate, else empty buffer & continue with upcoming characters.
- If EOF reached & match not found yet, DB doesn't exist.
