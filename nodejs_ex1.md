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
