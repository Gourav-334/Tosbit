# QUEUE


## 0. Description:

- This documentation is regarding ***data_structures.h*** & ***data_structures.c***.
- Its purpose is to provide storage facilities in form of various data structures.


## 1. `Queue_queue()`

### **1.1 Introduction:**
```c
void Queue_queue(Queue *q, char str[]);
```
- This function is used for **enqueueing** a value to queue.
- This queue is actually a linked list, storing the nodes dynamically.
- `q` is the address to the queue.
- `str` is the string value to enqueue.

### **1.2 Algorithm:**
1. If the number of nodes are zero, then do the following.
2. Create a node. ---(1)
3. Mark it as the starting point. ---(1)
4. Mark it as the ending point. ---(1)
5. Fill the user information. ---(1)
6. Else if the number of nodes are more than zero, then do the following.
7. Create a node. ---(2)
8. Mark it as the ending point. ---(2)
9. Fill the user information. ---(2)


## 2. `Queue_clear`

### **2.1 Introduction:**
```c
void Queue_clear(Queue *q);
```
- Used for freeing whole queue from memory.
- `*q` is the address to the queue (in following functions too).

### **2.2 Algorithm:**
1. Starting from first node.
2. If number of nodes is zero, print "No nodes present" message.
3. Else, do the following.
4. Until just one node is left. ---(1)
5. Clear node. ---(2)
6. Move to next node. ---(2)
7. Clear last node. ---(1)


## 3. `Queue_getIndex()`

### **3.1 Introduction:**
```c
int Queue_getIndex(Queue *q, char str[]);
```
- Used for searching & getting index for a passed value.
- `str` is the value to search for.

### **3.2 Algorithm:**
1. If the queue is empty, return `-2`.
2. Else start from $0th$ position i.e. index `0`.
3. Find the node by comparing the user input string with current node's value.
4. Travel to next node if they don't match & next node's value is not `NULL`.
5. Compare the last node in case none other matched.
6. If this one also doesn't match, return `-1`.
7. Initialize everything to normal state.


## 4. `Queue_getValue()`

### **4.1 Introduction:**
```c
char *Queue_getValue(Queue *q, int index);
```
- Used for getting a value at given index.
- `index` is the index to fetch a value from.

### **4.2 Algorithm:**
1. If the passed index is less than the corresponding total elements, then return string `NULL`.
2. Else traverse to the target node.
3. Get the value.


## 5. `Queue_peek()`

### **5.1 Introduction:**
```c
void Queue_peek(Queue *q);
```
- Peeks/gets the value at last node.

### **5.2 Algorithm:**
1. Get the value at that node using `temp` pointer there.


## 6. `Queue_showAll()`

### **6.1 Introduction:**
```c
void Queue_showAll(Queue *q);
```
- Prints all the elements in queue in sequence.

### **6.2 Algorithm:**
1. If number of nodes is zero:
2. Print "No nodes present" message.
3. Else, until last node is not reached, do the following.
4. Print current node details.
5. Move to next node.


## 7. `Queue_changeAt()`

### **7.1 Introduction:**
```c
void Queue_changeAt(Queue *q, int index, char str[]);
```
- Used for modifying value at a certain node.
- `index` is the index where we want to modify the value.
- `str` is the new value we want to replace old value with.

### **7.2 Algorithm:**
1. Traverse to the target node.
2. Erase the current value.
3. Paste new value to it.
4. Initialize everything to normal state.

---