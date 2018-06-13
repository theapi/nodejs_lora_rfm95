
const rfm95 = require('./build/Release/rfm95');

rfm95.readRegister(23)
  .then((msg) => {
    console.log(msg);
  })
  .catch ((err) => {
    console.error(err);
  })
;