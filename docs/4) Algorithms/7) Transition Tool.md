# TRANSITION TOOL



## 0. Description:

- This documentation is regarding ***transition_tool.h*** & ***transition_tool.c***.
- Its purpose is to provide storage facilities in form of various data structures.


## 1. Change State:

```
int changeState(char input, char symbols[], char transition[], int *state);
```

- Receive the `input` and `state`.
- Go through each character in `symbols`.
- When the character matches `input`, take note of its index number.
- Now traverse through array `transition`.
- Count the coma when they appear & keep reading until the number of commas is same as the index number of `input` in `symbols`.
- When they are equal, keep storing each character in another array `str` until another coma appears.
- When coma appears, set value of `state` as that.
