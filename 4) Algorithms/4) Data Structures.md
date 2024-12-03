# Data Structures


## 0. Description:

- This documentation is regarding ***data_structures.h*** & ***data_structures.c***.
- Its purpose is to provide storage facilities in form of various data structures.


## 1. Queueing:

```
void Queue_queue(Queue *q, char str[]);
```

- If the number of nodes are zero:
    - Create a node.
    - Mark it as the starting point.
    - Mark it as the ending point.
    - Fill the user information.
- Else if the number of nodes are more than zero:
    - Create a node.
    - Mark it as the ending point.
    - Fill the user information.


## 2. Dequeueing:

```
void Queue_clear(Queue *q);
```

- Starting from first node.
- If number of nodes is zero:
    - Print "No nodes present" message.
- Else:
    - Until just one node is left:
        - Clear node.
        - Move to next node. 
    - Clear last node.


## 3. Getting Index:

```
int Queue_getIndex(Queue *q, char str[]);
```

- Keep a counter set to zero.
- Starting from first node.
- Until the input value isn't found:
    - Increment the counter by 1.
    - Compare the input value & node value.
    - Move to next node.
- Return the counter value.


## 4. Getting Value:

```
char *Queue_getValue(Queue *q, int index);
```

- Set a counter to zero.
- For given {input number} of times:
    - Move to next node.
    - Increment the counter.
- Return the index number of current node.


## 5. Peek Element:

```
void Queue_peek(Queue *q);
```

- If number of nodes is zero:
    - Print "No nodes present" message.
- Else:
    - Print current node details.


## 6. Print All Elements

```
void Queue_showAll(Queue *q);
```

- If number of nodes is zero:
    - Print "No nodes present" message.
- Else:
    - Until last node is not reached:
        - Print current node details.
        - Move to next node.
