const rfm95 = require('./build/Release/rfm95');
const value = 16;
 console.log(`${value} times 2 equals`, rfm95.hello(value));
 console.log(rfm95.sleep());
 console.log(rfm95.listen());
//
//console.log(rfm95.byeASync());
//console.log(rfm95.byeSync());

rfm95.byeASync(function(msg){
    console.log(msg);
});

rfm95.cbtest(function (msg) {
    console.log(msg);
});


console.log(rfm95.byeSync());
