#ifndef SINELON_H
#define SINELON_H

/* This is adapted from a routine created by Mark Kriegsman */

void sinelon() {                                              // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int leftpos = beatsin16(13,0,LEFTNO);
  int rightpos = beatsin16(13,0,RIGHTNO) + FRONTNO + LEFTNO;
  int frontpos = beatsin16(13,0,FRONTNO) + LEFTNO;
  int backpos = beatsin16(13,0,BACKNO) + LEFTNO + FRONTNO + RIGHTNO;
  leds[leftpos] += CHSV( thishue, 255, 192);
  leds[rightpos] += CHSV( thishue, 255, 192);
  leds[frontpos] += CHSV( thishue, 255, 192);
  leds[backpos] += CHSV( thishue, 255, 192);
  thishue++;
}

/*

Note that we have to edit this because we want a cylon on EACH side of the room, not just on the whole strip!

*/

#endif
