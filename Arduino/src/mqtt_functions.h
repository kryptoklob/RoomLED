// Process incoming JSON MQTT message
bool process_json(char* message) {
	Serial.println("Processing message...");
	StaticJsonBuffer<BUFFER_SIZE> json_buffer;
	JsonObject& root = json_buffer.parseObject(message);

	if (!root.success()) {
		Serial.println("parseObject() failed");
		return false;
	}

	if (root.containsKey("state")) {
		if (strcmp(root["state"], "ON") == 0) {
			global_state_on = true;
		} else if(strcmp(root["state"], "OFF") == 0) {
			global_state_on = false;
		}
	}

	if (root.containsKey("color")) {
		global_red = root["color"]["r"];
		global_green = root["color"]["g"];
		global_blue = root["color"]["b"];
	}

	if (root.containsKey("effect")) {
		mode = root["effect"];
		global_mode_string = mode;
	}
}

// Send MQTT State
void send_state() {
	Serial.println("Sending state...");
  StaticJsonBuffer<BUFFER_SIZE> json_buffer;
  JsonObject& root = json_buffer.createObject();

  root["state"] = (global_state_on) ? "ON" : "OFF";

	JsonObject& color = root.createNestedObject("color");
	color["r"] = global_red;
	color["g"] = global_green;
	color["b"] = global_blue;

  root["effect"] = global_mode_string.c_str();

  char buffer[root.measureLength() + 1];
  root.printTo(buffer, sizeof(buffer));

  client.publish(mqtt_state_topic, buffer, true);
	Serial.println("State sent.");
}

// Try to reconnect to the mqtt server
void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(mqtt_clientid, mqtt_user, mqtt_password)) {
      Serial.println("Connected");
      client.subscribe(mqtt_set_topic);
			send_state();
    } else {
      Serial.print("Failed, client state: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

// Callback used when we get an MQTT message
void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");

  char message[length+1];
  strncpy(message, (char*)payload, length);
	message[length] = '\0';

	Serial.println(message);

	if (!process_json(message)) {
		return;
	}

	send_state();
}

