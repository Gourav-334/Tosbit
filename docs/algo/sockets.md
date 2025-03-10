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
