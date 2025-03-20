# FILE SYSTEM

>**<u>NOTE</u>:** Dots (`.`) in code sections below are spaces, added for clarity.



## File System Hierarchy

- `data/`
    - `db_name/`
    - `tbl_name/`
        - `details.tosbit`
        - `rows.tosbit`
        - `metadata.tosbit`
    - `tables.tosbit`
    - `metadata.tosbit`
- `databases.tosbit`
- `metadata.tosbit`
- `logs/`
- `users/`
    - `user.tosbit`

### 1. `details.tosbit` (`data/db_name/tbl_name/`)

```tosbit
name............................,string,unique.,5.\n
age.............................,int...,regular,4.
```
1. Attribute name
2. Data type
3. Key type
4. Length of largest value in an attribute.

### 2. `metadata.tosbit` (`data/db_name/tbl_name/`)

```tosbit
10,10,6.
```
1. Length of largest attribute name (larger than 10)
2. Length of largest data type name (larger than 10)
3. Length of largest key type (larger than 6)

### 3. `tables.tosbit` (`data/db_name/`)

```tosbit
table1..........................\n
table2..........................
```
1. Table's name

### 4. `metadata.tosbit` (`data/db_name/`)

```tosbit
6 
```
1. Length of largest table.

### 5. `database.tosbit` (`data/`)

```tosbit
db1.............................\n
db2.............................\n
mydb............................
```
1. Name of database
2. Name of its largest tables.

### 6. `metadata.tosbit` (`data/`)

```tosbit
10
```
1. Length of largest database name (larger than 10).

#### 7. `logs/`

- `logs/` directory contains all the log history in **JSON** format.
- These are easy to access in the local file system.

#### 8. `user.tosbit` (`users/`)

- `user/tosbit` contains all the user credential in encrypted form.

---