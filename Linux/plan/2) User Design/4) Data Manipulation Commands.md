# 4\) DATA MANIPULATION COMMANDS

## I\) Inserting record:

### i. Inserting into recently mentioned table:
```
insert into recent table [
    1, Yuvraj, 25
];
```

### ii. Inserting into table by mentioning:
```
insert into table Desk [
    1, Yuvraj, 25
];
```

## II\) Deleting record:

### i. Deleting from recently mentioned table:
```
delete from recent table where Sno<5;
delete from recent table where Sno=5;
delete from recent table where Sno>5;

delete from recent table where Sno=1 & name="Yuvraj";

delete from recent table where Sno=1 | name="Yuvraj";

@ Deletes first 'n' records with this @
delete 3 from recent table where age=25;

@ Deletes first all records with this @
delete all from recent table where age=25;
```

### ii. Deleting from table by mentioning:
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

### i. In recently mentioned table:
```
rename Sno in recent table as Serial;
```

### ii. By explicitly mentioning table:
```
rename Sno in table Desk as Serial;
```
