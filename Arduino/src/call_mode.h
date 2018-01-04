void call_mode(String mode, bool new_mode, uint8_t red=255, uint8_t green=255, uint8_t blue=255){
	if (new_mode){
		Serial.print("Mode: ");
		Serial.println(mode);
		fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB(0,0,0));
	}

	if (mode == "solid") {
		if (new_mode) { fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB(global_red, global_green, global_blue)); }
	} else if (mode == "rainbow") {
		if (new_mode) { global_delay = 255; global_dir = 1; global_rot = 1; global_diff = 1; }
		rainbow_march();
	}
}
