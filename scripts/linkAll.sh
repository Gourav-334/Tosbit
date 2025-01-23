echo "Linking in process..."

gcc -g ../dist/database_operations.o ../dist/encrypter.o ../dist/profile_manager.o ../dist/queue.o ../dist/syntax_parser.o ../dist/transition_tool.o ../dist/utility_box.o ../test/test.c -o ../exec/build/program

echo "All files linked."
