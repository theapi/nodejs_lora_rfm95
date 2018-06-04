const rfm95 = require('./build/Release/rfm95');

var promise = rfm95.examplePromise(42);
promise.then(console.log, console.error);
console.log("Running...");

var mode = rfm95.setMode(0x05);
mode.then(console.log, console.error);
