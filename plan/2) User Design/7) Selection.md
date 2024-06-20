# 7\) SELECTION

## I\) Selecting all:

### i. Recent table:
```
show all from recent table;
```

### ii. Explicitly mentioned table:
```
show all from table Desk;
```

## II\) Column selection:

### i. Recent table:
```
show column Name from recent table;
show column Name,Dep from recent table;
```

### ii. Explicitly mentioned table:
```
show column Name from table Desk;
show column Name,Dep from table Desk;
```

## III\) Conditional selection:

### i. Recent table:
```
show rows recent table where age<25;
show rows recent table where age=25;
show rows recent table where age>25;
```

### ii. Explicitly mentioned table:
```
show rows table Desk where age<25;
show rows table Desk where age=25;
show rows table Desk where age>25;
```
