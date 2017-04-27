#ifndef SOUNDFHT_H
#define SOUNDFHT_H

// Includes
#include "FHT.h"

// Defines
#define LOG_OUT 1                                             // Use logarithmic based bins
#define OCTAVE 1                                              // Use octave mode
#define FHT_N 64                                              // Set to 64 point fht.
#define OCT_NORM 0                                            // Octave normalization

// Function prototypes
void isRipple();
void display();

// Vars
unsigned long previousMillis = 0;

// Functions
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

}

// Main mode loop
void soundfhtlog() {
  GetFHT();
  display();

}

void display() {
    // Index vars
    uint8_t BASS_MID_SIDE       = LEFTNO/2;
    uint8_t BASS_MID_FRONT      = LEFTNO + FRONTNO/2;
    uint8_t MID_START1_FORWARD  = LEFTNO;
    uint8_t MID_START1_BACKWARD = LEFTNO+FRONTNO-1;
    uint8_t MID_START2_FORWARD  = 0;
    uint8_t MID_START2_BACKWARD = LEFTNO-1;

    // Fade each part of each segment at a different rate
    fadeToBlackBy(leds, NUM_LEDS, FAST_FADE_RATE);

    // First 5 leds fade instantly
    fadeToBlackBy(&leds[MID_START1_FORWARD],        5,      INSTANT_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_FORWARD],        5,      INSTANT_FADE_RATE);
    fadeToBlackBy(&leds[MID_START1_BACKWARD-5],     5,      INSTANT_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_BACKWARD-5],     5,      INSTANT_FADE_RATE);
    // Second 5 leds fade quickly
    fadeToBlackBy(&leds[MID_START1_FORWARD+5],      5,      FAST_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_FORWARD+5],      5,      FAST_FADE_RATE);
    fadeToBlackBy(&leds[MID_START1_BACKWARD-10],    5,      FAST_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_BACKWARD-10],    5,      FAST_FADE_RATE);
    // Third 5 leds fade at normally
    fadeToBlackBy(&leds[MID_START1_FORWARD+10],     5,      MEDIUM_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_FORWARD+10],     5,      MEDIUM_FADE_RATE);
    fadeToBlackBy(&leds[MID_START1_BACKWARD-15],    5,      MEDIUM_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_BACKWARD-15],    5,      MEDIUM_FADE_RATE);
    // Fourth 5 leds fade slowly
    fadeToBlackBy(&leds[MID_START1_FORWARD+15],     5,      SLOW_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_FORWARD+15],     5,      SLOW_FADE_RATE);
    fadeToBlackBy(&leds[MID_START1_BACKWARD-20],    5,      SLOW_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_BACKWARD-20],    5,      SLOW_FADE_RATE);
    // Fifth 5 leds fade very slowly
    fadeToBlackBy(&leds[MID_START1_FORWARD+20],     5,      VERY_SLOW_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_FORWARD+20],     5,      VERY_SLOW_FADE_RATE);
    fadeToBlackBy(&leds[MID_START1_BACKWARD-25],    5,      VERY_SLOW_FADE_RATE);
    fadeToBlackBy(&leds[MID_START2_BACKWARD-25],    5,      VERY_SLOW_FADE_RATE);

    // --------- FIRST TWO OCTAVES --------
    uint8_t BASS_MAX = ((fht_oct_out[0]+fht_oct_out[1]-100)/5);//+fht_oct_out[2]-120)/8);
    if (fht_oct_out[0]+fht_oct_out[1] < 100){
      BASS_MAX = 1;
    }

    CHSV bass_color = CHSV(130, 255, 255);
    // Show the lowest ocatve in the middle left/right strips
    for (int i = 0; (i < 25 && i < BASS_MAX); i++) {
      leds[BASS_MID_SIDE+i] = bass_color;
      leds[BASS_MID_SIDE-i] = bass_color;
      leds[BASS_MID_FRONT+i] = bass_color;
      leds[BASS_MID_FRONT-i] = bass_color;
      bass_color.hue += 7;
    }

   // -------- THIRD AND FOURTH OCTAVES ------
   uint8_t MID_MAX = ((fht_oct_out[4]+fht_oct_out[5]-30)/4);
   if (fht_oct_out[4]+fht_oct_out[5] < 50){
     MID_MAX = 1;
   }


   CHSV mid_color = CHSV(210, 255, 255);
   // Show the lowest ocatve in the middle left/right strips
   for (int i = 0; (i < 25 && i < MID_MAX); i++) {
     leds[MID_START1_FORWARD+i]   = mid_color;
     leds[MID_START1_BACKWARD-i]  = mid_color;
     leds[MID_START2_BACKWARD-i]  = mid_color;
     leds[MID_START2_FORWARD+i]   = mid_color;
     mid_color.hue += 7;
   }

   /*
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
   */
}




#endif
