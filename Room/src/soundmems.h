#ifndef SOUNDMEMS_H
#define SOUNDMEMS_H

void soundmems() {

  int n;
  n = analogRead(MIC_PIN);
  n = qsuba(abs(n-512), 10);
  //  Serial.println(n);
  nblend(leds[0], CHSV(n,255,n), 128);
  for (int i = NUM_LEDS-1; i>0; i--) {
    leds[i] = leds[i-1];
  }
}

#endif
