#ifndef SOUNDAMP_H
#define SOUNDAMP_H

void fill_solid_HSV(uint8_t ahue, uint8_t asat, uint8_t abright) {  // Set all LED's to an HSV value.
  for(int i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i] = CHSV(ahue, asat, abright);
  }
}  // fill_solid_HSV()

void soundamp() {

  int n;
  n = analogRead(MIC_PIN);
  n = qsuba(abs(n-512), 10);
  // Let's make the colors brighter
  n = n * 2;

  fill_solid_HSV(n, 255, n);
}

#endif
