#include "includes.h"

void setup() {
  // Set up serial connection
  Serial.begin(SERIAL_BAUDRATE); 
  Serial.setTimeout(SERIAL_TIMEOUT);
  
  delay(1000);  

  // Set up LEDS
	LEDS.setBrightness(max_bright);

  // -- Single strip of 150 LEDS set for development testing ------------------------------- //
  
  LEDS.addLeds<LED_TYPE, LED_PIN_ONE, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP); 

  // --------------------------------------------------------------------------------------- // 

  set_max_power_in_volts_and_milliamps(5, 1000);
  
  // Set up variables
  random16_set_seed(4832);
  random16_add_entropy(analogRead(2));

  Serial.println("---SETUP COMPLETE---");
 
  // Load starting mode and number of leds
  led_mode = EEPROM.read(STARTMODE);   

  // Set up palettes
  current_palette  = CRGBPalette16(CRGB::Black);
  target_palette   = RainbowColors_p;
  current_blending = LINEARBLEND;

  // Set up circ_noise variables
  for (long i = 0; i < NUM_LEDS_PER_STRIP; i++) {  
    uint8_t angle = (i * 256) / NUM_LEDS_PER_STRIP;  
    xd[i] = cos8( angle );                
    yd[i] = sin8( angle );               
  }
 
  // Init first mode
  strobe_mode(led_mode, 1);
}

