import inquirer from 'inquirer';

const promptUser = async () => {
    const answer = await inquirer.prompt([{
        type: 'list',
        name: 'action',
        message: 'What would you like to do?',
        choices: ['Create a new TODO', 'View all TODOs'],
    },
    ]);

    switch (answer.action) {
        case 'Create a new TODO':
            console.log('creating a new todo');
            break;
        case 'View all TODOs':
            console.log('Viewing all TODOs');
            break;
        default:
            console.error('Unexpected error has occurred, try again');
            promptUser();
    };
};

promptUser();



