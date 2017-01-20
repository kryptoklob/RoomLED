$('video source').last().on('error', function() {
    $("#videoStatus").text("Video (Status: Down)");
});

$('video').last().on('loadeddata', function() {
    $("#videoStatus").text("Video (Status: Up)");
})
