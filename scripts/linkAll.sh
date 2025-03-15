echo "Linking in process..."

gcc -g ../dist/database_operations.o ../dist/driver_manager.o ../dist/encrypter.o ../dist/engine.o ../dist/profile_manager.o ../dist/queue.o ../dist/shell_piping.o ../dist/syntax_parser.o ../dist/transition_tool.o ../dist/utility_box.o -o ../exec/build/engine
gcc -g ../dist/server.o -o ../exec/build/server

echo "All files linked."
