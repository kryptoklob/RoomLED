#ifndef JUGGLE_PAL_H
#define JUGGLE_PAL_H

/* This is adapted from a routine created by Mark Kriegsman */

/*  Usage - juggle_pal();
 *  
 *  this_hue
 *  this_fade
 *  numdots
 *  this_beat
 *  this_bright
 *  this_diff
 */

uint8_t numdots;

void juggle_pal() {                                            // Several colored dots, weaving in and out of sync with each other
  this_index = 0;                                           // Reset the hue values.
  fadeToBlackBy(leds, NUM_LEDS_PER_STRIP, this_fade);
  for( int i = 0; i < numdots; i++) {
    leds[beatsin16(this_beat+i+numdots,0,NUM_LEDS_PER_STRIP)] += ColorFromPalette(current_palette, this_index , this_bright, current_blending);    // Munge the values and pick a colour from the palette
    this_index += this_diff;
  }
} // juggle_pal()

#endif
