const { io } = require('socket.io-client');

class DatabaseClient {
    constructor(serverUrl) {
        if (!serverUrl) {
            throw new Error('Server URL is required! Example: http://team-leads-ip:3000');
        }
        this.socket = io(serverUrl);
        this.currentDatabase = null;
        
        this.socket.on('connect', () => {
            console.log('Connected to database server!');
            console.log('Your client ID is:', this.socket.id);
        });

        this.socket.on('disconnect', () => {
            console.log('Disconnected from database server');
        });

        this.socket.on('error', (error) => {
            console.error('Connection error:', error);
        });
    }

    async executeCommand(commandStr) {
        const command = commandStr.trim().toLowerCase();
        const parts = command.split(' ');

        try {
            switch(parts[0]) {
                case 'make':
                    if (parts[1] === 'db' && parts[2]) {
                        return await this.createDatabase(parts[2]);
                    } else if (parts[1] === 'table' && parts[2]) {
                        return await this.createTable(parts[2], this.parseTableStructure(parts.slice(3).join(' ')));
                    }
                    throw new Error('Invalid make command. Use: make db <name> or make table <name> (<columns>)');

                case 'open':
                    if (parts[1] === 'db' && parts[2]) {
                        return await this.useDatabase(parts[2]);
                    }
                    throw new Error('Invalid open command. Use: open db <name>');

                case 'show':
                    if (parts[1] === 'struct' && parts[2]) {
                        return await this.describeTable(parts[2]);
                    } else if (parts[1] === 'all') {
                        if (parts[2] === 'db') {
                            return await this.showDatabases();
                        } else if (parts[2] === 'tables') {
                            return await this.showTables();
                        }
                    }
                    throw new Error('Invalid show command. Use: show struct <table> or show all db or show all tables');

                default:
                    throw new Error('Unknown command. Available commands: make db, make table, open db, show struct, show all db, show all tables');
            }
        } catch (error) {
            console.error('Command error:', error.message);
            throw error;
        }
    }

    parseTableStructure(structStr) {
        structStr = structStr.trim().replace(/^\(|\)$/g, '');
        if (!structStr) {
            throw new Error('Table structure is required. Example: (id INT, name VARCHAR)');
        }

        const columns = structStr.split(',').map(col => {
            const [name, type] = col.trim().split(/\s+/);
            if (!name || !type) {
                throw new Error(`Invalid column definition: ${col}`);
            }
            return { name, type: type.toUpperCase() };
        });

        return columns;
    }

    async createDatabase(dbName) {
        return new Promise((resolve, reject) => {
            if (typeof dbName !== 'string' || dbName.trim().length === 0) {
                reject(new Error('Database name is required'));
                return;
            }

            if (/[\"\[\]]/.test(dbName)) {
                reject(new Error('Database name cannot contain ", [, or ]'));
                return;
            }

            this.socket.emit('createDatabase', dbName, (response) => {
                if (response.success) {
                    resolve({ success: true, message: `Database '${dbName}' created successfully` });
                } else {
                    reject(new Error(response.error));
                }
            });
        });
    }

    async useDatabase(dbName) {
        return new Promise((resolve, reject) => {
            this.socket.emit('useDatabase', dbName, (response) => {
                if (response.success) {
                    this.currentDatabase = dbName;
                    resolve({ success: true, message: `Using database '${dbName}'` });
                } else {
                    reject(new Error(response.error));
                }
            });
        });
    }

    async createTable(tableName, columns) {
        return new Promise((resolve, reject) => {
            if (!this.currentDatabase) {
                reject(new Error('No database selected. Use: open db <name>'));
                return;
            }

            this.socket.emit('createTable', { tableName, columns }, (response) => {
                if (response.success) {
                    resolve({ success: true, message: `Table '${tableName}' created successfully` });
                } else {
                    reject(new Error(response.error));
                }
            });
        });
    }

    async showDatabases() {
        return new Promise((resolve, reject) => {
            this.socket.emit('showDatabases', (response) => {
                if (response.success) {
                    const message = 'Available databases:\n' + response.databases.join('\n');
                    resolve({ success: true, message });
                } else {
                    reject(new Error(response.error));
                }
            });
        });
    }

    async showTables() {
        return new Promise((resolve, reject) => {
            if (!this.currentDatabase) {
                reject(new Error('No database selected. Use: open db <name>'));
                return;
            }

            this.socket.emit('showTables', (response) => {
                if (response.success) {
                    const message = `Tables in ${this.currentDatabase}:\n` + response.tables.join('\n');
                    resolve({ success: true, message });
                } else {
                    reject(new Error(response.error));
                }
            });
        });
    }

    async describeTable(tableName) {
        return new Promise((resolve, reject) => {
            if (!this.currentDatabase) {
                reject(new Error('No database selected. Use: open db <name>'));
                return;
            }

            this.socket.emit('describeTable', tableName, (response) => {
                if (response.success) {
                    const schema = response.schema;
                    let message = `Structure of table '${tableName}':\n`;
                    message += '+--------------------------------+------------+----------+\n';
                    message += '|         ATTRIBUTE NAME         | DATA TYPE  | KEY TYPE |\n';
                    message += '+--------------------------------+------------+----------+\n';
                    schema.forEach(col => {
                        const name = col.name.padEnd(32);
                        const type = col.type.padEnd(10);
                        const key = (col.key || '').padEnd(8);
                        message += `| ${name} | ${type} | ${key} |\n`;
                    });
                    message += '+--------------------------------+------------+----------+\n';
                    resolve({ success: true, message });
                } else {
                    reject(new Error(response.error));
                }
            });
        });
    }

    disconnect() {
        this.socket.disconnect();
    }
}

module.exports = DatabaseClient;
