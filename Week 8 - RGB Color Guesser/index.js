var red;
var blue;
var green;

const getColor = () => {
    red = Math.floor(Math.random() * 256);
    green = Math.floor(Math.random() * 256);
    blue = Math.floor(Math.random() * 256);
    color_div = document.getElementById('color');
    color_div.style.backgroundColor = `rgb(${red}, ${green}, ${blue})`;
};

const handleClick = () => {
    document.getElementById('form').addEventListener('submit', (e) => {
        e.preventDefault();
    console.log("click handled...)});
};

getColor();
