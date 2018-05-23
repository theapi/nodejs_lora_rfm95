const rfm95 = require('./build/Release/rfm95');
const value = 16;
console.log(`${value} times 2 equals`, rfm95.hello(value));
console.log(rfm95.setMode(value));