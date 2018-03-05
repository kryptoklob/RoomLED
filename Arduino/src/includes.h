// Order of the includes is important, since some vars use libraries

// Libraries
#include <Ethernet.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "FastLED.h"

// Variables
#include "variables.h"

// Mode Functions
#include "rainbow_march.h"
#include "soundfhtlog.h"

// Utility Functions
#include "call_mode.h"
#include "mqtt_functions.h"
#include "inits.h"
