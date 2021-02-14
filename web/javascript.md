# Javascript
## Standard
- [JS 6.0/2015](https://262.ecma-international.org/6.0/)
- [Tutorial Reference]()

## Tutorial
Embed js in <body>:
```
<script>
document.addEventListener("DOMContentLoaded", function() { // monitor event DOMContentLoaded.
  function createParagraph() {
    let para = document.createElement('p');
    para.textContent = '你点击了这个按钮！';
    document.body.appendChild(para);
  }

  const buttons = document.querySelectorAll('button');

  for(let i = 0; i < buttons.length ; i++) {
    buttons[i].addEventListener('click', createParagraph);
  }
});
</script>  
```
External js file: async works only for external js file. 
```
  <script src="script.js" async></script>
```
In script.js:
```
function createParagraph() {
  let para = document.createElement('p');
  para.textContent = '你点击了这个按钮！';
  document.body.appendChild(para);
}

const buttons = document.querySelectorAll('button');

for(let i = 0; i < buttons.length ; i++) {
  buttons[i].addEventListener('click', createParagraph);
} 
```
Embedde js function, no recommended
```
<button onclick="createParagraph()">点我呀</button>
```

- async 和 defer: External js files can be downloaded sync with html pages
```
<script async/defer src="js/vendor/jquery.js"></script>
<script async/defer src="js/script2.js"></script>
<script async/defer src="js/script3.js"></script>
```
async: orders are not determined.
defer: orders are kept.

Comments: 
- //: one line comments
- /*  */: multi-lines comments

### Variables,value,flow
使用关键字 let （旧代码中var）和一个名字来创建变量。常量用于存储不希望更改的数据，用关键字 const 创建，可以使用等号（=）和一个值来为变量赋值。
```
let randomNumber = Math.floor(Math.random() * 100) + 1;
const guesses = document.querySelector('.guesses');  // reference to an object
const guessSubmit = document.querySelector('.guessSubmit');
```
```
<p class="guesses"></p>
<p class="lastResult"></p>
<p class="lowOrHi"></p>

<label for="guessField">请猜数：</label>
<input type="text" id="guessField" class="guessField">
<input type="submit" value="确定" class="guessSubmit">
```
- Number: let myAge = 17;
- String: let dolphinGoodbye = 'So long and thanks for all the fish'; 单引号或双引号来包裹字符串,几乎没什么区别
- Bool: let iAmAlive = true;
- Array: let myNameArray = ['Chris', 'Bob', 'Jim'];
- Object: let dog = { name : 'Spot', breed : 'Dalmatian' };

#### Number and String
```
let myString = '123';
let myNum = Number(myString);
typeof myNum;

let myNum = 123;
let myString = myNum.toString();
typeof myString;
```
### Function
```
function checkGuess() {
  alert('我是一个占位符');
}
```
- Operators:
   - Math operators: +, -, *, /, %, **;  +=, -=, *=, /=, %=; ++, -- 
   - Comparison operators:  ===, !==, <, >, <=, >=
   - ==, !=: 测试值是否相同，但数据类型可能不同
   - ===, !==: 严格版本测试值和数据类型是否相同

- Conditional statement:
if () { ... }
if () { ... }
else if () { ... }
else  { ... }

- Loop
for (let i = 1; i < 21; i++) { console.log(i); }

- Event Listener and Handler
```
guessSubmit.addEventListener('click', checkGuess);  //event type: click, and event handler: function (without () )
```

### Object
### Builtin Objects  
- [string](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String)

- windows:
    - prompt():用户通过一个弹出对话框回答一个问题然后将输入的文本存储在一个给定的变量中
    - alert():来显示另一个弹出窗口
