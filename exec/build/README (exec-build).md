# $exec/build/$


- `CMakeFiles/` - Contains **build information** about the files we compile & link through **CMake**.
- `data/` - Storage place for database **data**.
- `logs/` - Stores **user logs** in a clusters in JSON format for easy searching.
- `users/` - Contains `user.tosbit` which stores **user credentials**.
- `cmake_install.cmake` - Used by **CMake** for file system operations on the requested executable related files.
- `CMakeCache.txt` - Stores **cache** produced during process run by **CMake**.
- `Makefile` - Again used by **CMake** for **automating** compile & built process.
- `engine` - Executable to use **local database** or interact with remote ***Tosbit*** databases directly.
- `server` - Executable to **run server** on a specific port passed as an argument.