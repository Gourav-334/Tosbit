# data_structures

### Queue.queueing

- If the number of nodes are zero:
    - Create a node.
    - Mark it as the starting point.
    - Mark it as the ending point.
    - Fill the user information.
- Else if the number of nodes are more than zero:
    - Create a node.
    - Mark it as the ending point.
    - Fill the user information.


### Queue.clear

- Starting from first node.
- If number of nodes is zero:
    - Print "No nodes present" message.
- Else:
    - Until just one node is left:
        - Clear node.
        - Move to next node. 
    - Clear last node.


### Queue.getIndex

- Keep a counter set to zero.
- Starting from first node.
- Until the input value isn't found:
    - Increment the counter by 1.
    - Compare the input value & node value.
    - Move to next node.
- Return the counter value.


### Queue.getValue

- Set a counter to zero.
- For given {input number} of times:
    - Move to next node.
    - Increment the counter.
- Return the index number of current node.


### Queue.peek

- If number of nodes is zero:
    - Print "No nodes present" message.
- Else:
    - Print current node details.


### Queue.printAll

- If number of nodes is zero:
    - Print "No nodes present" message.
- Else:
    - Until last node is not reached:
        - Print current node details.
        - Move to next node.
