const dgram = require('dgram');
const socket = dgram.createSocket('udp4');
const multi_addr = '239.0.0.57';

socket.bind(12345, multi_addr, () => {
    socket.addMembership(multi_addr);
});

socket.on('message', (msg, rinfo) => {
    console.log(`client got: ${msg} from ${rinfo.address}:${rinfo.port}`);
});
