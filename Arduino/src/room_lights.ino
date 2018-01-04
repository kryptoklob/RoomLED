#include "includes.h"

void setup() {
	// Serial, led, and mqtt setup
	init_serial();
	init_leds();
	init_mqtt();

  // Start default mode
  strobe_mode(led_mode, 1);
}

void loop() {
  if (!client.connected()) {
    Serial.println("Reconnecting MQTT...");
    reconnect_mqtt();
  }

  // Dynamic delay adjustment
  EVERY_N_MILLIS_I(this_timer, this_delay) {
    this_timer.setPeriod(this_delay);
    strobe_mode(led_mode, 0);
  }

  FastLED.show();
}

// Callback used when an MQTT message is received
void callback(char* topic, byte* payload, unsigned int length) {
  char tmp[length+1];
  strncpy(tmp, (char*)payload, length);
  tmp[length] = '\0';
  String data(tmp);

  Serial.print("Received Data from Topic: ");
  Serial.println(data);

  if (data.length() > 0) {
    String command = getValue(data, ':', 0);
    Serial.print("Command: ");
    Serial.println(command);
    String value = getValue(data, ':', 1);
    Serial.print("Value: ");
    Serial.println(value);

    if (command.length() > 0) {
      if (command.equals("mode")) {
        strobe_mode(value, 1);
      } else if (command.equals("red")) {
				global_red = value.toInt();
			} else if (command.equals("green")) {
				global_green = value.toInt();
			} else if (command.equals("blue")) {
				global_blue = value.toInt();
			}
    }
  }
}

// Sets the mode/routine for the LEDs.
void strobe_mode(uint8_t newMode, bool mc){
  // If this_ is a *new* mode, clear out LED array.
  if(mc) {
    fill_solid(leds, NUM_LEDS_PER_STRIP, CRGB( 0, 0, 0));
    Serial.print("Mode: ");
    Serial.println(led_mode);
  }

	call_mode(led_mode);
}

// Get the value from the MQTT packet
String get_value(String data, char separator, int index){
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// Try to reconnect to the mqtt server
void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(mqtt_clientid, mqtt_user, mqtt_password)) {
      Serial.println("Connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed, client state: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}
