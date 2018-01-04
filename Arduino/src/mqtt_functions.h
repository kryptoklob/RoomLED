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

// Callback used when we get an MQTT message
void callback(char* topic, byte* payload, unsigned int length) {
  char tmp[length+1];
  strncpy(tmp, (char*)payload, length);
  tmp[length] = '\0';
  String data(tmp);

  Serial.print("Received Data from Topic: ");
  Serial.println(data);

  if (data.length() > 0) {
    String command = get_value(data, ':', 0);
    Serial.print("Command: ");
    Serial.println(command);
    String value = get_value(data, ':', 1);
    Serial.print("Value: ");
    Serial.println(value);

    if (command.length() > 0) {
      if (command.equals("mode")) {
        call_mode(value.toInt(), 1);
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

