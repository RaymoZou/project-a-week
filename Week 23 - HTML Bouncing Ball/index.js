var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
ctx.font = "bold 48px serif";

const HEIGHT = canvas.height;
const WIDTH = canvas.width;
const BALL_SIZE = 10;
const FPS = 60;

var x = WIDTH / 2;
var y = HEIGHT / 2;
var x_velocity = 2;
var y_velocity = 2;

function reset() {
    console.info("resetting game");
    x = WIDTH / 2;
    y = HEIGHT / 2;
};

function render() {
    ctx.clearRect(0, 0, WIDTH, HEIGHT); // clear the canvas
    ctx.fillRect(x, y, BALL_SIZE, BALL_SIZE);
};

function update() {
    if (x <= 0 && x_velocity < 0) x_velocity *= -1;
    if (x >= WIDTH && x_velocity > 0) x_velocity *= -1;
    if (y <= 0 && y_velocity < 0) y_velocity *= -1;
    if (y >= HEIGHT && y_velocity) y_velocity *= -1;
    x += x_velocity;
    y += y_velocity;
};

function runGame() {
    update();
    render();
};

setInterval(runGame, 1000 / FPS);
