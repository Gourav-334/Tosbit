# 3\) DATA DEFINITION COMMANDS

## I\) Checking Basic Information:

### i. Checking all databases:
```
show all databases;
```

### ii. Checking all tables:
```
show all tables in Office;
```

### iii. Describe a table:
```
show Desk structure in database Office;
```


## II\) Creating database:
```
make database Office;
```

## III\) Using database:
```
open database Office;
```

## IV\) Dropping (deleting) database:

### i. While inside database:
```
delete this database;
```

### i. While outside database:
```
delete database Office;
```

## V\) Truncating (clearing) database:

### i. While inside database:
```
clear this database;
```

### ii. While outside database:
```
clear database Office;
```

## VI\) Renaming database:

### i. While inside database:
```
rename this database as Classroom;
```

### ii. While outside database:
```
rename database Office as Classroom;
```

## VII\) Exiting database:
```
exit database;
```

---

## VIII\) Creating table:
```
make table Desk columns [
    int Sno,
    string name,
    string dep
    ];
```

## IX\) Dropping (deleting) table:

### i. Dropping recently used referred table:
```
delete recent table;
```

### ii. Dropping table by mentioning:
```
delete table Desk;
```

## X\) Truncating (clearing) table:

### i. Truncating recently used referred table:
```
clear recent table;
```

### ii. Truncating table by mentioning:
```
clear table Desk;
```

## XI\) Renaming database:

### i. While inside database:
```
rename recent table as Room;
```

### ii. While outside database:
```
rename table Desk as Room;
```
