express = require('express');  //web server
app = express();
server = require('http').createServer(app);
io = require('socket.io').listen(server);	//web socket server

server.listen(8080); //start the webserver on port 8080
app.use(express.static('public')); //tell the server that ./public/ contains the static webpages

var SerialPort = require("serialport");
var serialPort = new SerialPort("/dev/ttyACM0", { baudrate: 57600 });

var mode = 0;
var modeName = "allOff";
var version = 1;

app.get("/notification",function(request, response){
  // Turn off led's at T-0
  serialPort.write("m");
  serialPort.write("0");

  // Flash them back at T+200ms
  setTimeout(function() {
    serialPort.write("m");
    serialPort.write("1");
}, 200);

  // Flash off at T+400ms
  setTimeout(function() {
    serialPort.write("m");
    serialPort.write("0");
}, 400);

  // Return to previously scheduled programming at T+600ms
  setTimeout(function() {
    serialPort.write("m");
    serialPort.write((Number(mode)+Number(version)-1).toString());
}, 600);

  response.writeHead(200, {"Content-Type": "application/json"});
  response.write("Notiication successful.");
});

io.sockets.on('connection', function (socket) { //gets called whenever a client connects
    socket.emit('led', {mode:modeName, version:version}); //send the new client current mode & version info

    socket.on('led', function (data) { //makes the socket react to 'led' packets by calling this function

        console.log("Receved data:\n");
        console.log(data);
        modeName = data.mode;

        if (data.mode == "allOff") mode = 0;
        else if (data.mode == "allOn") mode = 1;
        else if (data.mode == "twinkle") mode = 2;
        else if (data.mode == "twoSin") mode = 3;
        else if (data.mode == "matrix") mode = 13;
        else if (data.mode == "oneSin") mode = 16;
        else if (data.mode == "popFade") mode = 22;
        else if (data.mode == "threeSin") mode = 28;
        else if (data.mode == "rainbow") mode = 31;
        else if (data.mode == "noise") mode = 37;
        else if (data.mode == "confetti") mode = 39;
        else if (data.mode == "sinelon") mode = 40;
        else if (data.mode == "juggle") mode = 41;
        else {
            console.log("Received bad data.");
            return;}
        version = data.version;

        console.log("Writing 'm'");
        serialPort.write("m");
        console.log("Writing '"+(Number(mode)+Number(version)-1).toString()+"'");
        serialPort.write((Number(mode)+Number(version)-1).toString());
        io.sockets.emit('led', {mode:modeName, version:version}); //sends the updated brightness to all connected clients
        console.log("\n\n");
    });
});

console.log("Running...\n");
