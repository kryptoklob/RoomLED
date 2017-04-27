#ifndef SOUNDFHT_H
#define SOUNDFHT_H


// Defines
#define LOG_OUT 1                                             // Use logarithmic based bins
#define OCTAVE 1                                              // Use octave mode
#define FHT_N 256                                             // Set to 256 point fht.
#define OCT_NORM 0                                            // Octave normalization

// Vars
int bass_pot_modifier = 0;
int mid_pot_modifier = 0;

// This include must come after the defines to work properly.
#include <FHT.h>

// Function prototypes
void GetFHT();
void display();
void soundfhtlog();
void getPot();

// Functions
void getPot() {
  int potRead = analogRead(POT_PIN);
  mid_pot_modifier = (potRead/128) - 4;
  bass_pot_modifier = mid_pot_modifier * 2;
}

void GetFHT() {

  cli();
  for (int i = 0 ; i < 255 ; i++) {
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
  getPot();
  GetFHT();
  display();
}

/* Octave Baseline Measurements:
Bass Octaves:
Octave 0: 89
Octave 1: 68
Octave 2: 38
Total: 195
Mid Octaves:
Octave 3: 42
Octave 4: 45
Total: 87
High Octaves:
Octave 5: 51
Octave 6: 55
Octave 7: 54
Total: 160
*/

void display() {
  // Index vars
  uint8_t BASS_MID_SIDE       = LEFTNO/2;
  uint8_t BASS_MID_FRONT      = LEFTNO + FRONTNO/2;
  uint8_t MID_START1_FORWARD  = LEFTNO;
  uint8_t MID_START1_BACKWARD = LEFTNO+FRONTNO-1;
  uint8_t MID_START2_FORWARD  = 0;
  uint8_t MID_START2_BACKWARD = LEFTNO-1;

  // BASS FADES --------------------------------------------------------------
  fadeToBlackBy(&leds[BASS_MID_SIDE-25],          50,     MEDIUM_FADE_RATE);
  fadeToBlackBy(&leds[BASS_MID_FRONT-25],         50,     MEDIUM_FADE_RATE);

  // MID FADES ---------------------------------------------------------------
  // First 5 leds fade instantly
  fadeToBlackBy(&leds[MID_START1_FORWARD],        5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START2_FORWARD],        5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START1_BACKWARD-5],     5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START2_BACKWARD-5],     5,      FAST_FADE_RATE);
  // Second 5 leds fade quickly
  fadeToBlackBy(&leds[MID_START1_FORWARD+5],      5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START2_FORWARD+5],      5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START1_BACKWARD-10],    5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START2_BACKWARD-10],    5,      FAST_FADE_RATE);
  // Third 5 leds fade at normally
  fadeToBlackBy(&leds[MID_START1_FORWARD+10],     5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START2_FORWARD+10],     5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START1_BACKWARD-15],    5,      FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START2_BACKWARD-15],    5,      FAST_FADE_RATE);
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

  int BASS_MAX = ((fht_oct_out[0]+fht_oct_out[1]+fht_oct_out[2]-195)/(8-bass_pot_modifier);
  if (BASS_MAX <= 0){
    BASS_MAX = 1;
  }

  int MID_MAX = ((fht_oct_out[3]+fht_oct_out[4]-87)/(4-mid_pot_modifier);
  if (MID_MAX <= 0){
    MID_MAX = 1;
  }

  CHSV bass_color = CHSV(130, 255, 255);
  CHSV mid_color = CHSV(210, 255, 255);

  // --------- LOWS --------

  for (int i = 0; (i < 25 && i < BASS_MAX); i++) {
    leds[BASS_MID_SIDE+i] = bass_color;
    leds[BASS_MID_SIDE-i] = bass_color;
    leds[BASS_MID_FRONT+i] = bass_color;
    leds[BASS_MID_FRONT-i] = bass_color;
    bass_color.hue += 7;
  }

  // -------- MIDS ------

  for (int i = 0; (i < 25 && i < MID_MAX); i++) {
   leds[MID_START1_FORWARD+i]   = mid_color;
   leds[MID_START1_BACKWARD-i]  = mid_color;
   leds[MID_START2_BACKWARD-i]  = mid_color;
   leds[MID_START2_FORWARD+i]   = mid_color;
   mid_color.hue += 7;
  }
}




#endif
