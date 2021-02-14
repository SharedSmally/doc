# Javascript
## Standard
- [JS 6.0/2015](https://262.ecma-international.org/6.0/)
- [Tutorial Reference]()

## Tutorial
Embed js in <body>:
```
<script>
  javascript code
</script>  
```
External js file:  
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

### Variables,value,flow

### Function
### Object
### Builtin Objects  
