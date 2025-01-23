#!/bin/bash

echo "Compiling DATABASE OPERATIONS (.C)..."
gcc -g -c database_operations.c -o database_operations.o

echo "Compiling ENCRYPTER (.C)..."
gcc -g -c encrypter.c -o encrypter.o

echo "Compiling PROFILE MANAGER (.C)..."
gcc -g -c profile_manager.c -o profile_manager.o

echo "Compiling SYNTAX PARSER (.C)..."
gcc -g -c syntax_parser.c -o syntax_parser.o

echo "Compiling TRANSITION TOOL (.C)..."
gcc -g -c transition_tool.c -o transition_tool.o

echo "Compiling UTILITY BOX (.C)..."
gcc -g -c utility_box.c -o utility_box.o

echo "Compiling QUEUE (.C)..."
gcc -g -c queue.c -o queue.o

echo "Compiling TEST (.C)"
gcc -g -c test.c -o test.o


echo "All files compiled."
