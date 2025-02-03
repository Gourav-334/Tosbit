const DatabaseClient = require('./database-client');

// Replace this with your team lead's computer IP address when distributing to users
const TEAM_LEAD_SERVER = 'http://localhost:3000';

async function testDatabaseOperations() {
    // Create connection to database server
    const db = new DatabaseClient(TEAM_LEAD_SERVER);

    try {
        // 1. Create a new database
        console.log('\n1. Creating new database...');
        await db.createDatabase('testdb');
        console.log('✓ Database created');

        // 2. Use the database
        console.log('\n2. Switching to testdb...');
        await db.useDatabase('testdb');
        console.log('✓ Now using testdb');

        // 3. Create a table
        console.log('\n3. Creating users table...');
        await db.createTable('users', [
            { name: 'id', type: 'INT' },
            { name: 'name', type: 'VARCHAR' },
            { name: 'email', type: 'VARCHAR' },
            { name: 'age', type: 'INT' }
        ]);
        console.log('✓ Table created');

        // 4. Insert data
        console.log('\n4. Inserting user data...');
        await db.insert('users', {
            id: 1,
            name: 'John Doe',
            email: 'john@example.com',
            age: 25
        });
        console.log('✓ Data inserted');

        // 5. Query data
        console.log('\n5. Querying users...');
        const users = await db.select('users');
        console.log('Users in database:', JSON.stringify(users, null, 2));

        // 6. Show all databases
        console.log('\n6. Listing all databases...');
        const databases = await db.showDatabases();
        console.log('Available databases:', databases);

        // 7. Show all tables
        console.log('\n7. Listing all tables in testdb...');
        const tables = await db.showTables();
        console.log('Tables in testdb:', tables);

        // 8. Describe table
        console.log('\n8. Showing users table structure...');
        const schema = await db.describeTable('users');
        console.log('Users table schema:', JSON.stringify(schema, null, 2));

    } catch (error) {
        console.error('Error:', error.message);
    } finally {
        // Always disconnect when done
        db.disconnect();
        console.log('\nDisconnected from database server');
    }
}

// Run the test
console.log('Starting database operations test...');
console.log('This will connect to the database server and perform various operations');
testDatabaseOperations();
