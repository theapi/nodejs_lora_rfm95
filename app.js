const rfm95 = require('./build/Release/rfm95');

var promise = rfm95.examplePromise(42);
promise.then(console.log, console.error);
console.log("Running...");

rfm95.sleep()
    .then(function (status) {
        console.log('sleep ' + status)
    })
    .catch (function (err) {
        console.error('sleep failed: ' + err)
    });

rfm95.standby()
    .then(function (status) {
        console.log('standby ' + status)
    })
    .catch (function (err) {
        console.error('standby failed: ' + err)
    });

rfm95.listen()
    .then(function (status) {
        console.log('listen ' + status)
    })
    .catch (function (err) {
        console.error('listen failed: ' + err)
    });