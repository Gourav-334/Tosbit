echo "Linking in process..."

gcc -g ../dist/database_operations.o ../dist/encrypter.o ../dist/profile_manager.o ../dist/queue.o ../dist/syntax_parser.o ../dist/transition_tool.o ../dist/utility_box.o ../test/test.o -o ../exec/build/engine
gcc -g ../dist/client.o -o ../exec/build/client
gcc -g ../dist/server.o -o ../exec/build/server

echo "All files linked."
