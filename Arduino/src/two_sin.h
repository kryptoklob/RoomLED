#ifndef TWO_SIN_H
#define TWO_SIN_H

/* Usage - two_sin();
 *
 * Loads of variables to play with
 * 
 */


// two_sin_pal variables-------------------------------------------------------------------------

uint8_t thathue = 140;                                        // You can change the starting hue for other wave.
uint8_t thatrot = 0;                                          // You can change how quickly the hue rotates for the other wave. Currently 0.
int8_t thatspeed = 4;                                         // You can change the speed, and use negative values.
int thatphase = 0;                                            // Phase change value gets calculated.
uint8_t thatcutoff = 192;                                     // You can change the cutoff value to display that wave. Lower value = longer wave.


void two_sin() {                                                              // This is the heart of this_ program. Sure is short.

  if (this_dir == 0) {this_phase += this_speed; thatphase += thatspeed;} 
  else {this_phase -= this_speed; thatphase -= thatspeed;}

  this_hue = this_hue + this_rot;                                                // Hue rotation is fun for this_wave.
  thathue = thathue + thatrot;                                                // It's also fun for thatwave.
  
  for (int k=0; k<NUM_LEDS_PER_STRIP-1; k++) {
    int this_bright = qsuba(cubicwave8((k*all_freq)+this_phase), this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    int thatbright = qsuba(cubicwave8((k*all_freq)+128+thatphase), thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

    leds[k] = CHSV(this_hue, this_sat, this_bright);                              // Assigning hues and brightness to the led array.
    leds[k] += CHSV(thathue, this_sat, thatbright);                      

  }
} // two_sin()

#endif
