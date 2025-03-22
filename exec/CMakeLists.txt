cmake_minimum_required(VERSION 3.28)
project(Tosbit C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


include_directories(/usr/include)
link_directories(/usr/lib)

add_executable(engine
    ../src/database_operations.c
    ../src/driver_manager.c
    ../src/encrypter.c
    ../src/engine.c
    ../src/profile_manager.c
    ../src/shell_piping.c
    ../src/syntax_parser.c
    ../src/transition_tool.c
    ../src/utility_box.c
    ../src/queue.c
)

target_link_libraries(engine PRIVATE readline ncurses)


add_executable(server
    ../src/database_operations.c
    ../src/encrypter.c
    ../src/queue.c
    ../src/server.c
    ../src/shell_piping.c
    ../src/syntax_parser.c
    ../src/transition_tool.c
    ../src/utility_box.c
)

target_link_libraries(server PRIVATE readline ncurses)