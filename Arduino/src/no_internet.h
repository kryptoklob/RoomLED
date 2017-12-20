#ifndef NO_INTERNET_H
#define NO_INTERNET_H

/* No internet alert.
 * Flashes the sides of the strips red (with the rest of it blue)
 */

uint8_t flashing_index = 0;
uint8_t modifier = 1;

void no_internet() {
	// Fill up the entire strip red
	fill_solid(leds, NUM_LEDS_PER_STRIP, CHSV(160, 255, 255));

	uint8_t i;

	// Pulse the sides
	for(i = 0; i < 5; i++){
		leds[i] = CHSV(0, 255, flashing_index);
		leds[NUM_LEDS_PER_STRIP-1-i] = CHSV(0, 255, flashing_index);
	}

	flashing_index = flashing_index + modifier;
	if (flashing_index == 255)	{modifier = -1;}
	if (flashing_index == 0) 		{modifier = 1;}
}


#endif
