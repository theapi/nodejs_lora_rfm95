
const rfm95 = require('./build/Release/rfm95');

const addr = 0x07; // RFM95_MODE

rfm95.init()
  .then((msg) => {
    return rfm95.writeRegister(addr, 0x01);
  })
  .then((msg) => {
    return rfm95.readRegister(addr);
  })
  .then((val) => {
    console.log(
      'Register 0x' + Number(addr).toString(16).padStart(2, '0')
      + ' has value 0x' + Number(val).toString(16).padStart(2, '0')
    );
  })
  .catch ((err) => {
    console.error(err);
  })
;
