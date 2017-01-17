express = require('express');  //web server
app = express();
server = require('http').createServer(app);
io = require('socket.io').listen(server);	//web socket server

server.listen(8080); //start the webserver on port 8080
app.use(express.static('public')); //tell the server that ./public/ contains the static webpages

var SerialPort = require("serialport");
var serialPort = new SerialPort("/dev/ttyACM0", { baudrate: 57600 });

var red = 0;
var green = 0;
var blue = 0;

io.sockets.on('connection', function (socket) { //gets called whenever a client connects
    socket.emit('led', {red:red, blue:blue, green:green}); //send the new client the current brightness

    socket.on('led', function (data) { //makes the socket react to 'led' packets by calling this function
        red = data.red;  //updates brightness from the data object
        green = data.green;
        blue = data.blue;
        var buf = new Buffer(3); //creates a new 3-byte buffer
        buf.writeUInt8(red, 0); //writes the pwm value to the buffer
	    buf.writeUInt8(green, 1);
	    buf.writeUInt8(blue, 2);
        serialPort.write(buf); //transmits the buffer to the arduino


        io.sockets.emit('led', {red:red, blue:blue, green:green}); //sends the updated brightness to all connected clients
    });
});

console.log("running");
