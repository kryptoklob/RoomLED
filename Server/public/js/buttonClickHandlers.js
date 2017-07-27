// Add click handelers to buttons.
// Disables version buttons that aren't applicable to current mode.
// Enabled version buttons that are applicable to current mode.

$(document).ready(function () {

  // If we choose a new color, send it to the server.
  $("#flat").on("change.spectrum", function(e, tinycolor) {
    currentColor = tinycolor.toHexString();
    sendValues();
  });

  $('.modeDiv > label').each(function() {
    $(this).click(function(){
      currentMode = this.children[0].id;
      currentVersion = "1";
      sendValues();
    });
  });

  $('.versionDiv > label').each(function() {
    $(this).click(function(){
      currentVersion = $(this).children()[0].id.substring(1);
      sendValues();
    });
  });
});
