#include "includes.h"

void setup() {

  // Set up serial connection
  Serial.begin(SERIAL_BAUDRATE); 
  Serial.setTimeout(SERIAL_TIMEOUT);
  
  delay(1000);  

  // Set up LEDS
  LEDS.setBrightness(max_bright);
  LEDS.addLeds<LED_TYPE, LED_PIN_ONE, COLOR_ORDER >(leds, NUM_LEDS);
  LEDS.addLeds<LED_TYPE, LED_PIN_TWO, COLOR_ORDER >(leds, NUM_LEDS);
  set_max_power_in_volts_and_milliamps(5, 1000);

  // Set up variables
  random16_set_seed(4832);
  random16_add_entropy(analogRead(2));
  int ranstart = random16();

  Serial.println("---SETUP COMPLETE---");
 
  // Load starting mode and number of leds
  ledMode = EEPROM.read(STARTMODE);   

  // Set up palettes
  currentPalette  = CRGBPalette16(CRGB::Black);
  targetPalette   = RainbowColors_p;
  currentBlending = LINEARBLEND;

  // Set up circ_noise variables
  for (uint8_t i = 0; i < NUM_LEDS; i++) {  
    uint8_t angle = (i * 256) / NUM_LEDS;  
    xd[i] = cos8( angle );                
    yd[i] = sin8( angle );               
  }
 
  // Init first mode
  strobe_mode(ledMode, 1);
}

void loop() {
 
  // Get keyboard input
  readkeyboard();
 
  // Palette transitions - always running
  EVERY_N_MILLISECONDS(50) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   
  }
  
  EVERY_N_SECONDS(5) {   
    if (palchg == 1) SetupSimilar4Palette();
    if (palchg == 2) SetupRandom4Palette();
    if (palchg == 3) SetupRandom16Palette();
  }

  // Dynamically change delay
  EVERY_N_MILLIS_I(thistimer, thisdelay) {
    thistimer.setPeriod(thisdelay); 
    strobe_mode(ledMode, 0);
  }

  // Optionally add glitter
  if(glitter) addglitter(10); 

  FastLED.show(); 
}

/*
 * Sets the mode/routine for the LEDs.
 *
 * @param newMode : the mode to set the leds to
 * @param mc      : signifies if we're changing modes or not
 */

