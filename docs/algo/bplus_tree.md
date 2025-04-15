# B+ TREE


## 1. `bPlusTree_insert()`

### **1.1 Introduction:**
```c
void BPlusTree_insert(BPlusTree *bPlusTree, char str[]);
```
- This function is used for inserting elements to a B+ tree.
- Each node is basically a list of three elements & other pointers.
- `bPlusTree` is the pointer to B+ tree.
- `str` is string value to B+ tree.

### **1.2 Algorithm:**
- If no node is there, allocate memory for one & initialize the first element at 0th index.
- Else if atleast one node is present, compare element to 0th indexed element in root node.
- Starting comparison from root's 0th element, keep sending it left until left isn't bigger than inserting element, or leaf isn't reached. ---(1)
- When such a node is reached, insert the element there. ---(1)
- If the node has all the three indices filled & its a leaf node, scatter the elements. ---(1)
- Scatter by first bringing the middle element to 0th index. ---(2)
- Form left node with shortest value at its 0th index. ---(2)
- Form right node with largest value at its 0th index. ---(2)