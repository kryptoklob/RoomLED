$(document).ready(function () {

var socket = io.connect();
var mode;
var version;

socket.on('led', function(data) {
  mode = data.mode;
  version = data.version;

  // Set active mode buttons
  for ($i = 1; $i < 13; $i++) {
    $(".modeDiv > label:nth-child("+$i+")").toggleClass("active", false);
    console.log("Buttons un-activated.");
  }

  $("#"+mode).parent().toggleClass("active", true);


  // Set version buttons enabled/disabled
  for ($i = 10; $i > numModes[mode]; $i--) {
    $(".versionDiv > label:nth-child("+$i+")").toggleClass("disabled", true);
    console.log("Button disabled.");
  }
  for ($i = numModes[mode]; $i > 0; $i--){
    $(".versionDiv > label:nth-child("+$i+")").toggleClass("disabled", false);
    console.log("Button enabled.");
  }

  // Set the correct version active.
  for ($i = 1; $i < Object.keys(numModes).length; $i++) {
    $(".versionDiv > label:nth-child("+$i+")").toggleClass("active", false);
    console.log("Button deactivated.");
  }
  $(".versionDiv > label:nth-child("+version+")").toggleClass("active", true);


  console.log("Received data.");
});

function sendValues() {
  socket.emit('led', {mode:mode, version:version});
  console.log("Values sent.");
}

var numModes = {};
numModes.allOn = 1;
numModes.allOff= 1;
numModes.oneSin = 6;
numModes.twoSin = 10;
numModes.threeSin = 3;
numModes.confetti = 1;
numModes.sinelon = 1;
numModes.juggle = 1;
numModes.noise = 2;
numModes.rainbow = 6;
numModes.matrix = 3;
numModes.twinkle = 1;
numModes.popFade = 6;

var modes = ['allOff', 'allOn', 'oneSin', 'twoSin', 'threeSin', 'confetti', 'sinelon', 'juggle', 'noise', 'rainbow', 'matrix', 'twinkle', 'popFade']

$('.modeDiv > label').each(function(){
  console.log("Click handler added.");
  $(this).click(function(){
    console.log("Click detected on" + this);
    for ($i = 10; $i > numModes[this.children[0].id]; $i--) {
      $(".versionDiv > label:nth-child("+$i+")").toggleClass("disabled", true);
      $(".versionDiv > label:nth-child("+$i+")").attr('disabled', "disabled");
      console.log("Button disabled.");
    }
    for ($i = numModes[this.children[0].id]; $i > 0; $i--){
      $(".versionDiv > label:nth-child("+$i+")").toggleClass('disabled', false);
      $(".versionDiv > label:nth-child("+$i+")").removeAttr('disabled');
      console.log("Button enabled.");
    }
  });
});

$('.modeDiv > label').each(function(){
  $(this).click(function(){
    mode = this.children[0].id;
    version = "1";
    for ($i = 2; $i < Object.keys(numModes).length; $i++) {
      $(".versionDiv > label:nth-child("+$i+")").toggleClass("active", false);
      $(".versionDiv > label:nth-child("+$i+")").attr('disabled', "disabled");
      console.log("Button deactivated.");
    }

    $(".versionDiv > label:first-child").toggleClass("active", true);

    sendValues();
  });
});

$('.versionDiv > label').each(function(){
  $(this).click(function(){
    version = $(this).children()[0].id.substring(1);
    sendValues();
  });
});
});
