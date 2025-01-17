cmake_minimum_required(VERSION 3.28)
project(Tosbit C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(program
	test.c
	database_operations.c
	encrypter.c
	profile_manager.c
	syntax_parser.c
	transition_tool.c
	utility_box.c
)

