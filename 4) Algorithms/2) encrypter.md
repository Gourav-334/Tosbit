# encrypter

## 1. STRING ENCRYPTION:
- Move cursor to the ith character of the input.
- Search for the mapped index of the character in array.
- Append the code to the output string.
- Add 0.
- Repeat until all the characters are done.

## 2. STRING DECRYPTION:
- Move cursor to the first character/ character after 0.
- Keep appending it to buffer until 0 arrives.
- When 0 arrives, read which character is mapped with the code in buffer.
- Append the character to output string.
- Repeat until end of file reaches.

## 3. FINDING MAPPED KEY:
- Take the input string.
- Match it one-by-one with with element in code array.
- Keep increasing value of variable 'i' if it doesn't match.
- Return element at index 'i' to the function.
