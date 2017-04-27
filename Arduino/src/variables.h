#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdint.h>

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

// Global LED vars
uint8_t max_bright = 255;                                     // Overall brightness definition. It can be changed on the fly.
uint8_t thisdelay = 0;                                        // Standard delay
uint8_t thishue = 0;                                          // Standard hue
uint8_t thissat = 255;                                        // Standard saturation
uint8_t thisbright = 255;                                     // Standard brightness
uint8_t thisfade = 255;                                       // Standard fade rate
uint8_t ledMode = 0;                                          // Starting mode is typically 0. Use 99 if no controls available. ###### CHANGE ME #########
uint8_t maxMode;                                              // Maximum number of modes is set later.
uint8_t colour;
uint8_t deltahue = 1;                                         // Hue change between pixels.

// Serial vars
uint8_t inbyte;                                               // Serial input byte
uint8_t thisarg;                                              // Serial input argument

// Fade rate definitions
uint8_t VERY_SLOW_FADE_RATE = 8;
uint8_t SLOW_FADE_RATE      = 16;
uint8_t MEDIUM_FADE_RATE    = 32;
uint8_t FAST_FADE_RATE      = 64;
uint8_t INSTANT_FADE_RATE   = 255;

// Matrix variables

bool huerot = 0;
uint8_t bgclr = 0;
uint8_t bgbri = 0;



// pop_fade variables ----------------------------------------------------------------------
int ranamount = 200;                                           // The higher the number, lowers the chance for a pixel to light up.
// uint8_t thisdelay = 50;                                       // Standard delay value.
bool boolcolours = 1;                                         // True = random, False = array of colours (up to 10)
uint8_t numcolours = 2;                                       // Number of colours in the array to display.
unsigned long colours[4] = {0xff0000, 0x00ff00, 0x0000ff, 0xffffff};  // Just assign the first 3 of these selectable colours.
uint8_t maxbar = 4;                                           // Maximum # of pixels to turn on in a row
uint8_t fadeval = 255;                                        // Fade rate


uint32_t  x,hue_time;                                         // x & hue_time values
uint8_t octaves= 2;       //2                                  // how many octaves to use for the brightness
uint8_t hue_octaves=3;   //3                                  // how many octaves to use for the hue
int xscale=57771;        //57771                              // the 'distance' between points on the x axis
uint32_t hxy = 43213;    //43213                              // not sure about this
int hue_scale=20;        //1                                  // the 'distance' between points for the hue noise
int hue_speed = 1;       //31                                 // how fast we move through hue noise
uint8_t x_speed = 0;     //331                                // adjust this value to move along the x axis between frames
int8_t hxyinc = 3;       //3

#endif
