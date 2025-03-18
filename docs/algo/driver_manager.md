# DRIVER MANAGER


## 0. Description

- These algorithms are written with regards of `driver_manager.h` & `driver_manager.c`.
- The purpose of driver manager in ***Tosbit*** is to provide effortless client-server connection to users.
- It uses **BSD Sockets** for this purpose with its support for `epoll()` to handle multiple clients with multi-threading level performance.


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


## 4. `runClient()`

### **4.1 Introduction:**
```c
void runClient(char username[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[], int takeover);
```
- It activates socket to run a client on it.
- `username` is client's username.
- `hostIP` is IP address of server (if remote) or host name (if local).
- `port` is the port number where server is running.
- `hostUsername` is the host's username.
- `hostPassword` is the host's password.
- `takeover` tells if user wants to takeover the terminal which database command interpreter.

### **4.2 Algorithm:**
1. Set `interpretLoop` to user's preference of `takeover`.
2. Set socket file descriptor for client.
3. Get host's IP address.
4. Configure the server's properties.
5. If everything so far was successful, connect client socket to the server socket.
6. Send server the `username`, `hostUsername` & `hostPassword`.
7. Run the request-response (read-write) loop.
8. In this loop, send the command to server as it is.


## 5. `setConnection()`

### **5.1 Introduction:**
```c
void setConnection(char username[], char password[], char hostIP[], short unsigned int port, char hostUsername[], char hostPassword[], int takeover);
```
- It activates socket to run a client on it.
- `username` is client's username.
- `password` is client's password (for verification).
- `hostIP` is IP address of server (if remote) or host name (if local).
- `port` is the port number where server is running.
- `hostUsername` is the host's username.
- `hostPassword` is the host's password.
- `takeover` tells if user wants to takeover the terminal which database command interpreter.

### **5.2 Algorithm:**
1. Open `users/user.tosbit` in `r` mode.
2. Check if file is there or not.
3. If not, throw the error to user.
4. Else if its there, keep reading characters from `user.tosbit` to `codedUsername` until a `\n` is read.
5. Then read characters after `\n` until end of file to `codedPassword`.
6. Now match the passed username & password to decrypted `codedUsername` & `codedPassword`.


## 6. `interpret()`

### **6.1 Introduction:**
```c
void interpret(char *user_cmd);
```
- This function is used for passing commands to database through driver manager.
- Its used for passing them to server, whether local or remote.
- `user_cmd` is the command passed by user.

### **6.2 Algorithm:**
1. Write user's command to socket.
2. Read the feedback sent by server to socket after remote execution.
3. Display that feedback to client's screen.


## 7. `endConnection()`

```c
void endConnection();
```
- Closes the socket descriptor geacefully.

---
