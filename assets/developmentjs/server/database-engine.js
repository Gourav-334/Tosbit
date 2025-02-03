const fs = require('fs').promises;
const path = require('path');

class DatabaseEngine {
    constructor() {
        this.databases = new Map();
        this.currentDatabase = null;
        this.dataDir = path.join(__dirname, '..', 'data');
        this.initializeStorage();
    }

    async initializeStorage() {
        try {
            await fs.mkdir(this.dataDir, { recursive: true });
            await this.loadState();
        } catch (error) {
            console.error('Failed to initialize storage:', error);
        }
    }

    async saveState() {
        try {
            const state = {
                databases: Object.fromEntries(this.databases),
                currentDatabase: this.currentDatabase
            };
            await fs.writeFile(
                path.join(this.dataDir, 'db_state.json'),
                JSON.stringify(state, null, 2)
            );
        } catch (error) {
            console.error('Failed to save state:', error);
        }
    }

    async loadState() {
        try {
            const data = await fs.readFile(path.join(this.dataDir, 'db_state.json'), 'utf8');
            const state = JSON.parse(data);
            this.databases = new Map(Object.entries(state.databases));
            this.currentDatabase = state.currentDatabase;
        } catch (error) {
            console.log('No previous state found, starting fresh');
        }
    }

    async createDatabase(dbName) {
        if (typeof dbName !== 'string' || dbName.trim().length === 0) {
            throw new Error('Invalid database name');
        }
        if (this.databases.has(dbName)) {
            throw new Error(`Database '${dbName}' already exists`);
        }
        this.databases.set(dbName, new Map());
        await this.saveState();
        return true;
    }

    async useDatabase(dbName) {
        if (!this.databases.has(dbName)) {
            throw new Error(`Database '${dbName}' does not exist`);
        }
        this.currentDatabase = dbName;
        await this.saveState();
        return true;
    }

    async createTable(tableName, columns) {
        if (!this.currentDatabase) {
            throw new Error('No database selected');
        }
        if (typeof tableName !== 'string' || tableName.trim().length === 0) {
            throw new Error('Invalid table name');
        }
        if (!Array.isArray(columns) || columns.length === 0) {
            throw new Error('Columns must be a non-empty array');
        }

        const db = this.databases.get(this.currentDatabase);
        if (db.has(tableName)) {
            throw new Error(`Table '${tableName}' already exists`);
        }

        columns.forEach(col => {
            if (!col.name || !col.type) {
                throw new Error('Each column must have a name and type');
            }
            if (!this.isValidDataType(col.type)) {
                throw new Error(`Invalid data type '${col.type}' for column '${col.name}'`);
            }
        });

        db.set(tableName, {
            schema: columns,
            data: []
        });
        await this.saveState();
        return true;
    }

    async insert(tableName, data) {
        if (!this.currentDatabase) {
            throw new Error('No database selected');
        }

        const db = this.databases.get(this.currentDatabase);
        if (!db.has(tableName)) {
            throw new Error(`Table '${tableName}' does not exist`);
        }

        const table = db.get(tableName);
        
        table.schema.forEach(col => {
            if (!data.hasOwnProperty(col.name)) {
                throw new Error(`Missing value for column '${col.name}'`);
            }
            if (!this.validateDataType(data[col.name], col.type)) {
                throw new Error(`Invalid value type for column '${col.name}'. Expected ${col.type}`);
            }
        });

        table.data.push({...data, _id: Date.now()});
        await this.saveState();
        return true;
    }

    async select(tableName, conditions = null) {
        if (!this.currentDatabase) {
            throw new Error('No database selected');
        }

        const db = this.databases.get(this.currentDatabase);
        if (!db.has(tableName)) {
            throw new Error(`Table '${tableName}' does not exist`);
        }

        const table = db.get(tableName);
        if (!conditions) {
            return table.data;
        }

        return table.data.filter(row => {
            return Object.entries(conditions).every(([key, value]) => row[key] === value);
        });
    }

    async showDatabases() {
        return Array.from(this.databases.keys());
    }

    async showTables() {
        if (!this.currentDatabase) {
            throw new Error('No database selected');
        }
        const db = this.databases.get(this.currentDatabase);
        return Array.from(db.keys());
    }

    async describeTable(tableName) {
        if (!this.currentDatabase) {
            throw new Error('No database selected');
        }

        const db = this.databases.get(this.currentDatabase);
        if (!db.has(tableName)) {
            throw new Error(`Table '${tableName}' does not exist`);
        }

        return db.get(tableName).schema;
    }

    isValidDataType(type) {
        const validTypes = ['INT', 'VARCHAR', 'TEXT', 'BOOLEAN', 'FLOAT'];
        return validTypes.includes(type.toUpperCase());
    }

    validateDataType(value, type) {
        type = type.toUpperCase();
        switch (type) {
            case 'INT':
                return Number.isInteger(value);
            case 'FLOAT':
                return typeof value === 'number';
            case 'VARCHAR':
            case 'TEXT':
                return typeof value === 'string';
            case 'BOOLEAN':
                return typeof value === 'boolean';
            default:
                return false;
        }
    }
}

module.exports = DatabaseEngine;
