# 5\) DATA CONTROL COMMANDS

## I\) Granting access:

### i. On database:
```
@ Control over reading @
grant user1 r control over database Office;

@ Control over writing @
grant user1 w control over database Office;
```

### ii. On table:
```
@ Control over reading @
grant user1 r control over table Desk in database Office;

@ Control over writing @
grant user1 w control over table Desk in database Office;
```

## II\) Revoking access:

### i. On database:
```
snatch control from user1 over database Office;
```

### ii. On table:
```
snatch control from user1 over table Desk in database Office;
```
