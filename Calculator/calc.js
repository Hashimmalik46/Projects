const numBtns = document.querySelectorAll(".num");
const op = document.querySelectorAll(".op");
const output = document.querySelector(".output");
const backspace = document.querySelector(".backspace");
const clear = document.querySelector(".clear");
const equals = document.querySelector(".equals");
const decimal = document.querySelector(".decimal");
let currentInput = "";

numBtns.forEach((btn) => {
  btn.addEventListener("click", function () {
    currentInput += btn.textContent;
    output.textContent = currentInput;
  });
});

backspace.addEventListener("click", function () {
  currentInput = currentInput.slice(0, -1);
  output.textContent = currentInput;
});

clear.addEventListener("click", function () {
  currentInput = "";
  output.textContent = "";
});

decimal.addEventListener("click", function () {
  currentInput += decimal.dataset.decimal;
  output.textContent = currentInput;
});
op.forEach((btn) => {
  btn.addEventListener("click", function () {
    currentInput += btn.dataset.op;
    output.textContent = currentInput;
  });
});

// currentInput=Number(currentInput);
equals.addEventListener("click", function () {
  let result = eval(currentInput);
  output.textContent = result;
  currentInput = result;
});
