echo "Linking in process..."

gcc -g database_operations.o encrypter.o profile_manager.o syntax_parser.o transition_tool.o utility_box.o test.c -o program

echo "Linked all files."
