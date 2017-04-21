#ifndef SOUNDAMP_H
#define SOUNDAMP_H



void soundamp() {

  int n;
  n = analogRead(MIC_PIN);
  n = qsuba(abs(n-512), 10);
  // Let's make the colors brighter
  n = n * 2;

  fill_solid_HSV(n, 255, n);
}

#endif
