#include "MemoryFree.h"

// Process incoming JSON MQTT message
bool process_json(char* message) {
	Serial.println(F("Processing message..."));
	StaticJsonBuffer<BUFFER_SIZE> json_buffer;
	JsonObject& root = json_buffer.parseObject(message);

	Serial.println(freeMemory());

	if (!root.success()) {
		Serial.println(F("parseObject() failed"));
		return false;
	}

	if (root.containsKey("state")) {
		if (strcmp(root["state"], "ON") == 0) {
			global_state_on = true;
			global_red = 0;
			global_green = 255;
			global_blue = 255;
		} else if(strcmp(root["state"], "OFF") == 0) {
			global_state_on = false;
			global_red = 0;
			global_green = 0;
			global_blue = 0;
		}
	}

	if (root.containsKey("color")) {
		global_red = root["color"]["r"];
		global_green = root["color"]["g"];
		global_blue = root["color"]["b"];
	}

	if (root.containsKey("effect")) {
		if (root["effect"] == "solid") {mode = "solid";} 
		else if (root["effect"] == "rainbow") {mode = "rainbow";}
	}

	call_mode(mode, 1);

	return true;
}

const char* on_cmd = "ON";
const char* off_cmd = "OFF";

// Send MQTT State
void send_state() {
  Serial.println(F("Sending state..."));
  StaticJsonBuffer<BUFFER_SIZE> json_buffer;
  JsonObject& root = json_buffer.createObject();

  root["state"] = "off";//(global_state_on) ? on_cmd : off_cmd;

	//JsonObject& color = root.createNestedObject("color");
	//color["r"] = global_red;
	//color["g"] = global_green;
	//color["b"] = global_blue;

  //root["effect"] = mode;

  char buffer[root.measureLength() + 1];
  root.printTo(buffer, sizeof(buffer));

  client.publish(mqtt_state_topic, buffer, true);
  Serial.println(F("State sent."));
  delay(1000);
}

// Try to reconnect to the mqtt server
void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.println(F("Attempting MQTT connection..."));
    if (client.connect(mqtt_clientid, mqtt_user, mqtt_password)) {
      Serial.println(F("Connected"));
      if (!client.subscribe(mqtt_set_topic)){
	Serial.println(F("Unable to subscribe to topic."));
      }
	//send_state();
    } else {
      Serial.print(F("Failed, client state: "));
      Serial.println(client.state());
      delay(5000);
    }
  }
}

// Callback used when we get an MQTT message
void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print(F("Message arrived ["));
	Serial.print(topic);
	Serial.print(F("] "));

  char message[length+1];
  for(unsigned int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }

  message[length] = '\0';

	Serial.println(message);

	if (!process_json(message)) {
		return;
	}
  //send_state();
}

