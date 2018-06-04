const rfm95 = require('./build/Release/rfm95');

var promise = rfm95.examplePromise(42);
promise.then(console.log, console.error);
console.log("Running...");

rfm95.setMode(0x05)
    .then(function (status) {
        console.log('OK ' + status)
    })
    .catch (function (err) {
        console.error('Failed: ' + err)
    });

