let red;
let green;
let blue;

const getColor = () => {
  red = Math.floor(Math.random() * 256);
  green = Math.floor(Math.random() * 256);
  blue = Math.floor(Math.random() * 256);
  color_div = document.getElementById("color");
  color_div.style.backgroundColor = `rgb(${red}, ${green}, ${blue})`;
};

document.getElementById("form").addEventListener("submit", (e) => {
  e.preventDefault();
  const data = document.forms.form;
  const formData = new FormData(data);
  const redGuess = formData.get("red");
  const greenGuess = formData.get("green");
  const blueGuess = formData.get("blue");
  document.getElementById("result").textContent = `red guess: ${
    redGuess / red
  }}`;
  console.log("red guess: ", redGuess / red);
  console.log("green guess: ", greenGuess / green);
  console.log("blue guess: ", blueGuess / blue);
});

getColor();