void loop() {
  // Get keyboard input
  readkeyboard();
 
  // Palette transitions - always running
  EVERY_N_MILLISECONDS(50) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(current_palette, target_palette, maxChanges);   
  }
  
  EVERY_N_SECONDS(5) {   
    if (palette_change == 1) SetupSimilar4Palette();
    if (palette_change == 2) SetupRandom4Palette();
    if (palette_change == 3) SetupRandom16Palette();
  }

  // Dynamically change delay
  EVERY_N_MILLIS_I(this_timer, this_delay) {
    this_timer.setPeriod(this_delay); 
    strobe_mode(led_mode, 0);
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

  // If this_ is a *new* mode, clear out LED array.
  if(mc) {
    fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB( 0, 0, 0));
    Serial.print("Mode: "); 
    Serial.println(led_mode);
  }

  switch (newMode) {

    // 0 - all of
    case  0: 
      if(mc) { fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB( 0, 0, 0 )); } 
      break;

    // 1 - all on
    case  1: 
      if(mc) { fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB( 255, 255, 255 )); } 
      break;

    // 2 - two-sin
    case  2: 
      if(mc) { this_delay = 10; all_freq = 2; this_speed = 1; thatspeed = 1; this_hue = 0; thathue = 128; this_dir = 0; this_rot = 1; thatrot = 1; this_cutoff = 128; thatcutoff = 192; } 
      two_sin(); 
      break;

    // 3 - one-sin with rainbow pallete
    case  3: 
      if(mc) { this_delay = 20; target_palette = RainbowColors_p; all_freq = 4; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 2; this_cutoff = 224; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 4; wave_brightness = 255; } 
      one_sin_pal(); 
      break;

    // 4 - noise8 with party palette
    case  4: 
      if(mc) { this_delay = 10; target_palette = PartyColors_p; palette_change = 2; } 
      noise8_pal(); 
      break;

    // 5 - two-sin
    case  5: 
      if(mc) { this_delay = 10; all_freq = 4; this_speed = -1; thatspeed = 0; this_hue = 64; thathue = 192; this_dir = 0; this_rot = 0; thatrot = 0; this_cutoff = 64; thatcutoff = 192; } 
      two_sin(); 
      break;

    // 6 - one-sin with rainbow palette
    case  6: 
      if(mc) { this_delay = 20; target_palette = RainbowColors_p; all_freq = 10; bg_clr = 64; bg_bri = 4; this_bright = 255; start_index = 64; this_inc = 2; this_cutoff = 224; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 4; wave_brightness = 255; } 
      one_sin_pal(); 
      break;

    // 7 - juggle mode
    case  7: 
      if(mc) { this_delay = 10; numdots = 2; target_palette = PartyColors_p; this_fade = 16; this_beat = 8; this_bright = 255; this_diff = 64; } 
      juggle_pal(); 
      break;

    // 8 - matrix with palette
    case  8: 
      if(mc) { this_delay = 40; target_palette = LavaColors_p; this_index = 128; this_dir = 1; this_rot = 0; this_bright = 255; bg_clr = 200; bg_bri = 6; } 
      matrix_pal(); 
      break;

    // 9 - two-sin
    case  9: 
      if(mc) { this_delay = 10; all_freq = 6; this_speed = 2; thatspeed = 3; this_hue = 96; thathue = 224; this_dir = 1; this_rot = 0; thatrot = 0; this_cutoff = 64; thatcutoff = 64; } 
      two_sin(); 
      break;

    // 10 - one-sin with rainbow palette
    case 10: 
      if(mc) { this_delay = 20; target_palette = RainbowColors_p; all_freq = 16; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 2; this_cutoff = 224; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 4; wave_brightness = 255; } 
      one_sin_pal(); 
      break;

    // 11 - three-sin wiht palette
    case 11: 
      if(mc) { this_delay = 50; mul1 = 5; mul2 = 8; mul3 = 7; }
			three_sin_pal(); 
			break;
   
    // 12 - serendipitous with palette
    case 12:
      if(mc) { this_delay = 10; target_palette = ForestColors_p; }
			serendipitous_pal(); 
			break;
  
    // 13 - one-sine with lava palette
    case 13:
      if(mc) { this_delay = 20; target_palette = LavaColors_p; all_freq = 8; bg_clr = 0; bg_bri = 4; this_bright = 255; start_index = 64; this_inc = 2; this_cutoff = 224; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 4; wave_brightness = 255; }
			one_sin_pal(); 
			break;
 
    // 14 - two-sin
    case 14:
      if(mc) { this_delay = 10; all_freq = 20; this_speed = 2; thatspeed = -1; this_hue = 24; thathue = 180; this_dir = 1; this_rot = 0; thatrot = 1; this_cutoff = 64; thatcutoff = 128; }
			two_sin(); 
			break;

    // 15 - matrix with party palette
    case 15:
      if(mc) { this_delay = 50; target_palette = PartyColors_p; this_index = 64; this_dir = 0; this_rot = 1; this_bright = 255; bg_clr = 100; bg_bri = 10; }
			matrix_pal(); 
			break;

    // 16 - noise8 with palette
    case 16:
      if(mc) { this_delay = 10; target_palette = OceanColors_p; palette_change = 1; }
			noise8_pal(); 
			break;

    // 17 - circular noise with party palette
    case 17:
 			if(mc) { this_delay = 10; target_palette = PartyColors_p; }
			circnoise_pal_2(); 
			break;

    // 18 - two-sin
    case 18:
 			if(mc) { this_delay = 20; all_freq = 10; this_speed = 1; thatspeed = -2; this_hue = 48; thathue = 160; this_dir = 0; this_rot = 1; thatrot = -1; this_cutoff = 128; thatcutoff = 192; }
			two_sin(); 
			break;

    // 19 - three-sin with palette
    case 19:
 			if(mc) { this_delay = 50; mul1 = 6; mul2 = 9; mul3 = 11; }
			three_sin_pal(); 
			break;

    // 20 - rainbow march with wide waves
    case 20:
 			if(mc) { this_delay = 10; this_dir = 1; this_rot = 1; this_diff = 1; }
			rainbow_march(); 
			break;

    // 21 - rainbow march with narrow waves
    case 21:
 			if(mc) { this_delay = 10; this_dir = 1; this_rot = 2; this_diff = 10; }
			rainbow_march(); 
			break;

    // 22 - noise16 with palette
    case 22:
 			if(mc) { this_delay = 20; hxyinc = random16(1, 15); octaves = random16(1, 3); hue_octaves = random16(1, 5); hue_scale = random16(10,  50);  x = random16(); xscale = random16(); hxy =  random16(); hue_time = random16(); hue_speed = random16(1, 3); x_speed = random16(1, 30); }
			noise16_pal(); 
			break;

    // 23 - one-sine with ocean palette
    case 23:
 			if(mc) { this_delay = 20; target_palette = OceanColors_p; all_freq = 6; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 2; this_cutoff = 224; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 4; wave_brightness = 255; }
			one_sin_pal(); 
			break;

    // 24 - circular noise with ocean palette
    case 24:
 			if(mc) { this_delay = 10; target_palette = OceanColors_p; }
			circnoise_pal_4(); 
			break;

    // 25 - confetti with party palette
    case 25:
 			if(mc) { this_delay = 20; target_palette = PartyColors_p; this_inc = 1; this_hue = 192; this_sat = 255; this_fade = 2; this_diff = 32; this_bright = 255; }
			confetti_pal(); 
			break;

    // 26 - two-sin
    case 26:
 			if(mc) { this_delay = 10; this_speed = 2; thatspeed = 3; this_hue = 96; thathue = 224; this_dir = 1; this_rot = 1; thatrot = 2; this_cutoff = 128; thatcutoff = 64; }
			two_sin(); 
			break;

    // 27 - matrix with forest palette
    case 27:
 			if(mc) { this_delay = 30; target_palette = ForestColors_p; this_index = 192; this_dir = 0; this_rot = 0; this_bright = 255; bg_clr = 50; bg_bri = 0; }
			matrix_pal(); 
			break;

    // 28 - one-sin with party palette
    case 28:
 			if(mc) { this_delay = 20; target_palette = RainbowColors_p; all_freq = 20; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 2; this_cutoff = 224; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 4; wave_brightness = 255; }
			one_sin_pal(); 
			break;

    // 29 - confetti with lava palette
    case 29:
 			if(mc) { this_delay = 20; target_palette = LavaColors_p; this_inc = 2; this_hue = 128; this_fade = 8; this_diff = 64; this_bright = 255; }
			confetti_pal(); 
			break;

    // 30 - circular noise with party palette
    case 30:
 			if(mc) { this_delay = 10; target_palette = PartyColors_p; }
			circnoise_pal_3(); 
			break;

    // 31 - juggle mode with ocean palette
    case 31:
 			if(mc) { this_delay = 10; numdots = 4; target_palette = OceanColors_p; this_fade = 32; this_beat = 12; this_bright = 255; this_diff = 20; }
			juggle_pal(); 
			break;

    // 32 - one-sin with palette
    case 32:
 			if(mc) { this_delay = 30; SetupSimilar4Palette(); all_freq = 4; bg_clr = 64; bg_bri = 4; this_bright = 255; start_index = 64; this_inc = 2; this_cutoff = 224; this_phase = 0; this_cutoff = 128; this_rot = 1; this_speed = 8; wave_brightness = 255; }
			one_sin_pal(); 
			break;

    // 33 - three-sin with palette
    case 33:
 			if(mc) { this_delay = 50; mul1 = 3; mul2 = 4; mul3 = 5; }
			three_sin_pal(); 
			break;

    // 34 - rainbow march with slow, long waves
    case 34:
 			if(mc) { this_delay = 255; this_dir = -1; this_rot = 1; this_diff = 1;}
			rainbow_march(); 
			break;

    // 35 - circular noise with party palette
    case 35:
 			if(mc) { this_delay = 10; target_palette = PartyColors_p; }
			circnoise_pal_1(); 
			break;

    // 36 - confetti with forest palette
    case 36:
 			if(mc) { this_delay = 20; target_palette = ForestColors_p; this_inc = 1; this_hue = random8(255); this_fade = 1; this_bright = 255; }
			confetti_pal(); 
			break;

    // 37 - noise16 with palette
    case 37:
 			if(mc) { this_delay = 20; octaves = 1; hue_octaves = 2; hxy = 6000; x = 5000; xscale = 3000; hue_scale = 50; hue_speed = 15; x_speed = 100; }
			noise16_pal(); 
			break;

    // 38 - noise8 with lava palette
    case 38:
 			if(mc) { this_delay = 10; target_palette = LavaColors_p; palette_change = 0; }
			noise8_pal(); 
			break;

    // 39 - loading bar, then return to default mode
    case 39:
      if(mc) { this_delay = 50; this_hue = 100; this_bright = 180;}
      loading_bar_pal();
      break;
  }
}