void strobe_mode(uint8_t newMode, bool mc){

  // If this is a *new* mode, clear out LED array.
  if(mc) {
    fill_solid(leds, NUM_LEDS, CRGB( 0, 0, 0));
    Serial.print("Mode: "); 
    Serial.println(ledMode);
  }

  switch (newMode) {

    // 0 - all of
    case  0: 
      if(mc) { fill_solid(leds, NUM_LEDS, CRGB( 0, 0, 0 ));} 
      break;

    // 1 - all on
    case  1: 
      if(mc) { fill_solid(leds, NUM_LEDS, CRGB( 255, 255, 255 ));} 
      break;

    // 2 - two-sin
    case  2: 
      if(mc) { thisdelay=10; allfreq=2; thisspeed=1; thatspeed=1; thishue=0; thathue=128; thisdir=0; thisrot=1; thatrot=1; thiscutoff=128; thatcutoff=192;} 
      two_sin(); 
      break;

    // 3 - one-sin with rainbow pallete
    case  3: 
      if(mc) { thisdelay=20; targetPalette=RainbowColors_p; allfreq=4; bgclr=0; bgbri=0; thisbright=255; startindex=64; thisinc=2; thiscutoff=224; thisphase=0; thiscutoff=224; thisrot=0; thisspeed=4; wavebright=255; } 
      one_sin_pal(); 
      break;

    // 4 - noise8 with party palette
    case  4: 
      if(mc) { thisdelay=10; targetPalette = PartyColors_p; palchg=2; } 
      noise8_pal(); 
      break;

    // 5 - two-sin
    case  5: 
      if(mc) { thisdelay=10; allfreq=4; thisspeed=-1; thatspeed=0; thishue=64; thathue=192; thisdir=0; thisrot=0; thatrot=0; thiscutoff=64; thatcutoff=192; } 
      two_sin(); 
      break;

    // 6 - one-sin with rainbow palette
    case  6: 
      if(mc) { thisdelay=20; targetPalette=RainbowColors_p; allfreq=10; bgclr=64; bgbri=4; thisbright=255; startindex=64; thisinc=2; thiscutoff=224; thisphase=0; thiscutoff=224; thisrot=0; thisspeed=4; wavebright=255; } 
      one_sin_pal(); 
      break;

    case  7: 
      if(mc) { thisdelay=10; numdots=2; targetPalette=PartyColors_p; thisfade=16; thisbeat=8; thisbright=255; thisdiff=64; } 
      juggle_pal(); 
      break;

    case  8: 
      if(mc) { thisdelay=40; targetPalette = LavaColors_p; thisindex=128; thisdir=1; thisrot=0; thisbright=255; bgclr=200; bgbri=6; } 
      matrix_pal(); 
      break;

    case  9: 
      if(mc) { thisdelay=10; allfreq=6; thisspeed=2; thatspeed=3; thishue=96; thathue=224; thisdir=1; thisrot=0; thatrot=0; thiscutoff=64; thatcutoff=64; } 
      two_sin(); 
      break;

    case 10: 
      if(mc) { thisdelay=20; targetPalette=RainbowColors_p; allfreq=16; bgclr=0; bgbri=0; thisbright=255; startindex=64; thisinc=2; thiscutoff=224; thisphase=0; thiscutoff=224; thisrot=0; thisspeed=4; wavebright=255; } 
      one_sin_pal(); 
      break;

    case 11: 
      if(mc) {thisdelay=50; mul1=5; mul2=8; mul3=7;} three_sin_pal(); break;
    case 12: if(mc) {thisdelay=10; targetPalette=ForestColors_p;} serendipitous_pal(); break;
    case 13: if(mc) {thisdelay=20; targetPalette=LavaColors_p; allfreq=8; bgclr=0; bgbri=4; thisbright=255; startindex=64; thisinc=2; thiscutoff=224; thisphase=0; thiscutoff=224; thisrot=0; thisspeed=4; wavebright=255;} one_sin_pal(); break;
    case 14: if(mc) {thisdelay=10; allfreq=20; thisspeed=2; thatspeed=-1; thishue=24; thathue=180; thisdir=1; thisrot=0; thatrot=1; thiscutoff=64; thatcutoff=128;} two_sin(); break;
    case 15: if(mc) {thisdelay=50; targetPalette = PartyColors_p; thisindex=64; thisdir=0; thisrot=1; thisbright=255; bgclr=100; bgbri=10;} matrix_pal(); break;
    case 16: if(mc) {thisdelay=10; targetPalette = OceanColors_p; palchg=1;} noise8_pal(); break;
    case 17: if(mc) {thisdelay=10; targetPalette=PartyColors_p;} circnoise_pal_2(); break;
    case 18: if(mc) {thisdelay=20; allfreq=10; thisspeed=1; thatspeed=-2; thishue=48; thathue=160; thisdir=0; thisrot=1; thatrot=-1; thiscutoff=128; thatcutoff=192;} two_sin(); break;
    case 19: if(mc) {thisdelay=50; mul1=6; mul2=9; mul3=11;} three_sin_pal(); break;
    case 20: if(mc) {thisdelay=10; thisdir=1; thisrot=1; thisdiff=1;} rainbow_march(); break;
    case 21: if(mc) {thisdelay=10; thisdir=1; thisrot=2; thisdiff=10;} rainbow_march(); break;
    case 22: if(mc) {thisdelay=20; hxyinc = random16(1,15); octaves=random16(1,3); hue_octaves=random16(1,5); hue_scale=random16(10, 50);  x=random16(); xscale=random16(); hxy= random16(); hue_time=random16(); hue_speed=random16(1,3); x_speed=random16(1,30);} noise16_pal(); break;
    case 23: if(mc) {thisdelay=20; targetPalette=OceanColors_p; allfreq=6; bgclr=0; bgbri=0; thisbright=255; startindex=64; thisinc=2; thiscutoff=224; thisphase=0; thiscutoff=224; thisrot=0; thisspeed=4; wavebright=255;} one_sin_pal(); break;
    case 24: if(mc) {thisdelay=10; targetPalette=OceanColors_p;} circnoise_pal_4(); break;
    case 25: if(mc) {thisdelay=20; targetPalette = PartyColors_p; thisinc=1; thishue=192; thissat=255; thisfade=2; thisdiff=32; thisbright=255;} confetti_pal(); break;
    case 26: if(mc) {thisdelay=10; thisspeed=2; thatspeed=3; thishue=96; thathue=224; thisdir=1; thisrot=1; thatrot=2; thiscutoff=128; thatcutoff=64;} two_sin(); break;
    case 27: if(mc) {thisdelay=30; targetPalette = ForestColors_p; thisindex=192; thisdir=0; thisrot=0; thisbright=255; bgclr=50; bgbri=0;} matrix_pal(); break;
    case 28: if(mc) {thisdelay=20; targetPalette=RainbowColors_p; allfreq=20; bgclr=0; bgbri=0; thisbright=255; startindex=64; thisinc=2; thiscutoff=224; thisphase=0; thiscutoff=224; thisrot=0; thisspeed=4; wavebright=255;} one_sin_pal(); break;
    case 29: if(mc) {thisdelay=20; targetPalette = LavaColors_p; thisinc=2; thishue=128; thisfade=8; thisdiff=64; thisbright=255;} confetti_pal(); break;
    case 30: if(mc) {thisdelay=10; targetPalette=PartyColors_p;} circnoise_pal_3(); break;
    case 31: if(mc) {thisdelay=10; numdots=4; targetPalette=OceanColors_p; thisfade=32; thisbeat=12; thisbright=255; thisdiff=20;} juggle_pal(); break;
    case 32: if(mc) {thisdelay=30; SetupSimilar4Palette(); allfreq=4; bgclr=64; bgbri=4; thisbright=255; startindex=64; thisinc=2; thiscutoff=224; thisphase=0; thiscutoff=128; thisrot=1; thisspeed=8; wavebright=255;} one_sin_pal(); break;
    case 33: if(mc) {thisdelay=50; mul1=3; mul2=4; mul3=5;} three_sin_pal(); break;
    case 34: if(mc) {thisdelay=10; thisdir=-1; thisrot=1; thisdiff=5;} rainbow_march(); break;
    case 35: if(mc) {thisdelay=10; targetPalette=PartyColors_p;} circnoise_pal_1(); break;
    case 36: if(mc) {thisdelay=20; targetPalette = ForestColors_p; thisinc=1; thishue=random8(255); thisfade=1; thisbright=255;} confetti_pal(); break;
    case 37: if(mc) {thisdelay=20; octaves=1; hue_octaves=2; hxy=6000; x=5000; xscale=3000; hue_scale=50; hue_speed=15; x_speed=100;} noise16_pal(); break;
    case 38: if(mc) {thisdelay=10; targetPalette = LavaColors_p; palchg=0;} noise8_pal(); break;
  }
}

