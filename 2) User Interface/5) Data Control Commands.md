# 5\) DATA CONTROL COMMANDS

## I\) Granting access:

### i. On database:
```
@ Control over reading @
r+ user1 over db Office;

@ Control over writing @
w+ user1 over db Office;
```

### ii. On table:
```
@ Control over reading @
r+ user1 over Desk in db Office;

@ Control over writing @
w+ user1 over Desk in db Office;
```


## II\) Revoking access:

### i. On database:
```
@ Control over reading @
r- user1 over db Office;

@ Control over writing @
w- user1 over db Office;
```

### ii. On table:
```
@ Control over reading @
r- user1 over Desk in db Office;

@ Control over writing @
w- user1 over Desk in db Office;
```
