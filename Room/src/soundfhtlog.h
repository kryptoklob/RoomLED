#ifndef SOUNDFHT_H
#define SOUNDFHT_H

#include "Arduino.h"
#include "headerfile.h"
#define LOG_OUT 1                                             // Use logarithmic based bins
#define OCTAVE 1

void isRipple();
void ripple();

#include <FHT.h>

// FHT Definitions
#define FHT_N 256                                             // Set to 64 point fht.

uint8_t micmult = 30;                                         // Bin values are very low, to let's crank 'em up.
uint8_t noiseval = 25;                                        // Increase this to reduce sensitivity.

void GetFHT() {

  cli();
  for (int i = 0 ; i < 127 ; i++) {
    fht_input[i] = analogRead(MIC_PIN) - 512;
  }
  sei();

  fht_window();                                               // Window the data for better frequency response.
  fht_reorder();                                              // Reorder the data before doing the fht.
  fht_run();                                                  // Process the data in the fht.
  fht_mag_octave();

} // GetFHT()

void soundfhtlog() {

  GetFHT();
  isRipple();
  ripple();

} // fhtsound()

void isRipple() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {           // Wait for interval ms before allowing a new ripple to be generated.
    previousMillis = currentMillis;
    Serial.println(abs(fht_oct_out[3]));
    if (abs(fht_oct_out[3]) - noiseval > 0) {
      step = -1;        // If the sound > threshold then start a ripple.
      //Serial.println(F("Generated ripple."));
    }
  }
}

void ripple() {
  fadeToBlackBy(leds, NUM_LEDS, 64);

  switch (step) {

    case -1:                                                  // Initialize ripple variables.
      center = random(NUM_LEDS);
      step = 0;
      break;

    case 0:
      leds[center] = CHSV(100, 255, 100);  // Display the first pixel of the ripple.
      step ++;
      break;

    case maxsteps:                                            // At the end of the ripples.
      //step = -1;
      break;

    default:                                                  // Middle of the ripples.
      leds[(center + step + NUM_LEDS) % NUM_LEDS] += CHSV(100, 255, 100);
      leds[(center - step + NUM_LEDS) % NUM_LEDS] += CHSV(100, 255, 100);

      step ++;                                                // Next step.

      break;

  } // switch step
}



#endif
