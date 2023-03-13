# NodeJS

## Run Script: from
- exec: block
```
const { exec } = require('child_process');
exec('ls | grep js', (err, stdout, stderr) => {
  if (err) {    //some err occurred
    console.error(err)
  } else { // the *entire* stdout and stderr (buffered)
   console.log(`stdout: ${stdout}`);
   console.log(`stderr: ${stderr}`);
  }
});
```
With Promise:
```
const util = require('util');
const exec = util.promisify(require('child_process').exec);
async function lsWithGrep() {
  try {
      const { stdout, stderr } = await exec('ls | grep js');
      console.log('stdout:', stdout);
      console.log('stderr:', stderr);
  }catch (err)=>{
     console.error(err);
  };
};
lsWithGrep();
```
- spawn: stream
```
const { spawn } = require('child_process');
const child = spawn('ls', );
   // use child.stdout.setEncoding('utf8'); if you want text chunks
child.stdout.on('data', (chunk) => {
  // data from the standard output is here as buffers
});
// since these are streams, you can pipe them elsewhere
child.stderr.pipe(dest);
child.on('close', (code) => {
  console.log(`child process exited with code ${code}`);
});
```
- execute shell script synchronously
```
const { execSync } = require('child_process');
// stderr is sent to stdout of parent process: can set options.stdio if want it to go elsewhere
const stdout = execSync('ls');
const { spawnSync} = require('child_process');
const child = spawnSync('ls', );
console.error('error', child.error);
console.log('stdout ', child.stdout);
console.error('stderr ', child.stderr);
```
- Run Shell or bash file 
```
const exec = require('child_process').exec, child;
const myShellScript = exec('sh doSomething.sh /myDir');
myShellScript.stdout.on('data', (data)=>{
    console.log(data); 
    // do whatever you want here with data
});
myShellScript.stderr.on('data', (data)=>{
    console.error(data);
});
```
## Template
- handlebars: 
    - https://www.npmjs.com/package/handlebars (Mustach++)
    - https://handlebarsjs.com/
- Mustache: 
### handlers: npm install handlebars

```
<script src="https://cdn.jsdelivr.net/npm/handlebars@latest/dist/handlebars.js"></script>
<script>
  // compile the template
  var template = Handlebars.compile("Handlebars <b>{{doesWhat}}</b>");
  // execute the compiled template and print the output to the console
  console.log(template({ doesWhat: "rocks!" }));
</script>
```
or
```
const Handlebars = require("handlebars");
const template = Handlebars.compile("Name: {{name}}");
console.log(template({ name: "Nils" }));  // render
```
#### expression
##### Basic Usage: {{parameter}}
```
<p>{{firstname}} {{lastname}}</p>
{
  firstname: "Yehuda",
  lastname: "Katz",
}
=><p>Yehuda Katz</p>
```
##### Path expressions: using dot(.)
```
{{person.firstname}} {{person.lastname}}
{
  person: {
    firstname: "Yehuda",
    lastname: "Katz",
  },
}
```
###### Changing the context: #with / #each
```
{{#each people}}
    {{../prefix}} {{firstname}} 
{{/each}}
{
  people: [
    { firstname: "Nils" },
    { firstname: "Yehuda" },
  ],
  prefix: "Hello",
}
```
#####  HTML-escaping: {{{specialChars}}}
```
raw: {{{specialChars}}}
html-escaped: {{specialChars}}
{ specialChars: "& < > \" ' ` =" }
```
=>
```
raw: & < > " ' ` =
html-escaped: &amp; &lt; &gt; &quot; &#x27; &#x60; &#x3D;
```
##### Partials: reuse templates
```
Handlebars.registerPartial('myPartial', '{{prefix}}');  #register partial
{ prefix: "Hello" } 

{{> myPartial }} => Hello  # call partial to run it in current context
```



##### Helpers: new function
registered at runtime via Handlebars.registerHelper
```
Handlebars.registerHelper('loud', function (aString) {
    return aString.toUpperCase()
})

{{firstname}} {{loud lastname}}
```
Multiple arguments
```
Handlebars.registerHelper("link", function(text, url) {
      var url = Handlebars.escapeExpression(url), text = Handlebars.escapeExpression(text)       
     return new Handlebars.SafeString("<a href='" + url + "'>" + text +"</a>");
});
{{link "See Website" url}}
{ url: "https://yehudakatz.com/" }
=> <a href='https://yehudakatz.com/'>See Website</a>
```
###### Subexpressions
Allows to invoke multiple helpers within a single mustache, and pass in the results of inner helper invocations as arguments to outer helpers. 
```
{{outer-helper (inner-helper 'abc') 'def'}}
```
#### Built-in Helpers
- #if
- #unless
- #each
- #with
- lookup
- log

#### API
```
Handlebars.registerPartial("foo", partial);
Handlebars.registerPartial({ foo: partial, bar: partial });
Handlebars.unregisterPartial("foo");

Handlebars.registerHelper("foo", function() {});
Handlebars.unregisterHelper("foo");

var OtherHandlebars = Handlebars.create();

Handlebars.SafeString(string)
Handlebars.escapeExpression(string)
Handlebars.createFrame(data)
Handlebars.Utils.isEmpty(value)
Handlebars.Utils.extend(obj, value)
Handlebars.Utils.toString(obj)
Handlebars.Utils.isArray(obj)
Handlebars.Utils.isFunction(obj)
Handlebars.log(level, message)
```
#### @data variables
- @root: Initial context with which the template was executed.
```
{{#each array}} {{@root.foo}} {{/each}}
```
- @first/index/last:
```
{{#each array}} {{#if @first}} First! {{/if}} {{/each}}
{{#each array}} {{@index}} {{/each}}  //0-based
{{#each array}} {{#if @last}} Last :( {{/if}} {{/each}}
```
- @key:Key name for the current iteration step
```
{{#each array}} {{@key}} {{/each}}
```
