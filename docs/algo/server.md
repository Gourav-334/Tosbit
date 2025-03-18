# SERVER


## 0. Description

- This file is regarding `server.c` source file.
- It serves as a command receiver & executer on server-side database.


## 1. `error()`

```c
void error(const char *msg);
```
- Prints both `perror()` based error & exits.
- `msg` is the error tag message by developer.


## 2. `readMessage()`

### **2.1 Introduction:**
```c
int readMessage(int *sockFD, char *buffer, size_t size);
```
- Read a message until `\t` is received as a byte in stream.
- `sockFD` is the address to socket file descriptor.
- `buffer` is the buffer to read byte stream in.
- `size` is the size of buffer (used for emptying it).

### **2.2 Algorithm:**
1. Empty the `buffer`.
2. Read `1` byte at first & know what `read()` returns.
3. If it returns `0` i.e. unable to write, return.
4. Else allow the stream until a `\t` is read.


## 3. `writeMessage()`

### **3.1 Introduction:**
```c
int writeMessage(int *sockFD, char message[]);
```
- Writes a message to socket descriptor with an extra `\t`.
- `sockFD` is the address of socket descriptor we want to write to.
- `message` is the message we are writing to socket.

### **3.2 Algorithm:**
1. Write the message to socket.
2. If `write()` returns error, return from the function.
3. Else if it was successful, write `\t` to same socket.


## 4. `main()`

### **4.1 Introduction:**
```c
int main(int argc, char *argv[]);
```
- The entry point for it to run on terminal, as all the **C** programs.
- `argc` is the count of total arguments passed when running the executable for engine.
- `argv` is the array of all those passed arguments.

### **4.2 Algorithm:**
1. Create structures to configure server & epoll event settings.
2. Open `users/user.tosbit` in `r` mode.
3. Check if file is there or not.
4. If not, throw the error to user.
5. Else if its there, keep reading characters from `user.tosbit` to `codedUsername` until a `\n` is read.
6. Then read characters after `\n` until end of file to `codedPassword`.
7. Now match the passed username & password to decrypted `codedUsername` & `codedPassword`.
8. Check if a port number was passed in argument or not & handle error accordingly.
9. Establish a socket file descriptor (to non-blocking mode).
10. Configure the structures & bind the socket.
11. Listen to connections.
12. Create one epoll instance.
13. Open an infinite loop & do the following.
14. Put extra requests on wait for epoll connection.
15. If max number of connections isn't reached, accept the request (if any).
16. And set this request to non-blocking mode too. ---(1)
17. Receive `guestUsername`, `localUsername` & `localPassword`. ---(1)
18. Decrypt the fetched `username` and `password` & match them to what's passed by client. ---(1)
19. Else if receiving something from existing connection, do the following.
20. Clean the message receiving buffer. ---(1)
21. Receive message to that buffer. ---(1)
22. Call syntax parser with same command passed. ---(1)
23. Write back the output to client. ---(1)
24. Repeat step 14-23 (on loop).

---
