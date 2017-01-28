// Add click handelers to buttons.
    // Disables version buttons that aren't applicable to current mode.
    // Enabled version buttons that are applicable to current mode.


$(document).ready(function () {
  /**$('.modeDiv > label').each(function(){
    console.log("Click handler added.");
    $(this).click(function(){
      console.log("Click detected on" + this);
      for ($i = 10; $i > numModes[this.children[0].id]; $i--) {
        $(".versionDiv > label:nth-child("+$i+")").toggleClass("disabled", true);
        console.log("Button disabled.");
      }
      for ($i = numModes[this.children[0].id]; $i > 0; $i--){
        $(".versionDiv > label:nth-child("+$i+")").toggleClass('disabled', false);
        console.log("Button enabled.");
      }
    });
  });**/

  // If we choose a new color, send it to the server.
  $("#flat").on("change.spectrum", function(e, tinycolor) {
    color = tinycolor.toHexString();
    sendValues();
  });

  $('.modeDiv > label').each(function(){
    $(this).click(function(){
      currentMode = this.children[0].id;
      currentVersion = "1";
      /**for ($i = 2; $i < Object.keys(numModes).length; $i++) {
        $(".versionDiv > label:nth-child("+$i+")").toggleClass("active", false);
        console.log("Button deactivated.");
      }**/

      //$(".versionDiv > label:first-child").toggleClass("active", true);

      sendValues();
    });
  });

  $('.versionDiv > label').each(function(){
    $(this).click(function(){
      currentVersion = $(this).children()[0].id.substring(1);
      sendValues();
    });
  });
});
