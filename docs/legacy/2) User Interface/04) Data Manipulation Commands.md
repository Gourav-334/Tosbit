# 4\) DATA MANIPULATION COMMANDS

## I\) Inserting record:

```
insert into table Desk [
    1, Yuvraj, 25
];
```


## II\) Deleting record:

```
delete from table Desk where Sno=5;

delete from table Desk where Sno=1 & name="Yuvraj";

delete from table Desk where Sno=1 | name="Yuvraj";

@ Deletes first 'n' records with this @
delete 3 from table Desk where age=25;

@ Deletes first all records with this @
delete all from table Desk where age=25;
```

## III\) Updating record:

```
rename Sno in table Desk as Serial;
```
