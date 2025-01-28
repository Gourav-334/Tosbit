const DatabaseClient = require('./database-client');
const readline = require('readline');

const TEAM_LEAD_SERVER = 'http://localhost:3000';

const db = new DatabaseClient(TEAM_LEAD_SERVER);

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function promptCommand() {
    rl.question('TOS> ', async (command) => {
        if (command.toLowerCase() === 'exit') {
            console.log('Disconnecting from database server...');
            db.disconnect();
            rl.close();
            return;
        }

        try {
            const result = await db.executeCommand(command);
            console.log(result.message);
        } catch (error) {
            console.error('Error:', error.message);
        }

        promptCommand();
    });
}

console.log('Connected to database server. Type commands (e.g., "make db mydb") or "exit" to quit.');
promptCommand();

process.on('SIGINT', () => {
    console.log('\nDisconnecting from database server...');
    db.disconnect();
    rl.close();
});
