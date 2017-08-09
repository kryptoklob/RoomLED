// ---------- COMPILE VARS ---------- //

// Libraries
#include "FastLED.h"
#include "EEPROM.h"

// Unsigned subtraction magic
#define qsubd(x, b) ((x>b)?wavebright:0)
#define qsuba(x, b) ((x>b)?x-b:0)

// Serial vars
#define SERIAL_BAUDRATE 57600
#define SERIAL_TIMEOUT 5

// Arduino pin setup
#define LED_PIN_ONE 2
#define LED_PIN_TWO 3

// LED Meta Defines
#define COLOR_ORDER BGR
#define LED_TYPE WS2812B
#define NUM_LEDS 150
#define STARTMODE 0
#define STRANDLEN 150

// ---------- RUNTIME VARS ---------- //

// Serial Variables
byte in_byte;
int this_arg;

// LED Meta Variables
struct CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;         // Current palette we're using
CRGBPalette16 targetPalette;          // Next palette to transition to
TBlendType currentBlending;           // Linear vs No-Blending
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];   // from gradient_palettes.h
extern const uint8_t gGradientPaletteCount;                       // # of fixed palettes
uint8_t gCurrentPaletteNumber = 0;                                // Current palette number
uint8_t currentPatternIndex   = 0;                                // Index of current pattern


// LED Overall Variables
uint8_t max_bright = 255;
uint8_t ledMode;
uint8_t maxMode = 100;
uint8_t demorun = 0;

// LED Routine/Shared Variables
uint8_t allfreq     = 32;             // Frequency (width of bars)
uint8_t bgclr       = 0;              // Background color
uint8_t bgbri       = 0;              // Background brightness
bool    glitter     = 0;              // Glitter flag
uint8_t palchg;                       // ???                                  #fixme
uint8_t startindex  = 0;              // ???                                  #fixme
uint8_t thisbeat;                     // Standard beat                        #fixme
uint8_t thisbright  = 0;              // Starndard brightness
uint8_t thiscutoff  = 192;            // Cuttoff value; lower = longer wave
int     thisdelay   = 0;              // Standard delay
uint8_t thisdiff    = 1;              // Standard palette index jump
uint8_t thisdir      = 0;              // Standard direction
uint8_t thisfade    = 224;            // Standard fate rate
uint8_t thishue     = 0;              // Standard hue
uint8_t thisindex   = 0;              // Standard pallete index
uint8_t thisinc     = 1;              // Standard incrementer                 #fixme
int     thisphase   = 0;              // Standard phase change
uint8_t thisrot     = 1;              // Standard hue rotation rate
uint8_t thissat     = 255;            // Standard saturdation
uint8_t thisspeed   = 4;              // Standard speed change
uint8_t wavebright  = 255;            // Brightness of the waves/bars
uint8_t xd[NUM_LEDS];                 // X-array for 2d coordinates of leds
uint8_t yd[NUM_LEDS];                 // Y-array for 2d coordinates of leds
long    sum         = 0;              // ???                                  #fixme
