/**   Format of mode buttons:
<label class="btn btn-success sharp">
<input type="radio" name="options" id="allOff" autocomplete="off">All Off
</label>
**/

$(document).ready(function () {

  modes.forEach(addButton);

  // "Item" contains a mode as described in modes.js
  function addButton(item, index) {
    $('<label/>', {
      'class' : "btn btn-success sharp"
    }).append(
      $('<input/>', {
        'id'          : item.name,//item.name,
        'type'        : 'radio',
        'name'        : 'options',
        'autocomplete': 'off'
      })
    ).append(item.name)
    .appendTo(".modeDiv");
  }
});
