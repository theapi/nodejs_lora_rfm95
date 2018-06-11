const rfm95 = require('./build/Release/rfm95');



function changeState(state) {
  switch (state) {
    case 'failed':
    break;

    case 'init':
      rfm95.init()
        .then((msg) => {
          console.log(msg);
          state = changeState('setFrequency');
        })
        .catch ((err) => {
          console.error('failed: ' + err);
          state = changeState('failed');
        })
      ;
    break;

    case 'setFrequency':
      rfm95.setFrequency(868)
        .then((msg) => {
          console.log(msg);
          state = changeState('setModemConfig');
        })
        .catch ((err) => {
          console.error('failed: ' + err);
          state = changeState('failed');
        })
      ;
    break;

    case 'setModemConfig':
      const modemConfigs = rfm95.getModemConfigs();
      rfm95.setModemConfig(modemConfigs.Bw500Cr45Sf128)
        .then((msg) => {
          console.log(msg);
          state = changeState('setTxPower');
        })
        .catch ((err) => {
          console.error('failed: ' + err);
          state = changeState('failed');
        })
      ;
    break;

    case 'setTxPower':
      rfm95.setTxPower(23)
        .then((msg) => {
          console.log(msg);
          state = changeState('available');
        })
        .catch ((err) => {
          console.error('failed: ' + err);
          state = changeState('failed');
        })
      ;
    break;
  }

  return state;  
}

let state = 'init';
state = changeState(state);


// const modemConfigs = rfm95.getModemConfigs();
// console.log(rfm95.getModemConfigs());
//console.log(modemConfigs.Bw125Cr45Sf128);

/*
rfm95.init()
  .then((msg) => {
    console.log(msg)
  })
  .catch ((err) => {
    console.error('failed: ' + err)
  })
;

var promise = rfm95.sleep();
promise.then(console.log, console.error);
console.log("Running...");

rfm95.standby()
  .then(function (msg) {
      console.log(msg)
  })
  .catch (function (err) {
      console.error('failed: ' + err)
  });

rfm95.listen()
  .then(function (msg) {
      console.log(msg)
  })
  .catch (function (err) {
      console.error('failed: ' + err)
  });
  */