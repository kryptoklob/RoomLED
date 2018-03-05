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
  bass_pot_modifier = 0;
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
  /* Bass in middle of the LED strip,
   * lows on the ends of the LED strip,
   * mids in between them.              */

  uint8_t UNIT_WIDTH            = NUM_LEDS_PER_STRIP/8;
  uint8_t PIECE_WIDTH           = UNIT_WIDTH/2;

  uint8_t BASS_START            = NUM_LEDS_PER_STRIP/2 - UNIT_WIDTH;
  uint8_t MID_START_ONE         = NUM_LEDS_PER_STRIP/4 - PIECE_WIDTH;
  uint8_t MID_START_TWO         = ( NUM_LEDS_PER_STRIP - NUM_LEDS_PER_STRIP/4 ) - PIECE_WIDTH;
  uint8_t HIGH_START_ONE        = 0;
  uint8_t HIGH_START_TWO        = NUM_LEDS_PER_STRIP - PIECE_WIDTH;

  // BASS FADES --------------------------------------------------------------
  fadeToBlackBy(&leds[BASS_START],        UNIT_WIDTH*2,   MEDIUM_FADE_RATE);

  // MID FADES ---------------------------------------------------------------
  fadeToBlackBy(&leds[MID_START_ONE],     UNIT_WIDTH,     FAST_FADE_RATE);
  fadeToBlackBy(&leds[MID_START_TWO],     UNIT_WIDTH,     FAST_FADE_RATE);
 
  // HIGH FADES --------------------------------------------------------------
  fadeToBlackBy(&leds[HIGH_START_ONE],    UNIT_WIDTH,     FAST_FADE_RATE);
  fadeToBlackBy(&leds[HIGH_START_TWO],    UNIT_WIDTH,     FAST_FADE_RATE);

  // todo continue from here


  int BASS_MAX = ((fht_oct_out[0]+fht_oct_out[1]+fht_oct_out[2]-195)/(8-bass_pot_modifier));
  if (BASS_MAX <= 0){
    BASS_MAX = 1;
  }

  int MID_MAX = ((fht_oct_out[3]+fht_oct_out[4]-87)/(4-mid_pot_modifier));
  if (MID_MAX <= 0){
    MID_MAX = 1;
  }

  CHSV bass_color = CHSV(130, 255, 255);
  CHSV mid_color = CHSV(210, 255, 255);

  uint8_t BASS_MID = 75;
  uint8_t MID_START1 = 37;
  uint8_t MID_START2 = 112;

  // --------- LOWS --------

  for (int i = 0; (i < 25 && i < BASS_MAX); i++) {
    leds[BASS_MID+i] = bass_color;
    leds[BASS_MID-i] = bass_color;
    bass_color.hue += 7;
  }

  // -------- MIDS ------

  for (int i = 0; (i < 25 && i < MID_MAX); i++) {
   leds[MID_START1+i]   = mid_color;
   leds[MID_START1-i]  = mid_color;
   leds[MID_START2-i]  = mid_color;
   leds[MID_START2+i]   = mid_color;
   mid_color.hue += 7;
  }
}

#endif
