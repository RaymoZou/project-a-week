const getColor = () => {
    var red = Math.floor(Math.random() * 256);
    var green = Math.floor(Math.random() * 256);
    var blue = Math.floor(Math.random() * 256);
    color_div = document.getElementById('color');
    color_div.style.backgroundColor = `rgb(${red}, ${green}, ${blue})`;
};

getColor();