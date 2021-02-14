# Javascript
## Standard
- [JS 6.0/2015](https://262.ecma-international.org/6.0/)
- [Tutorial Reference]()

## Reference
- [Reference](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference)
- [Built-in Objects](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects)
- [Web API](https://developer.mozilla.org/en-US/docs/Web/API)
    - [DOM Object](https://developer.mozilla.org/en-US/docs/Web/API/Document_Object_Model)
        - [window](https://developer.mozilla.org/en-US/docs/Web/API/Window)
    - [DOM Spec](https://dom.spec.whatwg.org/)
    
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
let myStr = NEW String('123');
let myNum = Number(myString);
typeof myNum;

let myNum = 123;
let myString = myNum.toString();
typeof myString;
```
### Array
```
let sequence = [1, 1, 2, 3, 5, 8, 13];
let random = ['tree', 795, [0, 1, 2]];
```
### JSON and [json5](https://json5.org/)
```
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
没有函数名的函数叫做匿名函数,它也不会自己做任何事情,通常将匿名函数与事件处理程序一起使用：
```
var myButton = document.querySelector('button');
myButton.onclick = function() {
  alert('hello');
}
```
将匿名函数分配为变量的值：
```
let myGreeting = function() {
  alert('hello');
}
myGreeting();
```
### Event
- [Web Events reference](https://developer.mozilla.org/en-US/docs/Web/Events)
事件是系统会在事件出现时产生或触发某种信号，并且会提供一个自动加载某种动作的机制:
```
const btn = document.querySelector('button');

btn.onclick = function() {
  const rndCol = 'rgb(' + random(255) + ',' + random(255) + ',' + random(255) + ')';
  document.body.style.backgroundColor = rndCol;
}
```
```
const btn = document.querySelector('button');
function bgChange() {
  const rndCol = 'rgb(' + random(255) + ',' + random(255) + ',' + random(255) + ')';
  document.body.style.backgroundColor = rndCol;
}
btn.onclick = bgChange;
```
```
btn.addEventListener('click', bgChange);
btn.removeEventListener('click', bgChange);
```
event object:
```
function bgChange(e) {
  const rndCol = 'rgb(' + random(255) + ',' + random(255) + ',' + random(255) + ')';
  e.target.style.backgroundColor = rndCol;
  console.log(e);
}
```
### Object
```
var person = {};

var person = {
  name : ['Bob', 'Smith'],
  age : 32,
  gender : 'male',
  interests : ['music', 'skiing'],
  bio : function() {
    alert(this.name[0] + ' ' + this.name[1] + ' is ' + this.age + ' years old. He likes ' + this.interests[0] + ' and ' + this.interests[1] + '.');
  },
  greeting: function() {
    alert('Hi! I\'m ' + this.name[0] + '.');
  }
};

person.name[0]
person.age
person.interests[1]
person.bio()
person.greeting()

person['eyes'] = 'hazel'
person.farewell = function() { alert("Bye everybody!") }
```
Constructor: 使用了this关键词.
```
function Person(name) {
  this.name = name;
  this.greeting = function() {
    alert('Hi! I\'m ' + this.name + '.');
  };
}

var person1 = new Person('Bob');
person1.name
person1.greeting()

var person2 = Object.create(person1);

var person1 = new Object();
person1.name = 'Chris';
person1['age'] = 38;
person1.greeting = function() {
  alert('Hi! I\'m ' + this.name + '.');
}

var person1 = new Object({
  name : 'Chris',
  age : 38,
  greeting : function() {
    alert('Hi! I\'m ' + this.name + '.');
  }
});
```

### prototype
每个对象拥有一个原型对象，对象以其原型为模板、从原型继承方法和属性。原型对象也可能拥有原型，并从中继承方法和属性，一层一层、以此类推.

在传统的 OOP 中，首先定义“类”，此后创建对象实例时，类中定义的所有属性和方法都被复制到实例中。在 JavaScript 中并不如此复制——而是在
对象实例和它的构造器之间建立一个链接（它是__proto__属性，是从构造函数的prototype属性派生的），之后通过上溯原型链，在构造器中找到这些属性和方法

在javascript中，函数可以有属性。 每个函数都有一个特殊的属性叫作原型（prototype）。
```
function doSomething(){}
console.log( doSomething.prototype );

var doSomething = function(){};
console.log( doSomething.prototype );

doSomething.prototype.foo = "bar";
console.log( doSomething.prototype );

function doSomething(){}
doSomething.prototype.foo = "bar"; // add a property onto the prototype

var doSomeInstancing = new doSomething();
doSomeInstancing.prop = "some value"; // add a property onto the object
console.log( doSomeInstancing );
```
当访问 doSomeInstancing 的一个属性, 浏览器首先查找 doSomeInstancing 是否有这个属性. 如果没有这个属性, 会在 doSomeInstancing 的 __proto__ 中查找这个属性(也就是 doSomething.prototype). 如果__proto__有这个属性, 这个属性就会被使用. 否则浏览器就会去查找 doSomeInstancing 的 __proto__ 的 __proto__ ，看它是否有这个属性. 默认情况下, 所有函数的原型属性的 __proto__ 就是 window.Object.prototype.

继承的属性和方法是定义在 prototype 属性之上的,那些以 Object.prototype. 开头的属性。prototype 属性的值是一个对象，储存被原型链下游的对象继承的属性和方法。

每个实例对象都从原型中继承了一个constructor属性，该属性指向了用于构造此实例对象的构造函数。可以在 constructor 属性的末尾添加一对圆括号（括号中包含所需的参数），从而用这个构造器创建另一个对象实例。毕竟构造器是一个函数，故可以通过圆括号调用；只需在前面添加 new 关键字，便能将此函数作为构造器使用
```
var person3 = new person1.constructor('Karen', 'Stephenson', 26, 'female', ['playing drums', 'mountain climbing']);

Person.prototype.farewell = function() {
  alert(this.name.first + ' has left the building. Bye for now!');
}
```
一种极其常见的对象定义模式是，在构造器（函数体）中定义属性、在 prototype 属性上定义方法。
```
// 构造器及其属性定义
function Test(a,b,c,d) {
  // 属性定义
};

// 定义第一个方法
Test.prototype.x = function () { ... }

// 定义第二个方法
Test.prototype.y = function () { ... }

// 等等……
```

原型式的继承
```
function Teacher(first, last, age, gender, interests, subject) {
  Person.call(this, first, last, age, gender, interests);
  this.subject = subject;
}

Teacher.prototype = Object.create(Person.prototype);
Teacher.prototype.constructor = Teacher;

Teacher.prototype.greeting = function() { ... }

var teacher1 = new Teacher('Dave', 'Griffiths', 31, 'male', ['football', 'cookery'], 'mathematics');
```

### JSON
JSON 是一种纯数据格式，它只包含属性，没有方法。
JSON要求在字符串和属性名称周围使用双引号。 单引号无效
- Object
```
{
  "squadName" : "Super hero squad",
  "homeTown" : "Metro City",
  "formed" : 2016,
  "secretBase" : "Super tower",
  "active" : true,
  "members" : [
    {
      "name" : "Molecule Man",
      "age" : 29,
      "secretIdentity" : "Dan Jukes",
      "powers" : [
        "Radiation resistance",
        "Turning tiny",
        "Radiation blast"
      ]
    },
    {
      "name" : "Madame Uppercut",
      "age" : 39,
      "secretIdentity" : "Jane Wilson",
      "powers" : [
        "Million tonne punch",
        "Damage resistance",
        "Superhuman reflexes"
      ]
    },
    {
      "name" : "Eternal Flame",
      "age" : 1000000,
      "secretIdentity" : "Unknown",
      "powers" : [
        "Immortality",
        "Heat Immunity",
        "Inferno",
        "Teleportation",
        "Interdimensional travel"
      ]
    }
  ]
}
```
JSON Access
```
superHeroes.hometown
superHeroes["active"]
superHeroes["members"][1]["powers"][2]
```
- Array
```
[
  {
    "name" : "Molecule Man",
    "age" : 29,
    "secretIdentity" : "Dan Jukes",
    "powers" : [
      "Radiation resistance",
      "Turning tiny",
      "Radiation blast"
    ]
  },
  {
    "name" : "Madame Uppercut",
    "age" : 39,
    "secretIdentity" : "Jane Wilson",
    "powers" : [
      "Million tonne punch",
      "Damage resistance",
      "Superhuman reflexes"
    ]
  }
]
```
JSON，包含以下两个方法。
   - parse(): 以文本字符串形式接受JSON对象作为参数，并返回相应的对象。
   - stringify(): 接收一个对象作为参数，返回一个对应的JSON字符串。

```
var requestURL = 'https://mdn.github.io/learning-area/javascript/oojs/json/superheroes.json';
var request = new XMLHttpRequest();

request.responseType = 'json';
request.send();
request.onload = function() {
  var superHeroes = request.response;
  populateHeader(superHeroes);
  showHeroes(superHeroes);
}

request.open('GET', requestURL);
request.responseType = 'text'; // now we're getting a string!
request.send();

request.onload = function() {
  var superHeroesText = request.response; // get the string from the response
  var superHeroes = JSON.parse(superHeroesText); // convert it to an object
  populateHeader(superHeroes);
  showHeroes(superHeroes);
}
```

### Asynchronous JavaScript
- Async callbacks
```
btn.addEventListener('click', () => {
  alert('You clicked me!');

  let pElem = document.createElement('p');
  pElem.textContent = 'This is a newly-added paragraph.';
  document.body.appendChild(pElem);
});
```
- XMLHttpRequest
```
function loadAsset(url, type, callback) {
  let xhr = new XMLHttpRequest();
  xhr.open('GET', url);
  xhr.responseType = type;

  xhr.onload = function() {
    callback(xhr.response);
  };

  xhr.send();
}

function displayImage(blob) {
  let objectURL = URL.createObjectURL(blob);

  let image = document.createElement('img');
  image.src = objectURL;
  document.body.appendChild(image);
}

loadAsset('coffee.jpg', 'blob', displayImage);
```

- Promises
```
fetch('products.json').then(function(response) {
  return response.json();
}).then(function(json) {
  products = json;
  initialize();
}).catch(function(err) {
  console.log('Fetch problem: ' + err.message);
});
```
- Async functions
    - setTimeout(): Execute a specified block of code once after a specified time has elapsed.
```
// With a named function
let myGreeting = setTimeout(function sayHi() {
  alert('Hello, Mr. Universe!');
}, 2000)

// With a function defined separately
function sayHi() {
  alert('Hello Mr. Universe!');
}

let myGreeting = setTimeout(sayHi, 2000);

clearTimeout(myGreeting);
```
    - setInterval(): Execute a specified block of code repeatedly with a fixed time delay between each call.
    - requestAnimationFrame(): The modern version of setInterval(). 
```
function displayTime() {
   let date = new Date();
   let time = date.toLocaleTimeString();
   document.getElementById('demo').textContent = time;
}

const createClock = setInterval(displayTime, 1000);

const myInterval = setInterval(myFunction, 2000);

clearInterval(myInterval);

cancelAnimationFrame(rAF);
```
### Builtin Objects  
- [string](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String)
- array
- JSON object
- console
- windows:
    - prompt():用户通过一个弹出对话框回答一个问题然后将输入的文本存储在一个给定的变量中
    - alert():来显示另一个弹出窗口
