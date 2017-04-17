#ifndef SOUNDFHT_H
#define SOUNDFHT_H

#include "Arduino.h"
#include "headerfile.h"
#define LOG_OUT 1                                             // Use logarithmic based bins
#define OCTAVE 1

void isRipple();
void display();

#include <FHT.h>

// FHT Definitions
#define FHT_N 64                                             // Set to 64 point fht.
#define OCT_NORM 0

uint8_t micmult = 30;                                         // Bin values are very low, to let's crank 'em up.
uint8_t noiseval = 70;                                        // Increase this to reduce sensitivity.

void GetFHT() {

  cli();
  for (int i = 0 ; i < 127 ; i++) {
    fht_input[i] = (analogRead(MIC_PIN) - 512) << 2;
  }
  sei();

  fht_window();                                               // Window the data for better frequency response.
  fht_reorder();                                              // Reorder the data before doing the fht.
  fht_run();                                                  // Process the data in the fht.
  fht_mag_octave();

} // GetFHT()

void soundfhtlog() {

  GetFHT();
  display();

} // fhtsound()

void display() {
    // Fade everything
    fadeToBlackBy(leds, NUM_LEDS, 32);

    // --------- FIRST TWO OCTAVES --------
    uint8_t BASS_MAX = ((fht_oct_out[0]+fht_oct_out[1]-100)/5);//+fht_oct_out[2]-120)/8);
    if (fht_oct_out[0]+fht_oct_out[1] < 100){
      BASS_MAX = 1;
    }

    uint8_t BASS_MID = LEFTNO/2;
    CHSV bass_color = CHSV(130, 255, 255);
    // Show the lowest ocatve in the middle left/right strips
    for (int i = 0; (i < 25 && i < BASS_MAX); i++) {
      leds[BASS_MID+i] = bass_color;
      leds[BASS_MID-i] = bass_color;
      bass_color.hue += 7;
    }

   // -------- THIRD AND FOURTH OCTAVES ------
   uint8_t MID_MAX = ((fht_oct_out[4]+fht_oct_out[5]-30)/3);
   if (fht_oct_out[4]+fht_oct_out[5] < 50){
     MID_MAX = 1;
   }

   uint8_t MID_MID = LEFTNO + FRONTNO/2;
   CHSV mid_color = CHSV(130, 255, 255);
   // Show the lowest ocatve in the middle left/right strips
   for (int i = 0; (i < 25 && i < MID_MAX); i++) {
     leds[MID_MID+i] = mid_color;
     leds[MID_MID-i] = mid_color;
     mid_color.hue += 7;
   }

   // -------- SIXTH AND SEVENTH OCTAVES ------
   // Normalize the first octave maximum.
   uint8_t HIGH_MAX = ((fht_oct_out[6]+fht_oct_out[7]-30));
   if (fht_oct_out[6]+fht_oct_out[7] < 30){
     HIGH_MAX = 1;
   }

   uint8_t HIGH_START_FORWARD = LEFTNO;
   uint8_t HIGH_START_BACKWARD = LEFTNO+FRONTNO-1;
   CHSV high_color = CHSV(130, 255, 255);
   // Show the lowest ocatve in the middle left/right strips
   for (int i = 0; (i < 25 && i < MID_MAX); i++) {
     leds[HIGH_START_FORWARD+i] = high_color;
     leds[HIGH_START_BACKWARD-i] = high_color;
     leds[LEFTNO-1-i] = high_color;
     leds[0 + i] = high_color;
     high_color.hue += 7;
   }
}




#endif
