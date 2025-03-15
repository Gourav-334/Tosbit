# $exec/build/data/$

- `databases.tosbit` - Contains names of databases separated by newline character & deleted databases have tabspace as their first character.
- `metadata.tosbit` - Contains metadata which here is just the size of largest database name, or `9` by default for `Databases` as header when printed.
- Rest of the folders if you see, are by the name of the database & contain three kind of files which are `details.tosbit`, `metadata.tosbit` & `rows.tosbit`.
- `details.tosbit` there contains details like name of attributes, their data type, key & their largest value size separated by commas.
- `metadata.tosbit` contains 3 information separated by commas, which are largest attribute name, largest data type name & largest key name.
- `rows.tosbit` contains all the row data all-in-one file for now.