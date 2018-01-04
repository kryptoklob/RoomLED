#ifndef RAINBOW_MARCH_H
#define RAINBOW_MARCH_H

void rainbow_march() {
  this_index-= this_rot;
	fill_rainbow(leds, NUM_LEDS_PER_STRIP, this_index, this_diff);
}

#endif
