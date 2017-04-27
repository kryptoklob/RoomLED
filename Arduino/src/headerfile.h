#ifndef _HEADERFILE_H
#define _HEADERFILE_H

// Includes
#include <stdint.h>
#include "Arduino.h"
#include "FastLED.h"

// Global function prototypes
void call_mode(int newMode, int mc);
void readkeyboard();
void fill_solid_HSV(uint8_t ahue, uint8_t asat, uint8_t abright);

// LED Metadata
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define LEFTNO 89
#define RIGHTNO 89
#define FRONTNO 115
#define BACKNO 115
#define NUM_LEDS LEFTNO + FRONTNO

// Pin assignments
#define LED_DT_FRONT 5
#define LED_DT_RIGHT 4
#define LED_DT_LEFT 3
#define LED_DT_BACK 2
#define POT_PIN 0
#define MIC_PIN 5

// Serial arguments
#define SERIAL_BAUDRATE 57600
#define SERIAL_TIMEOUT 750

// Math functions
#define qsubd(x, b)  ((x>b)?wavebright:0)     // A digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)            // Unsigned subtraction macro. if result <0, then => 0.

// Global variable declarations
#include "variables.h"

// LED display modes
#include "matrix.h"
#include "noise16.h"
#include "one_sin.h"
#include "rainbow_march.h"
#include "three_sin.h"
#include "twinkle.h"
#include "two_sin.h"
#include "confetti.h"
#include "sinelon.h"
#include "juggle.h"
#include "lightnings.h"
#include "soundmems.h"
#include "soundamp.h"
#include "soundfhtlog.h"

#endif