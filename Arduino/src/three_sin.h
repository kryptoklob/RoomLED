#ifndef THREE_SIN_H
#define THREE_SIN_H

// Vars
int wave1=0;
int wave2=0;
int wave3=0;

uint8_t inc1 = 2;
uint8_t inc2 = 1;
uint8_t inc3 = -3;

uint8_t lvl1 = 80;
uint8_t lvl2 = 80;
uint8_t lvl3 = 80;

uint8_t mul1 = 20;
uint8_t mul2 = 25;
uint8_t mul3 = 22;

// Function
void three_sin() {
  wave1 += inc1;
  wave2 += inc2;
  wave3 += inc3;
  for (int k=0; k<NUM_LEDS; k++) {
    leds[k].r = qsub8(sin8(mul1*k + wave1), lvl1);         // Another fixed frequency, variable phase sine wave with lowered level
    leds[k].g = qsub8(sin8(mul2*k + wave2), lvl2);         // A fixed frequency, variable phase sine wave with lowered level
    leds[k].b = qsub8(sin8(mul3*k + wave3), lvl3);         // A fixed frequency, variable phase sine wave with lowered level
  }
} // three_sin()

#endif
