# SYNTAXES IN ORDER (v2.0.0)


## Commands

```
set Sno in Desk as unique_key
set Sno in Desk as regular_key

rename Sno in Desk as Serial

show column Name from Desk
show column Name,Dep from Desk
show rows from Desk where age<25
show rows from Desk where age=25
show rows from Desk where age>25

join Sno from Desk & Name from Class
join Sno,Name from Desk & Name from Class

rename table Desk as room
rename table Desk in Office as room
rename db as Classroom
rename db Office as Classroom

r+ user1 over db Office
w+ user1 over db Office
r- user1 over db Office
w- user1 over db Office

r+ user1 over Desk in db Office
w+ user1 over Desk in db Office
r- user1 over Desk in db Office
w- user1 over Desk in db Office

add to stash
reverse stash
commit stash
rollback by 2
show log
show last 4 log

make Exam from json at "path//to//file//filename.json"
make json at "path//to//file//filename.json" from Exam
make Exam from md at "path//to//file//filename.md"
make md at "path//to//file//filename.md" from Exam
```


## Details

$$ Total\;commands\;=\;32 $$
$$ Total\;categories\;=\;9 $$