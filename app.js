const rfm95 = require('./build/Release/rfm95');
const value = 16;
 console.log(`${value} times 2 equals`, rfm95.hello(value));
// console.log(rfm95.sleep());
// console.log(rfm95.listen());


rfm95.byeASync(42, function(data) {
    console.log(data);
});

// rfm95.cbtest(function (msg) {
//     console.log(msg);
// });


//console.log(rfm95.byeSync());
