# Module

## Module
- Module Provider: ./user.js
```
const getName = () => {
  return 'Jim';
};

const getLocation = () => {
  return 'Munich';
};

const dateOfBirth = '12.01.1982';

//exports: the object return from require
exports.getName = getName;
exports.getLocation = getLocation;
exports.dob = dateOfBirth;
```

- Module Consumer: main.js
```
const user = require('./user');
const { getName, dob } = require('./user');
console.log(
  `${user.getName()} lives in ${user.getLocation()} and was born on ${user.dob}.`
);
```

- export class
```
class User {
  constructor(name, age, email) {
    this.name = name;
    this.age = age;
    this.email = email;
  }

  getUserStats() {
    return `
      Name: ${this.name}
      Age: ${this.age}
      Email: ${this.email}
    `;
  }
}

module.exports = User;
```
- user
```
const User = require('./user');
const jim = new User('Jim', 37, 'jim@example.com');

console.log(jim.getUserStats());
```

- Difference between **module.exports** and **exports**

Using module.exports:
```
module.exports = {
  greet: function (name) {
    console.log(`Hi ${name}!`);
  },

  farewell: function() {
    console.log('Bye!');
  }
}
```
Using exports:
```
exports.greet = function (name) {
  console.log(`Hi ${name}!`);
}

exports.farewell = function() {
  console.log('Bye!');
}
```
