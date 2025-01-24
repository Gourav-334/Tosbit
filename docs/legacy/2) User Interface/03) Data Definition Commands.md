# 3\) DATA DEFINITION COMMANDS

## I\) Checking Basic Information:

### i. Checking all databases:
```
show all db;
```

### ii. Checking all tables (inside):
```
show all tables;
```

### iii. Show all tables (outside):
```
show all tables in Office;
```

### iii. Describe a table (inside):
```
show struct Desk;
```

### iv. Describe a table (outside):
```
show struct Desk in Office;
```


## II\) Creating database:
```
make db Office;
```

## III\) Using database:
```
open db Office;
```

## IV\) Dropping (deleting) database:

### i. While inside database:
```
delete db;
```

### ii. While outside database:
```
delete db Office;
```


## V\) Truncating (clearing) database:

### i. While inside database:
```
clear db;
```

### ii. While outside database:
```
clear db Office;
```

## VI\) Renaming database:

### i. While inside database:
```
rename db as Classroom;
```

### ii. While outside database:
```
rename db Office as Classroom;
```

## VII\) Exiting database:
```
exit db;
```

---

## VIII\) Creating table:
```
make table Desk [
    int Sno,
    string name,
    string dep
    ];
```


## IX\) Dropping (deleting) table:

```
delete table Desk;
```


## X\) Truncating (clearing) table:

```
clear table Desk;
```


## XI\) Renaming table:

### i. While inside database:
```
rename table Desk as Room;
```

### ii. While outdide databse:
```
rename table Desk in Office as Room;
```