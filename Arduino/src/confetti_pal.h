#ifndef CONFETTI_PAL_H
#define CONFETTI_PAL_H

/* This is adapted from the confetti routine created by Mark Kriegsman */

/*  Usage - confetti_pal();
 *   
 *  this_fade
 *  this_delay
 *  current_palette and target_palette
 *  this_diff
 *  this_index
 *  this_inc
 *  this_bright
 */


void confetti_pal() {                                                                                               // random colored speckles that blink in and fade smoothly

//  EVERY_N_SECONDS(5) {
//    SetupSimilar4Palette();
//  }

  fadeToBlackBy(leds, NUM_LEDS_PER_STRIP, this_fade);                                                                      
  int pos = random8(NUM_LEDS_PER_STRIP);                                                                                      // Pick an LED at random.
  leds[pos] = ColorFromPalette(current_palette, this_index + random8(this_diff)/4 , this_bright, current_blending);      // Munge the values and pick a colour from the palette
  this_index = this_index + this_inc;                                                                                  // base palette counter increments here.
} // confetti_pal()

#endif
