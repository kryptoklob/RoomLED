#ifndef _HEADERFILE_H
#define _HEADERFILE_H
#include "headerfile.h"
#endif


// Initialize changeable global variables.
uint8_t max_bright = 255;                                     // Overall brightness definition. It can be changed on the fly.

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

int ledMode = 0;                                             // Starting mode is typically 0. Use 99 if no controls available. ###### CHANGE ME #########
int maxMode;                                                  // Maximum number of modes is set later.
byte inbyte;                                                  // Serial input byte
int thisarg;                                                  // Serial input argument

// Generic variables
uint8_t thisdelay = 0;                                        // Standard delay
uint8_t thishue = 0;                                          // Standard hue
uint8_t thissat = 255;                                        // Standard saturation
int thisbright = 255;                                           // Standard brightness
uint8_t thisfade = 255;                                         // Standard fade rate
bool thisdir = 0;                                             // Standard direction

// Matrix variables

bool huerot = 0;
uint8_t bgclr = 0;
uint8_t bgbri = 0;

// Two_sin variables-------------------------------------------------------------------------
uint8_t wavebright = 255;                                     // You can change the brightness of the waves/bars rolling across the screen. Best to make them not as bright as the sparkles.
//uint8_t thishue = 0;                                          // You can change the starting hue value for the first wave.
uint8_t thathue = 140;                                        // You can change the starting hue for other wave.
uint8_t thisrot = 0;                                          // You can change how quickly the hue rotates for this wave. Currently 0.
uint8_t thatrot = 0;                                          // You can change how quickly the hue rotates for the other wave. Currently 0.
uint8_t allsat = 255;                                         // I like 'em fully saturated with colour.
//bool thisdir = 0;                                             // A direction variable that will work with inputs.
int8_t thisspeed = 4;                                         // You can change the speed, and can use negative values.
int8_t thatspeed = 4;                                         // You can change the speed, and use negative values.
uint8_t allfreq = 32;                                         // You can change the frequency, thus overall width of bars.
int thisphase = 0;                                            // Phase change value gets calculated.
int thatphase = 0;                                            // Phase change value gets calculated.
uint8_t thiscutoff = 100;                                     // You can change the cutoff value to display this wave. Lower value = longer wave.
uint8_t thatcutoff = 100;                                     // You can change the cutoff value to display that wave. Lower value = longer wave.


// Twinkle variables -----------------------------------------------------------------------
int twinkrate = 50;


// One_sin variables -----------------------------------------------------------------------

// bool thisdir = 0;
// uint8_t bgclr = 0;
// uint8_t bgbri = 0;


// pop_fade variables ----------------------------------------------------------------------
int ranamount = 200;                                           // The higher the number, lowers the chance for a pixel to light up.
// uint8_t thisdelay = 50;                                       // Standard delay value.
bool boolcolours = 1;                                         // True = random, False = array of colours (up to 10)
uint8_t numcolours = 2;                                       // Number of colours in the array to display.
unsigned long colours[10] = {0xff0000, 0x00ff00, 0x0000ff, 0xffffff};  // Just assign the first 3 of these selectable colours.
uint8_t maxbar = 4;                                           // Maximum # of pixels to turn on in a row
uint8_t fadeval = 255;                                        // Fade rate


// three_sin variables ---------------------------------------------------------------------

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

// rainbow_march variables -----------------------------------------------------------------

uint8_t deltahue = 1;                                         // Hue change between pixels.


// noise16 variables -----------------------------------------------------------------------

//uint8_t thisdelay = 20;                                       // A delay value for the sequence(s)
// bool thisdir = 0;                                          // We can reverse the direction.
uint32_t  x,hue_time;                                         // x & hue_time values
uint8_t octaves=2;       //2                                  // how many octaves to use for the brightness
uint8_t hue_octaves=3;   //3                                  // how many octaves to use for the hue
int xscale=57771;        //57771                              // the 'distance' between points on the x axis
uint32_t hxy = 43213;    //43213                              // not sure about this
int hue_scale=20;        //1                                  // the 'distance' between points for the hue noise
int hue_speed = 1;       //31                                 // how fast we move through hue noise
uint8_t x_speed = 0;     //331                                // adjust this value to move along the x axis between frames
int8_t hxyinc = 3;       //3

// uint8_t wavebright= 128;                                      // Usesd by qsub to set a fixed value to LED's depending on their current value

uint8_t colour;
