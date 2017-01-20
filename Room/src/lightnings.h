#ifndef LIGHTNINGS_H
#define LIGHTNINGS_H

/* This is adapted from a routine created by Mark Kriegsman */

uint8_t frequency = 50;                                       // controls the interval between strikes
uint8_t flashes = 8;                                          //the upper limit of flashes per strike
unsigned int dimmer = 1;
uint8_t ledstart;                                             // Starting location of a flash
uint8_t ledlen;

void lightnings() {                                              // a colored dot sweeping back and forth, with fading trails
    ledstart = random8(NUM_LEDS);           // Determine starting location of flash
    ledlen = random8(NUM_LEDS-ledstart);    // Determine length of flash (not to go beyond NUM_LEDS-1)
    for (int flashCounter = 0; flashCounter < random8(3,flashes); flashCounter++) {
      if(flashCounter == 0) dimmer = 5;     // the brightness of the leader is scaled down by a factor of 5
      else dimmer = random8(1,3);           // return strokes are brighter than the leader
      fill_solid(leds+ledstart,ledlen,CHSV(255, 0, 255/dimmer));
      FastLED.show();                       // Show a section of LED's
      delay(random8(4,10));                 // each flash only lasts 4-10 milliseconds
      fill_solid(leds+ledstart,ledlen,CHSV(255,0,0));   // Clear the section of LED's
      FastLED.show();
      if (flashCounter == 0) delay (150);   // longer delay until next flash after the leader
      delay(50+random8(100));               // shorter delay between strokes
    } // for()
    delay(random8(frequency)*100);          // delay between strikes
}

#endif
