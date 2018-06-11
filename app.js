const rfm95 = require('./build/Release/rfm95');

function changeState(state) {
  switch (state) {
    case 'failed':
    break;

    case 'setup':
      rfm95.init()
        .then((msg) => {
          console.log(msg);
          return rfm95.setFrequency(868);
        })
        .then((msg) => {
          console.log(msg);
          const modemConfigs = rfm95.getModemConfigs();
          return rfm95.setModemConfig(modemConfigs.Bw500Cr45Sf128);
        })
        .then((msg) => {
          console.log(msg);
          return rfm95.setTxPower(23);
        })
        .then((msg) => {
          console.log(msg);
          state = changeState('listen');
        })
        .catch ((err) => {
          console.error('failed: ' + err);
          state = changeState('failed');
        })
      ;
    break;

    case 'listen':
      console.log('wait for rfm95.available()');
    break;

    case 'recv':
      // Process payload, then return to listen state.
    break;
  }

  return state;  
}

// Start the state machine.
let state = 'setup';
state = changeState(state);
