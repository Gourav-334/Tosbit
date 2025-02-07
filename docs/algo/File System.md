# FILE SYSTEM



## File System Hierarchy

- data/
- db_name/

- tbl_name/
- details.tosbit	{checkTableExistence(), tableStructure(), makeTable(), deleteTable(), clearTable(), pushRow()}
- rows.tosbit		{makeTable(), deleteTable(), clearTable(), pushRow()}
- metadata.tosbit	{tableStructure(), makeTable(), deleteTable()}

- tables.tosbit		{checkDbExistence(), allTables(), makeTable(), makeDb(), deleteDb(), clearDb()}
- metadata.tosbit	{allTables(), makeTable(), makeDb(), deleteDb(), clearDb()}

- databases.tosbit	{allDatabases(), makeDb()}
- metadata.tosbit	{allDatabases(), makeDb()}



## tbl_name/

### details.tosbit

```tosbit
name............................,string,unique.,5.\n
age.............................,int...,regular,4.
```

1. Attribute name
2. Data type
3. Key type
4. Length of largest value in an attribute.


### metadata.tosbit

```tosbit
10,10,6.
```

1. Length of largest attribute name (larger than 10)
2. Length of largest data type name (larger than 10)
3. Length of largest key type (larger than 6)



## db_name/

### tables.tosbit

```tosbit
table1..........................\n
table2..........................
```

1. Table's name


### metadata.tosbit (Database)

```tosbit
6 
```

1. Length of largest table.



## data/

### database.tosbit

```tosbit
db1.............................\n
db2.............................\n
mydb............................
```

1. Name of database
2. Name of its largest tables.


## metadata.tosbit (Data)

```tosbit
10
```

1. Length of largest database name (larger than 10).
