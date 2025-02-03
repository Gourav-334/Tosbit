cmake_minimum_required(VERSION 3.28)
project(Tosbit C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(program
	../src/engine.c
	../src/database_operations.c
	../src/driver_manager.c
	../src/encrypter.c
	../src/profile_manager.c
	../src/shell_piping.c
	../src/syntax_parser.c
	../src/transition_tool.c
	../src/utility_box.c
	../src/queue.c
)
