const rfm95 = require('./build/Release/rfm95');

// console.log(rfm95.sleep());
// console.log(rfm95.listen());

var promise = rfm95.examplePromise(42);
promise.then(console.log, console.error);
console.log("Running...");


