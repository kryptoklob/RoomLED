#ifndef RAINBOW_MARCH_H
#define RAINBOW_MARCH_H

void rainbow_march() {
  global_index-= global_rot;
	fill_rainbow(leds, NUM_LEDS_PER_STRIP, global_index, global_diff);
}

#endif
