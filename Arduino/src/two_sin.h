#ifndef TWO_SIN_H
#define TWO_SIN_H

// Vars
uint8_t wavebright = 255;                                     // You can change the brightness of the waves/bars rolling across the screen. Best to make them not as bright as the sparkles.
uint8_t thathue = 140;                                        // You can change the starting hue for other wave.
uint8_t thisrot = 0;                                          // You can change how quickly the hue rotates for this wave. Currently 0.
uint8_t thatrot = 0;                                          // You can change how quickly the hue rotates for the other wave. Currently 0.
uint8_t allsat = 255;                                         // I like 'em fully saturated with colour.
bool thisdir = 0;                                             // A direction variable that will work with inputs.
int8_t thisspeed = 4;                                         // You can change the speed, and can use negative values.
int8_t thatspeed = 4;                                         // You can change the speed, and use negative values.
uint8_t allfreq = 32;                                         // You can change the frequency, thus overall width of bars.
int thisphase = 0;                                            // Phase change value gets calculated.
int thatphase = 0;                                            // Phase change value gets calculated.
uint8_t thiscutoff = 100;                                     // You can change the cutoff value to display this wave. Lower value = longer wave.
uint8_t thatcutoff = 100;                                     // You can change the cutoff value to display that wave. Lower value = longer wave.

// Function
void two_sin() {                                                              // This is the heart of this program. Sure is short.

  if (thisdir == 0) {thisphase += thisspeed; thatphase += thatspeed;}
  else {thisphase -= thisspeed; thatphase -= thatspeed;}

  thishue = thishue + thisrot;                                                // Hue rotation is fun for thiswave.
  thathue = thathue + thatrot;                                                // It's also fun for thatwave.

  for (int k=0; k<NUM_LEDS-1; k++) {
    int thisbright = qsuba(cubicwave8((k*allfreq)+thisphase), thiscutoff);     // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    int thatbright = qsuba(cubicwave8((k*allfreq)+128+thatphase), thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

    leds[k] = CHSV(thishue, allsat, thisbright);                              // Assigning hues and brightness to the led array.
    leds[k] += CHSV(thathue, allsat, thatbright);
  }
} // two_sin()

#endif
