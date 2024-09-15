```
@ This is a comment (total 58 commands!) @

open db Office;

show Desk struct;
show Desk struct in Office;

show all db;

make table Desk [
    int Sno,
    string name,
    string dep
];

set Sno in Desk as unique_key;
set Sno in Desk as regular_key;

insert into table Desk [
    1, Yuvraj, 25
];

delete from table Desk where Sno=5;
delete from table Desk where Sno=5 & name="Yuvraj";
delete from table Desk where Sno=5 | name="Yuvraj";

show all from table Desk;
show column Name from Desk;
show column Name,Dep from Desk;
show rows from Desk where age<25;
show rows from Desk where age=25;
show rows from Desk where age>25;

rename Sno in Desk as Serial;

show all tables;
show all tables in Office;

join Sno from Desk & Name from Class;
join Sno,Name from Desk & Name from Class;

rename table Desk as room;
rename table Desk in Office as room;
rename db as Classroom;
rename db Office as Classroom;

clear table Desk;
clear db;
clear db Office;

delete table Desk;

delete db;
delete db Office;

exit db;

r+ user1 over db Office;
w+ user1 over db Office;
r- user1 over db Office;
w- user1 over db Office;

r+ user1 over Desk in db Office;
w+ user1 over Desk in db Office;
r- user1 over Desk in db Office;
w- user1 over Desk in db Office;

add to stash;
reverse stash;
commit stash;
rollback by 2;
show log;
show last 4 log;

make Exam from json at "path//to//file//filename.json";
make json at "path//to//file//filename.json" from Exam;
make Exam from md at "path//to//file//filename.md";
make md at "path//to//file//filename.md" from Exam;

create new account;
switch account to user2;
change account password;
delete account;

Enter details in password#username format to confirm:
abc123#my_account
```