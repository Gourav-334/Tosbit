const { Server } = require('socket.io');
const DatabaseEngine = require('./database-engine');

const io = new Server(3000, {
    cors: {
        origin: "*"
    }
});

const dbEngine = new DatabaseEngine();

function logOperation(clientId, operation, details) {
    const log = {
        timestamp: new Date(),
        clientId,
        operation,
        details
    };
    console.log(`[${log.timestamp.toISOString()}] Client ${clientId}: ${operation}`, details);
}

io.on('connection', (socket) => {
    console.log(`New client connected: ${socket.id}`);
    logOperation(socket.id, 'CONNECT', 'New connection established');

    socket.on('disconnect', () => {
        logOperation(socket.id, 'DISCONNECT', 'Client disconnected');
        console.log(`Client disconnected: ${socket.id}`);
    });

    socket.on('createDatabase', async (dbName, callback) => {
        try {
            await dbEngine.createDatabase(dbName);
            logOperation(socket.id, 'CREATE_DATABASE', { database: dbName });
            callback({ success: true, message: `Database '${dbName}' created` });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });

    socket.on('useDatabase', async (dbName, callback) => {
        try {
            await dbEngine.useDatabase(dbName);
            logOperation(socket.id, 'USE_DATABASE', { database: dbName });
            callback({ success: true, message: `Using database '${dbName}'` });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });

    socket.on('createTable', async ({ tableName, columns }, callback) => {
        try {
            await dbEngine.createTable(tableName, columns);
            logOperation(socket.id, 'CREATE_TABLE', { table: tableName, columns });
            callback({ success: true, message: `Table '${tableName}' created` });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });

    socket.on('insert', async ({ tableName, data }, callback) => {
        try {
            await dbEngine.insert(tableName, data);
            logOperation(socket.id, 'INSERT', { table: tableName, data });
            callback({ success: true, message: 'Data inserted successfully' });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });

    socket.on('select', async ({ tableName, conditions }, callback) => {
        try {
            const results = await dbEngine.select(tableName, conditions);
            logOperation(socket.id, 'SELECT', { table: tableName, conditions });
            callback({ success: true, data: results });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });

    socket.on('showDatabases', async (callback) => {
        try {
            const databases = await dbEngine.showDatabases();
            logOperation(socket.id, 'SHOW_DATABASES', { count: databases.length });
            callback({ success: true, databases });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });

    socket.on('showTables', async (callback) => {
        try {
            const tables = await dbEngine.showTables();
            logOperation(socket.id, 'SHOW_TABLES', { count: tables.length });
            callback({ success: true, tables });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });

    socket.on('describeTable', async (tableName, callback) => {
        try {
            const schema = await dbEngine.describeTable(tableName);
            logOperation(socket.id, 'DESCRIBE_TABLE', { table: tableName });
            callback({ success: true, schema });
        } catch (error) {
            logOperation(socket.id, 'ERROR', error.message);
            callback({ success: false, error: error.message });
        }
    });
});

process.on('SIGINT', async () => {
    console.log('\nSaving database state before exit...');
    await dbEngine.saveState();
    process.exit();
});

console.log('Database server is running on port 3000');
console.log('Ready to accept client connections...');
