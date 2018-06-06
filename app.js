const rfm95 = require('./build/Release/rfm95');

var promise = rfm95.sleep();
promise.then(console.log, console.error);
console.log("Running...");


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