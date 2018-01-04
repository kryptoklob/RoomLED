void call_mode(uint8_t mode_number, bool new_mode, uint8_t red=255, uint8_t green=255, uint8_t blue=255){

	// If new mode, clear out LEDs
	if (new_mode){
		Serial.print("Mode: ");
		Serial.println(led_mode);
		fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB(0,0,0));
	}

	switch (mode_number){
		// 0 - all off
		case 0:
			if (mc) { fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB(0,0,0)); }
			break;

		// 1 - all on
		case 1:
			if (mc) { fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB(red, green, blue); }
			break;

		// 2 - rainbow march
		case 2:
			if (mc) { this_delay = 255; this_dir = 1; this_rot = 1; this_diff = 1; rainbow_march(); }
			break;

		/**

		// 3 - audio responsive
		case 3:
			if (mc) { audio_responsive(); }
			break;


			**/
	}
}
