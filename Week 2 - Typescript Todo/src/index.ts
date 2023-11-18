import 'dotenv/config';
import inquirer from 'inquirer';
import pg, { Client } from 'pg';

var client: Client;

const getInput = async (client: Client) => {
    const answer = await inquirer.prompt([{
        type: 'list',
        name: 'action',
        message: 'What would you like to do?',
        choices: ['Create a new TODO', 'View all TODOs', 'Quit'],
    },
    ]);

    return answer.action;
};

const connect_database = async () => {
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

const initiate_db = async (client: Client) => {
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
        const client = await connect_database();

        // enter cli loop
        while (true) {
            const action = await getInput(client);
            switch (action) {
                case 'Create a new TODO':
                    console.log('TODO: implement create new TODO function');
                    break;
                case 'View all TODOs':
                    await printTodos();
                    break;
                case 'Quit':
                    break;
                default:
                    console.error('Unexpected error has occurred, try again');
            };
            if (action === 'Quit') break;
        }
    } catch (err) {
        console.error(err);
    } finally {
        await client.end();
    }
};

main();