/*
 * Takes in keyboard input and executes commands.
 *
 * Serial timeout value here is important.
 * We should make sure it's set high enough
 * to type the entire command within the timeout.
 */
void readkeyboard() { 
  while (Serial.available() > 0) {
  
    in_byte = Serial.read();

    // Don't print carriage return
    if (in_byte != 10) {
      Serial.print("# ");
      Serial.print(char(in_byte));
      Serial.print(" ");
    }
    
    switch(in_byte) {

      // Command: a {hue} - set entire strip to {hue} (0-255)
      case 97:
        led_mode = 0;
        this_arg = Serial.parseInt();
        this_arg = constrain(this_arg, 0, 255);
        Serial.println(this_arg);
        fill_solid(leds, NUM_LEDS_PER_STRIP, CHSV(this_arg, 255, 255));
        break;

      // Command: b {brightness} - set entire strip to {brightness} (0-255)
      case 98:
        max_bright = Serial.parseInt();
        max_bright = constrain(max_bright, 0, 255);        
        Serial.println(max_bright);
        LEDS.setBrightness(max_bright);
        break;

      // Command: c - clear strip
      case 99:
        Serial.println(" ");
        led_mode = 0;
        strobe_mode(led_mode, 1);
        break;

      // Command: d {delay} - set the delay amount to {delay} (0-255)
      case 100:
        this_arg = Serial.parseInt();
        this_delay = constrain(this_arg, 0, 255);
        Serial.println(this_delay);
        break;

      // Command: e {0/1} - increment or decrement the mode
      case 101:
        this_arg = Serial.parseInt();
        if (this_arg) {
          demo_run = 0;
          led_mode = (led_mode + 1)%(max_mode + 1);
        } else {
          demo_run = 0; 
          led_mode = (led_mode - 1);
          if (led_mode == 255) led_mode = max_mode; 
        }
        strobe_mode(led_mode, 1);
        break;

      // Command: f {palette_number} - set the current palette
      case 102:
        demo_run = 0;
        palette_change = 0;
        this_arg = Serial.parseInt();
        g_current_palette_number = this_arg % g_gradient_palette_count;
        target_palette = g_gradient_palettes[g_current_palette_number];
        Serial.println(g_current_palette_number);
        break;

      // Command: g - toggle glitter
      case 103:
        glitter = !glitter;
        Serial.println(" ");
        break;

      // Command: h {hue} - set hue variable to {hue} (0-255)
      case 104:
        this_arg = Serial.parseInt();
        this_hue = constrain(this_arg, 0, 255);
        Serial.println(this_hue);
        break;

      // Command: i {hue} - set similar pallete with selected hue {hue} (0-255)
      case 105:
        palette_change = 0;
        this_arg = Serial.parseInt();
        this_hue = constrain(this_arg, 0, 255);
        Serial.println(this_hue);
        SetupMySimilar4Palette();
        break;

      // Command: m {mode} - select mode {mode} (0-255)
      case 109:
	old_mode = led_mode;
        led_mode = Serial.parseInt();
        led_mode = constrain(led_mode, 0, max_mode);
        Serial.println(led_mode);
        strobe_mode(led_mode, 1);
        break;

      // Command: n - toggle direction
      case 110:
        Serial.println(" ");
        this_dir = !this_dir;
        break;

      // Command: p {0/1/2} - set demo mode (fixed/sequential/shuffle)
      case 112:
        demo_run = Serial.parseInt();
        demo_run = constrain(demo_run, 0, 2);
        Serial.println(demo_run);        
        break;      
     
      // Command: s {saturation} - set saturation to {saturation} (0-255)
      case 115:
        this_arg = Serial.parseInt();
        this_sat = constrain(this_arg, 0, 255);
        Serial.println(this_sat);
        break;

      // Command: t {0/1/2/3} - set palette mode (fixed/4similar/random4/random16)
      case 116:
        this_arg = Serial.parseInt();
        palette_change = constrain(this_arg, 0, 3);
        Serial.println(palette_change);
        break;

      // Command: w - write current mode to EEPROM
      case 119:
        EEPROM.write(STARTMODE, led_mode);
        Serial.print("Writing keyboard: ");
        Serial.println(led_mode);
        break;   
    }
  }
}
