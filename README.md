# TOSBIT v0.1.1-beta


## **1. Introduction**

Hello contributors! I am the author of project Tosbit, which aims at providing very **simple syntax grammar** for database commands, following **relational database** theory & design. Also there are some key features that we are trying to implement in it to keep the mommentum going & contributing with new ideas. Started it as a **hobby project** with excuse of college's minor project, but would really love to see it evolving with improvements. I invite all interested developers to freely discuss & contribute to this **open-source** project.


## **2. Features**

- Relational design
- Simple syntax grammar
- Precise error messages
- Media file storage facility
- CSV-like data storage
- High performance
- Lightweight nature
- Unambiguous parsing


## **3. System Requirements**

- **Architecture (existing):** x86, x86_64
- **Architecture (*coming soon...*):** RISC-V, ARM-Cortex (M/R/A)
- **Platform:** Any Linux distro
- **RAM:** A few megabytes
- **Space:** A few megabytes


## **4. Directory Structure**

- `assets/` - Contains media files & images for testing purpose.
- `dist/` - Contains object (`.o`) files as result of intermediate compilation.
- `docs/` - Contains brief documentation files.
- `exec/` - Contains makefiles, application directories & executables.
- `include/` - Contains header (`.h`) files for all the used source code files.
- `lib/` - Contains all the statically linked libraries/APIs.
- `scripts/` - Contains Bash scripts for automation.
- `src/` - Contains all the source code (`.c`) files.
- `test/` - Contains source files which were used in unit testing of components.

>**<u>NOTE</u>:** Most directories & nested directories contain their own ***README*** files for more information regarding their contained directories.


## **5. Installation**

### <u>For Release Users</u>

These installation steps are for those who are willing to download the release:

1. Get the `.tar.gz` file from **GitHub**.

```sh
wget https://github.com/Gourav-334/Tosbit/releases/download/Tosbit-v0.1.1/Tosbit-v0.1.1-Linux.tar.gz
```

2. Extract this `.tar.gz` file.

```sh
tar -xzvf Tosbit-v0.1.1-Linux.tar.gz
```

3. Allow permission to it.

```sh
chmod +x Tosbit-v0.1.1-Linux/*
```

4. Navigate inside the directory.

```sh
cd Tosbit-v0.1.1-Linux
```

5. Try running engine or server.

```sh
./engine
./server 8080           # Create account in engine first before running server.
```


### <u>For Developers</u>

For installation by developers having cloned the repository, follow the given steps (assuming you to be in parent directory of repository):


1. Install required tools for our database:
```sh
bash scripts/alpinelinux.sh         # Only for Alpine Linux.
bash scripts/arch.sh                # Only for Arch, Manjero & EndeavourOS.
bash scripts/fedora.sh              # Only for Fedora, RHEL, Rocky & AlmaLinux.
bash scripts/opensuse.sh            # Only for openSUSE.
bash scripts/ubuntu.sh              # Only for Debian & Ubuntu.
bash scripts/voidlinux.sh           # Only for Void Linux.
```

2. Set up environment using CMake:
```sh
cd exec
mkdir build
bash remake.sh 1
cd build
cmake ..
make
cd ../..
```

$$ OR $$

2. Alternatively (but discouraged), use Bash scripts for compilation & linking:

```sh
cd scripts
bash compileAll.sh
bash linkAll.sh
cd ..
```

3. ***(Optional)*** Run the server component with an argument telling what port to run it on:

```sh
cd exec/build
./server 8080
cd ../..
```

4. Try running Tosbit engine now:

```sh
cd exec/build
./engine
cd ../..
```


## **6. In-Code Tosbit Usage**

Follow the given steps for using in-code Tosbit in C:

1. Navigate to `exec/build/` & create a C source (`.c`) file:

```sh
cd exec/build
touch myfile.c
```

2. Open this file with your favorite code editor, I would be using **GNU Nano**:

```sh
nano myfile.c
```


3. Write the following code in it:

```c
#include "../../include/driver_manager.h"

int main(void)
{
    /* Enter 'Username', 'Password' & 'Hostname' as per your entered credentials. */

    setConnection("Username", "Password", "Hostname", 8080, "Username", "Password", FALSE);

    interpret("SHOW ALL DB");
    interpret("MAKE DB mydb");
    interpret("SHOW ALL DB");

    endConnection();

    return 0;
}
```

4. Link against `tosbitAPI.a` static library:

```sh
gcc myfile.c \
-I/usr/include -I/usr/include/readline -I../../include \
-L/usr/lib/x86_64-linux-gnu -L../../lib \
-ltosbitAPI -lreadline -lhistory -lncurses \
-o myfile
```

5. Run the server:

```sh
./server 8080
```

>**<u>NOTE</u>:** If it doesn't work, try changing port number argument here & in code too.

6. Run the created executable:

```sh
./myfile
```

- This was a very basic tutorial on very painlessly using in-code **Tosbit** using GCC.
- Also the linking stage we went through (*step 4*) was considering the user to be at `exec/build/` of repository.
- One must know how to link libraries using **GCC** to link `libtosbitAPI.a` present at `lib/`.
- And there is no worry of space in **embedded systems** regarding it, because linking is just a one time process.


### 7. <u>File System</u>

- `data/`
    - `db_name/`
    - `tbl_name/`
        - `details.tosbit`
        - `rows.tosbit`
        - `metadata.tosbit`
    - `tables.tosbit`
    - `metadata.tosbit`
- `databases.tosbit`
- `metadata.tosbit`
- `logs/`
- `users/`
    - `user.tosbit`

>**<u>NOTE</u>:** Dots (`.`) in code sections below are spaces, added for clarity.

### 1.1 `details.tosbit` (`data/db_name/tbl_name/`)

```tosbit
name............................,string,unique.,5.\n
age.............................,int...,regular,4.
```
1. Attribute name
2. Data type
3. Key type
4. Length of largest value in an attribute.

### 1.2 `metadata.tosbit` (`data/db_name/tbl_name/`)

```tosbit
10,10,6.
```
1. Length of largest attribute name (larger than 10)
2. Length of largest data type name (larger than 10)
3. Length of largest key type (larger than 6)

### 1.3 `tables.tosbit` (`data/db_name/`)

```tosbit
table1..........................\n
table2..........................
```
1. Table's name

### 1.4 `metadata.tosbit` (`data/db_name/`)

```tosbit
6.
```
1. Length of largest table.

### 1.5 `database.tosbit` (`data/`)

```tosbit
db1.............................\n
db2.............................\n
mydb............................
```
1. Name of database
2. Name of its largest tables.

### 1.6 `metadata.tosbit` (`data/`)

```tosbit
10
```
1. Length of largest database name (larger than 10).

### 1.7 `logs/`

- `logs/` directory contains all the log history in **JSON** format.
- These are easy to access in the local file system.

### 1.8 `user.tosbit` (`users/`)

- `user/tosbit` contains all the user credential in encrypted form.


## **8. Personal Information**

For anyone willing to connect with me, I am more than happy to connect back.

- [Gmail](guduthestriker11@gmail.com)
- [LinkedIn](www.linkedin.com/in/gourav-kumar-mallick-272715250)
- [GitHub](https://github.com/Gourav-334) (lol, ofcourse)

---