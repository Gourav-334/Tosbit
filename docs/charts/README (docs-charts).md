# $docs/charts/$

- `Attribute Parser.drawio` - The DFA for parsing everything within paranthesis while executing `MAKE TABLE tbl_name` (in `syntax_parser.c`).
- `Data Parser.drawio` - The DFA for parsing a data type as per its data type while executing `PUSH TO tbl_name(...)` (in `database_operations.c`).
- `Encrypter.drawio` - Stores flowchart for working of encrypter (`encrypter.c`).
- `Main Automaton.drawio` - The central DFA for each outermost command (in `syntax_parser.c`).
- `Nested DFA Parsers.drawio` - All small DFAs for nested parsing operations (in `database_operations.c`).