//----------------- IR Receiver, Keyboard and Button Command Processing ---------------------------------------------

void readkeyboard() {                                         // Process serial commands
  while (Serial.available() > 0) {
  
    in_byte = Serial.read();                                   // Read the command

    if (in_byte != 10) {                                       // Don't print out the separate carriage return.
      Serial.print("# ");
      Serial.print(char(in_byte));
      Serial.print(" ");
    }
    
    switch(in_byte) {

      case 97:                                                // "a" - SET ALL TO ONE colour BY hue = 0 - 255
        ledMode = 0;
        this_arg = Serial.parseInt();
        this_arg = constrain(this_arg,0,255);
        Serial.println(this_arg);
        fill_solid(leds, NUM_LEDS, CHSV(this_arg, 255, 255));
        break;

      case 98:                                                // "b" - SET MAX BRIGHTNESS to #
        max_bright = Serial.parseInt();
        max_bright = constrain(max_bright,0,255);        
        Serial.println(max_bright);
        LEDS.setBrightness(max_bright);
        break;

      case 99:                                                // "c" - CLEAR STRIP
        Serial.println(" ");
        ledMode = 0;
        strobe_mode(ledMode, 1);
        break;

      case 100:                                               // "d" - SET DELAY VAR to #
        this_arg = Serial.parseInt();
        thisdelay = constrain(this_arg,0,255);
        Serial.println(thisdelay);
        break;

      case 101:                                              // "e" - SET PREVIOUS / NEXT mode

        this_arg = Serial.parseInt();
        if (this_arg) {
          demorun = 0; ledMode=(ledMode+1)%(maxMode+1);
        } else {
         demorun = 0; ledMode=(ledMode-1); if (ledMode==255) ledMode=maxMode; 
        }
        strobe_mode(ledMode,1);
        break;

      case 102:                                               // "f - Set a fixed palette
        demorun = 0;
        palchg = 0;
        this_arg = Serial.parseInt();
        gCurrentPaletteNumber = this_arg % gGradientPaletteCount;
        targetPalette = gGradientPalettes[gCurrentPaletteNumber];
        Serial.println(gCurrentPaletteNumber);
        break;

      case 103:                                               // "g" - TOGGLE glitter
        glitter = !glitter;
        Serial.println(" ");
        break;

      case 104:                                               // "h" - SET HUE VAR to #
        this_arg = Serial.parseInt();
        thishue = constrain(this_arg,0,255);
        Serial.println(thishue);
        break;

      case 105:                                               // "i" - Set Similar Palette with hue selection
        palchg = 0;
        this_arg = Serial.parseInt();
        thishue = constrain(this_arg,0,255);
        Serial.println(thishue);
        SetupMySimilar4Palette();
        break;

      case 109:                                               // "m" - SET MODE to #
        ledMode = Serial.parseInt();
        ledMode = constrain(ledMode,0,maxMode);
        Serial.println(ledMode);
        strobe_mode(ledMode, 1);
        break;

      case 110:                                               // "n"  - TOGGLE direction
        Serial.println(" ");
        thisdir = !thisdir;
        break;

      case 112:                                               // "p" - Play mode is either fixed, sequential or shuffle
        demorun = Serial.parseInt();
        demorun = constrain(demorun,0,2);
        Serial.println(demorun);        
        break;      
      
      case 115:                                               // "s"  SET SATURATION VAR to #
        this_arg = Serial.parseInt();
        thissat = constrain(this_arg,0,255);
        Serial.println(thissat);
        break;

      case 116:                                               // "t" - Select Palette mode
        this_arg = Serial.parseInt();
        palchg = constrain(this_arg,0,3);
        Serial.println(palchg);
        break;

      case 119:                                               // "w" - Write current mode to EEPROM
        EEPROM.write(STARTMODE,ledMode);
        Serial.print("Writing keyboard: ");
        Serial.println(ledMode);
        break;   
        
    } // switch inbyte
  } // while Serial.available
  
} // readkeyboard()
