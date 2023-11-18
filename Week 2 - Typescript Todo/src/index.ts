import 'dotenv/config';
import inquirer from 'inquirer';
import pg from 'pg';

const promptUser = async () => {
    const answer = await inquirer.prompt([{
        type: 'list',
        name: 'action',
        message: 'What would you like to do?',
        choices: ['Create a new TODO', 'View all TODOs'],
    },
    ]);
    return answer.action;

    // switch (answer.action) {
    //     case 'Create a new TODO':
    //         console.log('creating a new todo');
    //         break;
    //     case 'View all TODOs':
    //         console.log('Viewing all TODOs');
    //         break;
    //     default:
    //         console.error('Unexpected error has occurred, try again');
    //         promptUser();
    // };
};

const connect_database = async () => {
    try {
        console.log('Connecting to database...');
        const client = new pg.Client();
        await client.connect();
        console.log('Connected!');
        return client;
    } catch (err) {
        throw new Error('There was an error connecting to the database...');
    };
};

const main = async () => {
    try {
        const client = await connect_database();
        const action = await promptUser();
        console.log(action);
        client.end();
    } catch (err) {
        console.error(err);
    }
};

main();



