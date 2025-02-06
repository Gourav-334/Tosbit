# FILE SYSTEM


## metadata.tosbit (Table)

```tosbit
10,10,6.
```

1. Length of largest attribute name (larger than 10)
2. Length of largest data type name (larger than 10)
3. Length of largest key type (larger than 6)


## details.tosbit

```tosbit
name............................,string,unique.,5.\n
age.............................,int...,regular,4.
```

1. Attribute name
2. Data type
3. Key type
4. Length of largest value in an attribute.


## metadata.tosbit (Data)

```tosbit
10
```

1. Length of largest database name (larger than 10).


## tables.tosbit

```tosbit
table1..........................\n
table2..........................
```

1. Table's name


## database.tosbit

```tosbit
db1.............................,6.\n
db2.............................,6.\n
mydb............................,11
```

1. Name of database
2. Name of its largest tables.


## metadata.tosbit (Database)

```tosbit
6 
```

1. Length of largest table.