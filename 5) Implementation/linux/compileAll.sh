#!/bin/bash

echo "Compiling DATABASE OPERATIONS (.C)..."
gcc -c database_operations.c -o database_operations.o

echo "Compiling ENCRYPTER (.C)..."
gcc -c encrypter.c -o encrypter.o

echo "Compiling PROFILE MANAGER (.C)..."
gcc -c profile_manager.c -o profile_manager.o

echo "Compiling SYNTAX PARSER (.C)..."
gcc -c syntax_parser.c -o syntax_parser.o

echo "Compiling TRANSITION TOOL (.C)..."
gcc -c transition_tool.c -o transition_tool.o

echo "Compiling UTILITY BOX (.C)..."
gcc -c utility_box.c -o utility_box.o

