express = require('express');  //web server
tinycolor = require('tinycolor2');
app = express();
server = require('http').createServer(app);
io = require('socket.io').listen(server);	//web socket server
modesFile = require('./public/js/modes')


server.listen(8080); //start the webserver on port 8080
app.use(express.static('public')); //tell the server that ./public/ contains the static webpages

var SerialPort = require("serialport");
var serialPort = new SerialPort("/dev/ttyACM0", { baudrate: 57600 });

var modes = modesFile.modes;
var modeNumber = 0;
var modeName = "allOff";
var modeObject;
var version = 1;
var color = "#000000";

app.head("/notification",function(request, response){
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
    if (mode != 1) {
      serialPort.write("m");
      serialPort.write((Number(mode)+Number(version)-1).toString());
    }
    if (mode == 1) {
      colorTiny = tinycolor(color).toHsv();
      serialPort.write("a");
      serialPort.write(Math.round(colorTiny.h).toString());
    }
  }, 600);


  response.writeHead(200, {"Content-Type": "application/json"});
  response.end();
});

io.sockets.on('connection', function (socket) { //gets called whenever a client connects
  socket.emit('led', {mode:modeName, version:version, color:color}); //send the new client current mode & version info

  socket.on('led', function (data) { //makes the socket react to 'led' packets by calling this function
  socket.emit('led', {mode:modeName, version:version, color:color});

  console.log("Receved data:\n");
  console.log(data);

  modeName = data.mode;
  version = data.version;
  color = data.color;

  // Get mode #
  modeObject = modes.filter(function(value){ return value.name == modeName;})
  modeNumber = modeObject['baseID'] + version - 1;

  // Write mode to Arduino.

  console.log("Writing 'm'");
  serialPort.write("m");
  console.log("Writing '" + modeNumber + "'");
  serialPort.write(modeNumber.toString());
  io.sockets.emit('led', {mode:modeName, version:version, color: color});
  console.log("\n\n");

  // Get color info
  colorTiny = tinycolor(color).toHsv();

  setTimeout(function(){
    console.log("Writing 'h'");
    serialPort.write("h");
    console.log("Writing '"+(Math.round(colorTiny.h)).toString()+"'");
    serialPort.write((Math.round(colorTiny.h)).toString());
  }, 600);

  setTimeout(function(){
    console.log("Writing 't'");
    serialPort.write("t");
    console.log("Writing '"+(Math.round(colorTiny.s*255)).toString()+"'");
    serialPort.write((Math.round(colorTiny.s*255)).toString());
  }, 800);
});
});

console.log("Running...\n");
