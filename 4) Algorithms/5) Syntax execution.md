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
- Until EOF not reached, read each character:
    - If 0 encountered, decrypt string in buffer & append it to enc_database variable.
    - If again zero is encountered, clean the buffer & read string afterwards.
    - Else just append to intermediate buffer.
- Match it to the variable database.
- If it matches, then good. Otherwise display error.