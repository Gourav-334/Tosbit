# COMMAND BATCH


## Algorithm

1. Start reading passed target file from start.
2. Read until an EOF appears.
3. Keep storing each byte until a `\n` or EOF appears.
4. Now pass this command to syntax parser to execute.
5. After execution, proceed with next line.


## Outlook

- A function which takes file's path as input.
- Opens it and performs the algorithms using syntax parser.