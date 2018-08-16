## [Command Line Args]

The "argv" array contains everything given on the command line. The first item (argv[0]) will be the path to node itself, and the second item (argv[1]) will be the path to your script code.

So a slice starting at 2 will discard both of those and return everything else that was typed on the command line. These are the arguments that will be used to construct the API query string.
```
const argv = require('minimist')(process.argv.slice(2));
```

## [exec command](https://nodejs.org/dist/latest-v10.x/docs/api/child_process.html)
```
var cmd='my.bat';
var cmd=util.format("%s/%s",_dir, path.basename(cmdfile));
# cmd.repalce();

const { exec } = require('child_process');
exec(cmd, { timeout:Number(time)*1000 }, (err, stdout, stderr) => {
  if (err) {
    console.error(err);
    return;
  }
  console.log(stdout);
});
```
