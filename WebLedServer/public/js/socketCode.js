// Implements button listeners and socket communication.

$(document).ready(function () {

  var socket = io.connect();
  var currentMode;
  var currentVersion;
  var currentColor;
  var modeObject;

  // Receive data from server.
  socket.on('led', function(data) {
    currentMode = data.mode;
    currentVersion = data.version;
    currentColor = data.color;
    modeObject = $.grep(modes, function(e){ return e.id == currentMode; });

    // Set the version, mode, color text
    $("#modeText").text(currentMode);
    $("#versionText").text(currentVersion);
    $("#colorText").css('background-color', currentColor);

    // Set color picker to current color.
    $("#flat").spectrum("set", currentColor);

    // Set all mode buttons as un-selected
    for ($i = 1; $i < 15; $i++) {
      $(".modeDiv > label:nth-child("+$i+")").toggleClass("active", false);
      console.log("Buttons un-activated.");
    }

    // De-select all version buttons
    for ($i = 1; $i < 10; $i++) {
      $(".versionDiv > label:nth-child("+$i+")").toggleClass("active", false);
    }

    // Enable the current mode
    $("#"+currentMode).parent().toggleClass("active", true);

    // Disable unavailable version buttons
    for ($i = 10; $i > modesObject[currentMode]; $i--) {
      $(".versionDiv > label:nth-child("+$i+")").toggleClass("disabled", true);
      console.log("Button disabled.");
    }

    // Enable available version buttons
    for ($i = modesObject[currentMode]; $i > 0; $i--){
      $(".versionDiv > label:nth-child("+$i+")").toggleClass("disabled", false);
      console.log("Button enabled.");
    }

    // Set the correct version active.
    for ($i = 1; $i < modes.length; $i++) {
      $(".versionDiv > label:nth-child("+$i+")").toggleClass("active", false);
      console.log("Button deactivated.");
    }
    $(".versionDiv > label:nth-child("+version+")").toggleClass("active", true);

    console.log("Received data.");
  });

  // Send data to server.
  function sendValues() {
    socket.emit('led', {mode:currentMode, version:currentVersion, color:currentColor});
    // Set the version mode, text, and color
    $("#modeText").text(currentMode);
    $("#versionText").text(currentVersion);
    $("#colorText").css('background-color', currentColor);
    console.log("Values sent:");
    console.log("mode:"+currentMode);
    console.log("version:"+currentVersion);
    console.log("color:"+currentColor);
  }

  // If we choose a new color, send it to the server.
  $("#flat").on("change.spectrum", function(e, tinycolor) {
    color = tinycolor.toHexString();
    sendValues();
  });
});
