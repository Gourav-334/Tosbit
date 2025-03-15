# SOCKETS



## Who Runs What?

### Introduction

- For offline version, client runs `engine.h`.
- For online version, client runs `client.h`.
- While servers only run `server.h`.


### engine.h

- `engine.h` is used for interacting with local file system of a client.
- This is done using the default configurations, a driver manager isn't required.


### client.c

- `client.h` is used for accessing a remote file system.
- A driver manager is required for this purpose.
- IP address is required to be passed along with other parameters.
- Then it is checked if the socket endpoint is there or not.
- Commands are made using `interpret()`.
- Whatever command are passed in `client.h` are sent to `server.h` at remote server.
- Then those commands are executed there.


### server.c

- `server.c` is always running actively on a remote server.
- It receives commands & executes them on local file system.
- For all form of feedbacks & requests, it writes back everything to the client.



## The Algorithm

### Macro-level:

1. Server fetches its local username and password & stores it.
2. Driver fetches its local username.
3. Driver sends its username, hostIP, hostUsername & hostPassword to the host.
4. Host checks if its username & password by client are correct.
5. If any mismatch is found, connection request is rejected. Else accepted.


## Server's request-response:

1. If user chooses 'y', engine sets connection, which calls client program.
2. Then client tells syntax parser that its not a local operation.
3. Client gets the `TOS>` style prompt.
4. Whatever command client enters, is sent to server through socket.
5. Server receives the command.
6. Server parses it locally & writes output to local and client terminal.


### Conditional socket print:

```
{database_operations.h} -> {syntax_parser.h} -> {server.c}
```

1. Make a global variable `serverMode` in `database_operations.c`.
2. Make a global limitless string variable `feedback` & its global size tracker `feedbackSize` in `database_operations.c`.
3. Also make a function `extendFeedback()` in `database_operations.c`.
4. At the start of `syntax_parser.c`, memset `feedback` if required & set `feedbackSize` to `0`.
5. Whenever `syntax_parser.c` is called, it checks if `serverConn` flag in `TRUE` or `FALSE` & sets `serverMode` to same.
6. All print functions are replaced with `extendFeedback()`. *
7. Print `feedback` at the end of `syntaxParser()`.
8. At `server.c`, send `feedback` in chunks of `1024` (client buffer size).


## Chunkifier

1. First send client that how many chunks you are going to send.
2. For that many times, server will write fragments of `feedback` to client.
3. And for that many times, client will read fragments of `feedback` by server.


## String Extender

```c
void extendFeedback(char message[]);
```

1. Extend `feedback` by string length of `message`.
2. Clean the newly extended part with `memset()`.
3. Increment `feedbackSize` by string length of `message`.
4. Append `message` at the end of `feedback`.


## User driver manager:

```
{client.h} -> {driver_manager.h} -> {program.c}
```

1. Explicitly tell `runClient()` that there is no database takeover to main program (breaks allowed).
2. Use a global flag for doing this job.
3. If this flag is ON, make the takeover by entering the endless loop.
4. Else if flag is OFF, skip the takeover & return from function.
5. When using `interpret()` function, it checks that flag & interprets the passed command.
6. User must close the socket for gracefully disconnecting from the server.


## File transfer through server:

- If running in offline mode, do the following.
- Prompt the user about the path.
