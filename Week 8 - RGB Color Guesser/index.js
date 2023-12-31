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
  document.getElementById("red_result").textContent = `
  red guess: ${Math.abs(red - redGuess)} points ${
    redGuess > red ? "above" : "below"
  }
   the actual red value.`;
  document.getElementById("green_result").textContent = `
  green guess: ${Math.abs(green - greenGuess)} points ${
    greenGuess > green ? "above" : "below"
  }
   the actual green value.`;
  document.getElementById("blue_result").textContent = `
  blue guess: ${Math.abs(blue - blueGuess)} points ${
    blueGuess > blue ? "above" : "below"
  }
   the actual blue value.`;
});

getColor();
