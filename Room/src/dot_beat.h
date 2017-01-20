#ifndef DOT_BEAT_H
#define DOT_BEAT_H

/* This is adapted from a routine created by Mark Kriegsman */
uint8_t bpm = 30;

void dot_beat() {

  uint8_t inner = beatsin8(bpm, NUM_LEDS/4, NUM_LEDS/4*3);
  uint8_t outer = beatsin8(bpm, 0, NUM_LEDS-1);
  uint8_t middle = beatsin8(bpm, NUM_LEDS/3, NUM_LEDS/3*2);

  leds[middle] = CRGB::Purple;
  leds[inner] = CRGB::Blue;
  leds[outer] = CRGB::Aqua;

  nscale8(leds,NUM_LEDS,fadeval);                             // Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);
} // dot_beat()
