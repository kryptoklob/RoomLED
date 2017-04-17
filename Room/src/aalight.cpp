#include "headerfile.h"
#include "variables.h"

/*

Much thanks to Andrew Tuline for most of this codebase: https://github.com/atuline

*/

void setup() {
  analogReference(EXTERNAL);

  Serial.begin(SERIAL_BAUDRATE);
  Serial.setTimeout(SERIAL_TIMEOUT);

  LEDS.setBrightness(max_bright);



  LEDS.addLeds<LED_TYPE, LED_DT_LEFT, COLOR_ORDER>(leds, 0, LEFTNO);
  LEDS.addLeds<LED_TYPE, LED_DT_RIGHT, COLOR_ORDER>(leds, 0, LEFTNO);

  LEDS.addLeds<LED_TYPE, LED_DT_FRONT, COLOR_ORDER>(leds, LEFTNO, FRONTNO);
  LEDS.addLeds<LED_TYPE, LED_DT_BACK, COLOR_ORDER>(leds, LEFTNO, FRONTNO);


  set_max_power_in_volts_and_milliamps(5, 500);

  random16_set_seed(4832);
  random16_add_entropy(analogRead(2));

  Serial.println(F("---SETUP COMPLETE---"));
  call_mode(ledMode, 1);
}

void loop() {
  readkeyboard();
  call_mode(ledMode, 0);
  show_at_max_brightness_for_power();
  //delay_at_max_brightness_for_power(2.5*thisdelay);
}


void call_mode(int newMode, int mc){

   maxMode = 41;
   if(mc) fill_solid(leds,NUM_LEDS,CRGB(0,0,0));              // Clean up the array for the first time through. Don't show display though, so you may have a smooth transition.

  switch (newMode) {                                          // First time through a new mode, so let's initialize the variables for a given display.

    case  0: if(mc) {fill_solid(leds,NUM_LEDS,CRGB(0,0,0)); LEDS.show();} LEDS.show(); break;              // All off, not animated.
    case  1: if(mc) {fill_solid(leds, NUM_LEDS,CHSV(thishue, thisbright, thissat)); LEDS.show();} LEDS.show(); break;              // All on, not animated.
    case  2: if(mc) {thisdelay=20; twinkrate=NUM_LEDS; thishue=0; thissat=255; thisbright=255; thisfade=255; } twinkle(); break;
    case  3: if(mc) {thisdelay=10; thisrot=1; thatrot=1;} two_sin(); break;
    case  4: if(mc) {thisdelay=10; thisrot=0; thisdir=1;} two_sin(); break;
    case  5: if(mc) {thisdelay=10; thatrot=0; thishue=255; thathue=255;} two_sin(); break;
    case  6: if(mc) {thisdelay=10; allfreq=16; thathue=128;} two_sin(); break;
    case  7: if(mc) {thisdelay=10; thiscutoff=96; thishue=196; thatcutoff=240;} two_sin(); break;
    case  8: if(mc) {thisdelay=10; thiscutoff=96; thatcutoff=96; thisrot=1;} two_sin(); break;
    case  9: if(mc) {thisdelay=10; thisspeed= -4; thatspeed= -4;} two_sin(); break;
    case 10: if(mc) {thisdelay=10; thiscutoff=128; thatcutoff=128; wavebright=64;} two_sin(); break;
    case 11: if(mc) {thisdelay=10; wavebright=128; thisspeed=3;} two_sin(); break;
    case 12: if(mc) {thisdelay=10; thisspeed=3; thatspeed=-3;} two_sin(); break;
    case 13: if(mc) {thisdelay=30; thishue=95; bgclr=100; bgbri=10;} matrix(); break;
    case 14: if(mc) {thisdelay=30; thishue=40; thisdir=1; bgclr=75;} matrix(); break;
    case 15: if(mc) {thisdelay=30; thishue=random8(); huerot=1; bgbri=0;} matrix(); break;
    case 16: if(mc) {thisdelay=20; thisrot=1; thiscutoff=254; allfreq=8; bgclr=0; bgbri=10;} one_sin(); break;
    case 17: if(mc) {thisdelay=20; thisrot=0; bgclr=50;} one_sin(); break;
    case 18: if(mc) {thisdelay=20; thishue=255; bgclr=100; bgbri=40;} one_sin(); break;
    case 19: if(mc) {thisdelay=20; allfreq=16; bgbri=0;} one_sin(); break;
    case 20: if(mc) {thisdelay=20; thiscutoff=96; bgclr=200; bgbri=20;} one_sin(); break;
    case 21: if(mc) {thisdelay=20; thiscutoff=128; wavebright=64;} one_sin(); break;
    case 28: if(mc) {thisdelay=20; mul1=20; mul2=25; mul3=22;} three_sin(); break;
    case 29: if(mc) {thisdelay=20; mul1=5; mul2=8; mul3=7;} three_sin(); break;
    case 30: if(mc) {thisdelay=20; lvl1=220; lvl2=220; lvl3=220;} three_sin(); break;
    case 31: if(mc) {thisdelay=10; thisrot=1; deltahue=5;} rainbow_march(); break;
    case 32: if(mc) {thisdelay=10; thisdir=-1; deltahue=10;} rainbow_march(); break;
    case 33: if(mc) {thisdelay=10; thisrot=5;} rainbow_march(); break;
    case 34: if(mc) {thisdelay=10; thisrot=5; thisdir=-1; deltahue=20;} rainbow_march(); break;
    case 35: if(mc) {thisdelay=10; deltahue=30;} rainbow_march(); break;
    case 36: if(mc) {thisdelay=10; deltahue=2; thisrot=5;} rainbow_march(); break;
    case 37: if(mc) {thisdelay=20; octaves=1; hue_octaves=2; hxy=6000; x=5000; xscale=3000; hue_scale=50; hue_speed=15; x_speed=100;} noise16(); break;
    case 38: if(mc) {thisdelay=20; hxyinc = random16(1,15); octaves=random16(1,3); hue_octaves=random16(1,5); hue_scale=random16(10, 50);  x=random16(); xscale=random16(); hxy= random16(); hue_time=random16(); hue_speed=random16(1,3); x_speed=random16(1,30);} noise16(); break;
    case 39: if(mc) {thisdelay=20; thishue = 20;} confetti(); break;
    case 40: if(mc) {thisdelay=20; thishue = 50;} sinelon(); break;
    case 41: if(mc) {thisdelay=10;} juggle(); break;
    case 43: if(mc) {thisdelay=20;} lightnings(); break;
    case 44: if(mc) {thisdelay=0;} soundmems(); break;
    case 45: if(mc) {thisdelay=0;} soundamp(); break;
    //case 46: if(mc) {thisdelay=20;} soundripple(); break;
    case 47: if(mc) {thisdelay=20;} soundfhtlog(); break;

    // DEMO MODE
    case 99: ; break;

  } // switch newMode

  ledMode = newMode;
} // change_mode()


