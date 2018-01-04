// ---------- COMPILE VARS ---------- //

// Fixes flickering
// #define FASTLED_ALLOW_INTERRUPTS 0

// Disables Version "errors" on compile
#define FASTLED_INTERNAL

// Libraries
#include "FastLED.h"
#include "EEPROM.h"

// Serial vars
#define SERIAL_BAUDRATE 57600
#define SERIAL_TIMEOUT 750

// Arduino pin setup

// Single pin (2) defined for development testing
#define LED_PIN_ONE 2

// LED Meta Defines
#define COLOR_ORDER GRB

// WS2812B used for development testing
#define LED_TYPE WS2812B

// 150 Length LED strip used for development testing
#define NUM_LEDS_PER_STRIP 150
#define STARTMODE 0
#define STRANDLEN 150

// ---------- RUNTIME VARS ---------- //

// Ethernet variables
byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0x00
};

IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetClient ethClient;
PubSubClient client(ethClient);

// MQTT variables
const char* mqtt_server = "192.168.1.187";
const int mqtt_port = 1883;
const char* mqtt_user = "homeassistant";
const char* mqtt_password = "password";
const char* mqtt_topic = "led";
const char* mqtt_clientid = "arduino";

// LED Meta Variables
struct CRGB leds[NUM_LEDS_PER_STRIP];
uint8_t default_mode              = 34;

// LED Overall Variables
uint8_t max_bright  = 255;
uint8_t max_mode    = 100;
uint8_t led_mode;

// LED Routine/Shared Variables
uint8_t global_diff       = 0;
uint8_t global_index      = 1;
uint8_t global_delay			= 10;
uint8_t global_red				= 0;
uint8_t global_green			= 255;
uint8_t global_blue				= 255;
