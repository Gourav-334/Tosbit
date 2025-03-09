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

1. Server fetches password & stores it decrypted in as a variable.
2. Driver verifies the username at local file-system.
3. Immeditately when connection is established to server, client sends the password to server.
4. Server verifies it as per its local file system.
5. If the verification is successful, the connection is continued to exist, else disconnected.
6. After connection is established successfully, server receives commands to buffers & executes them on local file-system.
