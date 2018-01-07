// ---------- COMPILE VARS ---------- //

// Fixes flickering
// #define FASTLED_ALLOW_INTERRUPTS 0

// Serial Defines
#define SERIAL_BAUDRATE 57600
#define SERIAL_TIMEOUT 750

// MQTT Defines
//#define MQTT_MAX_PACKET_SIZE 512

// Led Defines
#define LED_PIN_ONE 2
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
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
const char* mqtt_set_topic = "homeassistant/light/led/set";
const char* mqtt_state_topic = "homeassistant/light/led";
const char* mqtt_clientid = "arduino";
const int BUFFER_SIZE = JSON_OBJECT_SIZE(2) + 50;

// LED Meta Variables
struct CRGB leds[NUM_LEDS_PER_STRIP];
uint8_t default_mode              = 34;

// LED Overall Variables
uint8_t max_bright  = 255;
uint8_t max_mode    = 100;

// LED Routine/Shared Variables
uint8_t global_diff       = 0;
uint8_t global_dir				= 1;
uint8_t global_index      = 1;
uint8_t global_rot				= 1;
uint8_t global_delay			= 10;
uint8_t global_red				= 0;
uint8_t global_green			= 255;
uint8_t global_blue				= 255;
String mode = "solid";
bool global_state_on			= false;
