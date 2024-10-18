# COMMINUTED ENCRYPTION `(CONFIDENTIAL)`


## **Introduction**

- A strong encryption technique.


## **Procedure**

### <u>Step 1</u>: Store decryption order indices order somewhere else

- Make an array which stores order of characters in a given string.
- They must be descendingly ordered according to their corresponding ASCII value.

---

### <u>Step 2</u>: Make prime mapped multiplication

- Multiply the prime numbers, to which the corresponding ASCII values of each string character is mapped with.

---

### <u>Step 3</u>: Write corresponding "small" alphabets

$$ 0 = a $$
$$ 1 = b $$
$$ 2 = c $$
$$ ... $$
$$ 9 = j $$

---

### <u>Step 4</u>: Arrange each index letter replaced with its next's next letter

- Replace each letter at each index continuously & linearly.
- Refer to example given below.

```
1. abcdef
2. cbadef
3. cdabef
4. cdebaf
5. cdefab
```

- Must be done until last index is exchanged, or the index reference crosses last element's index value.

---

### <u>Step 5</u>: Replace each alphabet with its corresponding (i-n)th alphabet

- 'i' is the particular alphabet's index position.
- 'n' is the string length.
- Each alphabet is replaced by its **(i-n)th**, meaning previous 'nth' alphabet from its own index position.
- The array of alphabets in this case must be circular.

---

### <u>Step 6</u>: Stuff (0-V) letters at even indices

- Stuff the elements in our decryption order index, which we made in starting at even indices.
- Maximum 32 characters can be recorded legally in Tosbit.

$$ char1 = 0 $$
$$ char2 = 1 $$
$$ char3 = 2 $$
$$ ... $$
$$ char10 = 9 $$
$$ char11 = A $$
$$ char12 = B $$
$$ char13 = C $$
$$ ... $$
$$ char32 = V $$

---

### <u>Step 7</u>: Re-arrange each index letter by replacing it with its next's next's next element.

- Now, for the current state of our string, we will replace each index element with the element next to it with step of **3**.
- Look at the example shown below.

```
1. heF89h2Bf32h
2. 8eFh9h2Bf32h
3. 89Fheh2Bf32h
4. 89hheF2Bf32h
5. 89h2eFhBf32h
6. 89h2BFhef32h
7. 89h2BfheF32h
8. 89h2Bf3eFh2h
9. 89h2Bf32Fheh
10. 89h2Bf32hheF
```

- Must be done until last index is exchanged, or the index reference crosses last element's index value.

---


## **Example**

### <u>Step 1</u>:

```
nick = cikn
3102   0123
```

- We are storing `3,1,0,2` as array elements in an array.

---

### <u>Step 2</u>:

```
nick = 43*23*5*31 = 4945
```

---

### <u>Step 3</u>:

```
4945 = ajde
```

---

### <u>Step 4</u>:

```
1. ajde
2. djae
3. deaj
```

---

### <u>Step 5</u>:

- In our case, string length is **4**.

```
ajde -> (backward by 4 steps) -> wfza
```

---

### <u>Step 6</u>:

```
wfza -> (stuffing) -> w3f1z0a1
```

---

### <u>Step 7</u>:

```
1. w3f1z0a1
2. 13fwz0a1
3. 1zfw30a1
4. 1z0w3fa1
5. 1z0a3fw1
6. 1z0a1fw3
```

- So, `1z0a1fw3` is our final encrypted product for string `nick`.

---
