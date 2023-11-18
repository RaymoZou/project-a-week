import 'dotenv/config';
import inquirer from 'inquirer';
import pg, { Client } from 'pg';

var client: Client;

const choices = [
    'Create a new TODO ✏️',
    'View all TODOs 🔍',
    'Quit 🚪',

];

const getInput = async () => {
    const answer = await inquirer.prompt([{
        type: 'list',
        name: 'action',
        message: 'What would you like to do?',
        choices: choices,
    },
    ]);

    return answer.action;
};

const connectDB = async () => {
    try {
        console.log('Connecting to database...');
        client = new pg.Client();
        await client.connect();
        console.log('Connected!');
        return client;
    } catch (err) {
        throw err;
    };
};

const printTodos = async () => {
    try {
        const todos = await client.query(`SELECT * FROM todos`);
        todos.rows.forEach(todo => {
            console.log(`------------------`)
            console.log(`ID: ${todo.id}\nTitle: ${todo.title}`);
            console.log(`------------------`)
        })
    } catch (err) {
        throw err;
        // throw new Error('There was an error getting the TODOs');
    }
};

const initiateDB = async () => {
    try {
        await client.query(
            `CREATE TABLE todos (
                id serial PRIMARY KEY,
                title text
            )`
        );
    } catch (err) {
        throw err;
    }
}

const main = async () => {
    try {
        // connect to local postgreSQL database
        const client = await connectDB();

        // enter cli loop
        while (true) {
            const action = await getInput();
            switch (action) {
                case choices[0]:
                    console.log('TODO: implement create new TODO function');
                    break;
                case choices[1]:
                    await printTodos();
                    break;
            };
            if (action === choices[2]) break;
        }
    } catch (err) {
        console.error(err);
    } finally {
        await client.end();
    }
};

main();



