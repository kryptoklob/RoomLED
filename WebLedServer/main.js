express = require('express');  //web server
tinycolor = require('tinycolor2');
app = express();
server = require('http').createServer(app);
io = require('socket.io').listen(server);	//web socket server
//modesFile = require('./public/js/modes')
var fs = require('fs');
eval(fs.readFileSync('./public/js/modes.js')+'');


server.listen(8080); //start the webserver on port 8080
app.use(express.static('public')); //tell the server that ./public/ contains the static webpages

var SerialPort = require("serialport");
var serialPort = new SerialPort("/dev/ttyACM0", { baudrate: 57600 });

//var modes = modesFile.modes;
/**var modes = [
  { name: "All Off", baseID: 0, versions: 1 },
  { name: "All On", baseID: 1, versions: 1 },
  { name: "One-Sin", baseID: 16, versions: 6 },
  { name: "Two-Sin", baseID: 3, versions: 10 },
  { name: "Three-Sin", baseID: 28, versions: 3 },
  { name: "Confetti", baseID: 39, versions: 1 },
  { name: "Sinelon", baseID: 40, versions: 1 },
  { name: "Juggle", baseID: 41, versions: 1 },
  { name: "Noise", baseID: 37, versions: 2 },
  { name: "Rainbow", baseID: 31, versions: 6 },
  { name: "Matrix", baseID: 13, versions: 3 },
  { name: "Twinkle", baseID: 2, versions: 1 },
  { name: "Pop-Fade", baseID: 22, versions: 6 },
  { name: "Dot-Beat", baseID: 42, versions: 1 },
  { name: "Lightnings", baseID: 43, versions: 1 }
];**/
var modeNumber = 1;
var modeName = "All On";
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
  modeObject = modes.filter(function(value){ return value.name == modeName;})[0]
  modeNumber = Number(modeObject['baseID']) + Number(version) - 1;

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
