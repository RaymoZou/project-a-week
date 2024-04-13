var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
ctx.font = "bold 48px serif";

const HEIGHT = canvas.height;
const WIDTH = canvas.width;
const BALL_SIZE = 10;
const FPS = 60;

var ball_x = WIDTH / 2;
var ball_y = HEIGHT / 2;
var x_velocity = 2;
var y_velocity = 2;

function reset() {
    console.info("resetting game");
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
};

function render() {
    ctx.clearRect(0, 0, WIDTH, HEIGHT); // clear the canvas
    ctx.fillRect(ball_x, ball_y, BALL_SIZE, BALL_SIZE);
};

function update() {
    if (ball_x <= 0 && x_velocity < 0) x_velocity *= -1;
    if (ball_x >= WIDTH && x_velocity > 0) x_velocity *= -1;
    if (ball_y <= 0 && y_velocity < 0) y_velocity *= -1;
    if (ball_y >= HEIGHT && y_velocity) y_velocity *= -1;
    ball_x += x_velocity;
    ball_y += y_velocity;
};

function runGame() {
    update();
    render();
};

setInterval(runGame, 1000 / FPS);
