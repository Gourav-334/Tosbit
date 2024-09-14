# utility_box

## 1. STRING APPEND:
- Move pointer to the base of last character.
- Make this base as offset of string to be appended.
- Insert the string right there.

## 2. CONSTANT STRING APPEND:
> Same as above but string to be appended is declared constant.

## 3. CHARACTER APPEND:
- Move pointer to the base of last character.
- Make this base as offset of character to be appended.
- Insert the character right there.

## 4. CONSTANT CHARACTER APPEND:
> Same as above but string to be appended is declared constant.

## 5. NEWLINE REMOVER:
- Check if the last character of the string is a newline character.
- If yes, move to the offset of last character.
- Remove the newline character.

## 6. FRONT CHARACTER REMOVER:
- Move to the offset of first character.
- Remove that first character.
- Move the pointer forward by 1 byte.

## 7. FLUSH STANDARD INPUT:
> Copied code.

## 8. BINARY PRINTER:
- Move to the offset of first character of string.
- Start reading each character one by one.
- Print **-** for each character.
- Print **$** for each newline character.

## 9. CHECK CHARACTER EXISTENCE IN ARRAY:
- Move to the first character of the array.
- Sequentially match each character to the elements.
