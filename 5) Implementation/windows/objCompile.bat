echo "Compileing DATABASE OPERATIONS (.c)"
gcc -c database_operations.c -o database_operations.obj

echo "Compileing ENCRYPTER (.c)"
gcc -c encrypter.c -o encrypter.obj

echo "Compileing SYNTAX PARSER (.c)"
gcc -c syntax_parser.c -o syntax_parser.obj

echo "Compileing TRANSITION TOOL (.c)"
gcc -c transition_tool.c -o transition_tool.obj

echo "Compileing UTILITY BOX (.c)"
gcc -c utility_box.c -o utility_box.obj

echo "Compileing TEST (.c)"
gcc -c test.c -o test.obj
