// Server framework.
express = require('express');

// Color utililties.
tinycolor = require('tinycolor2');

// Create the server.
app = express();
server = require('http').createServer(app);
io = require('socket.io').listen(server);

// Quick & dirty way to import the modes files also used client-side.
var fs = require('fs');
eval(fs.readFileSync('./public/js/modes.js')+'');

// Server setup.
server.listen(8080);
app.use(express.static('public'));

// Connects to the Arduino Serial port via USB.
var SerialPort = require("serialport");
var serialPort = new SerialPort("/dev/ttyACM0", { baudrate: 57600 });

// Global var initial assignments.
var modeNumber = 1;
var modeName = "AllOn";
var modeObject;
var version = 1;
var color = "#000000";

// API!
app.head("/api/:command",function(request, response){
  modeName = String(request.params.command);
  console.log("Command received via API: " + modeName);

  version = 1;
  
  response.writeHead(200, {"Content-Type": "application/json"});
  response.end();


  setMode();


});

function setMode(){
  // Send LED event to all clients.
  //socket.emit('led', {mode:modeName, version:version, color:color});
  // Get mode number.
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

  // Write color info to Arduino. Timeout functions are to prevent us from
  // writing again within the socket communication threshold.
  setTimeout(function(){
    console.log("Writing 'h'");
    serialPort.write("h");
    console.log("Writing '"+(Math.round(colorTiny.h)).toString()+"'");
    serialPort.write((Math.round(colorTiny.h)).toString());
}, 300);

  setTimeout(function(){
    console.log("Writing 't'");
    serialPort.write("t");
    console.log("Writing '"+(Math.round(colorTiny.s*255)).toString()+"'");
    serialPort.write((Math.round(colorTiny.s*255)).toString());
}, 600);
}

// On connection from a client:
io.sockets.on('connection', function (socket) {

  // Update the client with the new info (and push an update to other clients)
  socket.emit('led', {mode:modeName, version:version, color:color});

  // On "LED" events from clients: (aka commands)
  socket.on('led', function (data) {
    // Send LED event to all clients.
    socket.emit('led', {mode:modeName, version:version, color:color});

    // Log received data.
    console.log("Receved data:\n");
    console.log(data);

    // Set global vars.
    modeName = data.mode;
    version = data.version;
    color = data.color;

    // Set mode.
    setMode();
  });
});

  console.log("Running...\n");
