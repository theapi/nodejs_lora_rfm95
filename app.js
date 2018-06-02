const rfm95 = require('./build/Release/rfm95');
const value = 16;
 console.log(`${value} times 2 equals`, rfm95.hello(value));
// console.log(rfm95.sleep());
// console.log(rfm95.listen());


rfm95.byeASync(42, function(data) {
    console.log(data);
});

var promise = rfm95.examplePromise(42);
promise.then(console.log, console.error);

// rfm95.cbtest(function (msg) {
//     console.log(msg);
// });


//console.log(rfm95.byeSync());