//----------------- Hardware Support Functions ---------------------------------------------

void readkeyboard() {                                         // PROCESS HARDWARE SERIAL COMMANDS AND ARGS
  while (Serial.available() > 0) {

    inbyte = Serial.read();                                   // READ SINGLE BYTE COMMAND
    Serial.print(F("Serial read is: "));
    Serial.println(inbyte);
    switch(inbyte) {

      case 97:                                                // "a" - SET ALL TO ONE COLOR BY HSV 0-255
        thisarg = Serial.parseInt();
        Serial.println(F("Argument Received:"));
        Serial.println(thisarg);
        thissat = 255;
        thisbright = 255;
        fill_solid_HSV(thisarg, thissat, thisbright);
        break;

      case 98:                                                // "b" - SET MAX BRIGHTNESS to #
        max_bright = Serial.parseInt();
        Serial.println(F("Argument Received:"));
        Serial.println(max_bright);
        LEDS.setBrightness(max_bright);
        break;

      case 104:                                               // "h" - SET HUE VAR to #
        thisarg = Serial.parseInt();
        Serial.println(F("Argument Received:"));
        Serial.println(thisarg);
        thishue = thisarg;
        break;

      case 109:
        Serial.println(F("Mode change requested."));
        thisarg = Serial.parseInt();
        Serial.println(F("Argument Received:"));
        Serial.println(thisarg);
        call_mode(thisarg, 1);
        break;

    }
  }
}

//---------------------- LED Utility Functions ---------------------------------------------

int wrap(int step) {
  if(step < 0) return NUM_LEDS + step;
  if(step > NUM_LEDS - 1) return step - NUM_LEDS;
  return step;
}

void fill_solid_HSV(uint8_t ahue, uint8_t asat, uint8_t abright) {  // Set all LED's to an HSV value.
  for(int i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i] = CHSV(ahue, asat, abright);
  }
}  // fill_solid_HSV()
