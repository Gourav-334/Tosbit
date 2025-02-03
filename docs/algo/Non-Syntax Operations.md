# NON-SYNTACTICAL OPERATIONS


## Record Log

1. Fetch & pipe current time to `time`.
2. Fetch & pipe current location to `loc`.
3. Open `data/logs.json` in `r+` mode.
4. If doesn't opens, then display appropriate message & stop the process.
5. Move `6` bytes back from EOF.
6. Read next byte forward.
7. If its `[`, insert `\n\t\t`.
8. Else for `{`, insert `,\n\n\t\t`.
9. Now insert `{\n\t\t\t"UTC": "{TIME}",\n\t\t\t"location": "{LOC}"\n\t\t\t"author": {USERNAME},\n\t\t\t"command": "{COMMAND}"\n\t\t}`.
10. Close all file descriptors.
