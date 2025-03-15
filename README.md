# $\fbox{TOSBIT v0.1.0-beta}$


## **1. Introduction**

Hello dear contributors! I am ***Gourav Kumar Mallick*** - the author of this project. Tosbit aims at providing very **simple syntax grammar** for database commands, following **relational database** theory & design. Also there are some key features that we are trying to implement in it to keep the mommentum going & contributing with new ideas. Started it as a **hobby project** with excuse of college's minor project, but would really love to see it evolving with improvements. I invite all interested developers to freely discuss & contribute to this **open-source** project.


## **2. Features**

- Relational design
- Simple syntax grammar
- Media file storage facility
- CSV-like data storage
- High performance
- Lightweight nature
- Unambiguous parsing


## **3. Directory Structure**

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


## **4. Installation**

For installation, follow the given steps (assuming you to be in parent directory):

1. Install required tools for our database:
```sh
bash scripts/ubuntu.sh
```

2. Set up environment using CMake:
```sh
cd exec
bash remake.sh 0
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


## **5. In-Code Tosbit Usage**

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
gcc myfile.c -I../include -L../lib -ltosbitAPI -o myfile
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

This was a very basic tutorial on very painlessly using in-code **Tosbit** using GCC.


## **6. Personal Information**

For anyone willing to connect with me, I am more than happy to connect back.

- [Gmail](guduthestriker11@gmail.com)
- [LinkedIn](www.linkedin.com/in/gourav-kumar-mallick-272715250)
- [GitHub](https://github.com/Gourav-334) (lol, ofcourse)
