document.addEventListener('keydown', (event) => {
    if (event.code == 'Space') {
        startTimer();
    };
});

const startTimer = () => {
    element = document.getElementById('timer').textContent = 'timer has started...';
};