const rfm95 = require('./build/Release/rfm95');

const modemConfigs = rfm95.getModemConfigs();
console.log(rfm95.getModemConfigs());
//console.log(modemConfigs.Bw125Cr45Sf128);

rfm95.init()
  .then(function (status) {
    console.log('init: ' + status)
  })
  .catch (function (err) {
    console.error('init failed: ' + err)
  })
;

var promise = rfm95.sleep();
promise.then(console.log, console.error);
console.log("Running...");

// rfm95.setModemConfig(modemConfigs.Bw125Cr45Sf128)
//   .then(console.log, console.error);


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