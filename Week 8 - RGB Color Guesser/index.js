const getColor = () => {
  const red = Math.floor(Math.random() * 256);
  const green = Math.floor(Math.random() * 256);
  const blue = Math.floor(Math.random() * 256);
  color_div = document.getElementById("color");
  color_div.style.backgroundColor = `rgb(${red}, ${green}, ${blue})`;
};

getColor();

console.log("hello world");
