import 'dotenv/config';
import inquirer from 'inquirer';
import pg, { Client } from 'pg';
import { v4 as uuidv4 } from 'uuid';

var client: Client;

const choices = [
    'Create a new TODO',
    'View all TODOs',
    'Initiate Database',
    'Clear Database',
    'Quit',
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
        const todos = await client.query(`SELECT * FROM todos;`);
        todos.rows.forEach(todo => {
            console.log(`------------------`)
            console.log(`ID: ${todo.id}\nTitle: ${todo.title}\nDescription: ${todo.description}`);
            console.log(`------------------`)
        })
    } catch (err) {
        throw err;
    }
};

const initiateDB = async () => {
    try {
        await client.query(
            `CREATE TABLE todos (
                id text PRIMARY KEY,
                title text,
                description text
            );`
        );  
    } catch (err) {
        throw err;
    }
}

const createTodo = async () => {
    try {
        const todo = await inquirer.prompt([{
            type: 'input',
            name: 'title',
            message: 'Enter TODO title',
        },
        {
            type: 'input',
            name: 'description',
            message: 'Enter TODO description',
        }]);
        const id = uuidv4();
        console.log(id, todo.title, todo.description);
        client.query({
            text: 'INSERT INTO todos (id, title, description) VALUES ($1, $2, $3)',
            values: [id, todo.title, todo.description]
        });
    } catch (err) {
        throw err;
    }
}

const resetTodos = async () => {
    await client.query(`DROP TABLE todos;`);
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
                    await createTodo();
                    break;
                case choices[1]:
                    await printTodos();
                    break;
                case choices[2]:
                    await initiateDB();
                    break;
                case choices[3]:
                    await resetTodos();
                    break;
            };
            if (action === choices[choices.length - 1]) break;
        }
    } catch (err) {
        console.error(err);
    } finally {
        await client.end();
    }
};

main();



