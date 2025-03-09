#!/bin/bash

echo "START OF COMPILATION"


echo "Compiling DATABASE OPERATIONS (.C)..."
gcc -g -c -I../include ../src/database_operations.c -o ../dist/database_operations.o

echo "Compiling ENCRYPTER (.C)..."
gcc -g -c -I../include ../src/encrypter.c -o ../dist/encrypter.o

echo "Compiling PROFILE MANAGER (.C)..."
gcc -g -c -I../include ../src/profile_manager.c -o ../dist/profile_manager.o

echo "Compiling SYNTAX PARSER (.C)..."
gcc -g -c -I../include ../src/syntax_parser.c -o ../dist/syntax_parser.o

echo "Compiling TRANSITION TOOL (.C)..."
gcc -g -c -I../include ../src/transition_tool.c -o ../dist/transition_tool.o

echo "Compiling UTILITY BOX (.C)..."
gcc -g -c -I../include ../src/utility_box.c -o ../dist/utility_box.o

echo "Compiling QUEUE (.C)..."
gcc -g -c -I../include ../src/queue.c -o ../dist/queue.o

echo "Compiling TEST (.C)"
gcc -g -c -I../include ../test/test.c -o ../dist/test.o

echo "Compiling CLIENT (.C)"
gcc -g -c -I../include ../src/client.c -o ../dist/client.o

echo "Compiling SERVER (.C)"
gcc -g -c -I../include ../src/server.c -o ../dist/server.o


echo "END OF COMPILATION"
