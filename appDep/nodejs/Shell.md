# Run Shell using NodeJS

## Tutorial
- Child process: https://nodejs.org/docs/latest/api/child_process.html
- ShellJS: 
-  https://stackabuse.com/executing-shell-commands-with-node-js/


##  child_process module
The child_process module creates new child processes of the main Node.js process, executes shell commands with these child processes.

- **exec**: Buffered
creates a new shell and executes a given command. It stores all the output in a buffer, and is more memory intensive.
```
child_process.exec(command or script file,[, options][, callback]);

const { exec } = require("child_process");

exec("ls -la", (error, stdout, stderr) => {
    if (error) {
        console.log(`error: ${error.message}`);
        return;
    }
    if (stderr) {
        console.log(`stderr: ${stderr}`);
        return;
    }
    console.log(`stdout: ${stdout}`);
});
```

- **spawn**: Stream
executes a command in a new process, it uses a Stream API, and its output of the command is made available via listeners.
```
const { spawn } = require("child_process");

const ls = spawn("ls", ["-la"]);

ls.stdout.on("data", data => {
    console.log(`stdout: ${data}`);
});

ls.stderr.on("data", data => {
    console.log(`stderr: ${data}`);
});

ls.on('error', (error) => {
    console.log(`error: ${error.message}`);
});

ls.on("close", code => {
    console.log(`child process exited with code ${code}`);
});
```
- **sync spawn**:
```
'use strict';

const { spawnSync } = require( 'child_process' );
const ls = spawnSync( 'ls', [ '-lh', '/usr' ] );

console.log( `stderr: ${ ls.stderr.toString() }` );
console.log( `stdout: ${ ls.stdout.toString() }` );
```
- **promise**: buffered,non-stream formatted output
```
function execShellCommand(cmd) {
  const exec = require("child_process").exec;
  return new Promise((resolve, reject) => {
    exec(cmd, { maxBuffer: 1024 * 500 }, (error, stdout, stderr) => {
      if (error) {
        console.warn(error);
      } else if (stdout) {
        console.log(stdout); 
      } else {
        console.log(stderr);
      }
      resolve(stdout ? true : false);
    });
  });
}
```
- **stop process**:
```
const { exec,  } = require('node:child_process')

// execute the sleep command - this will wait for 100 seconds before exiting
const command = exec("sleep 100")

// when a child process exits, it fires the "close" event
command.on('close', (code) => {
    console.log('process has exited')
})

// Since we don't want to wait for 100 seconds, we can send a kill command after a 1 second timeout
setTimeout(() => {
    command.kill()
}, 1000)
```

## ShellJS 
ShellJS is a npm library to run UNIX commands in cross platforms using javascript code. It provides the unix commands:
_touch, cat, rm, which, cd, cp_.
```
var shell = require('shelljs');

if (!shell.which('java')) {
  shell.echo('Java version is not installed');
  shell.exit(1);
}

shell.rm('-rf', 'dist/public');

shell.cp('-R', 'dist/', 'release');
```
