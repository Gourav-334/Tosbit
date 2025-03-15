# $src/$


- `database_operations.c` - Contains functions written to run various **operations** on the database. Also includes some **secondary DFA** parsers.
- `driver_manager.c` - Contains socket codes for connecting to a remote server or even local one through C programs.
- `encrypter.c` - Applies simple encryption when storing sensitive data & also decrypts when retrieving them.
- `engine.c` - Central program to assemble rest of the components on it & run the final executable.
- `profile_manager.c` - Managers entered user credentials & verification of it.
- `queue.c` - Provides interface to make object-styled structure instances for queues.
- `server.c` - Contains socket codes for server to handle client request & execute its commands.
- `shell_piping.c` - Contains functions which retrieve information from shell.
- `syntax_parser.c` - Primary Determistic Finite Automaton to parse user command.
- `transition_tool.c` - Provides functionalities for working with DFA-based parsers as in `syntax_parser.c`.
- `utility_box.c` - Provides basic utility functions, mostly related to strings.
