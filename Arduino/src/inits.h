void init_serial() {
	delay(2500);
	Serial.begin(SERIAL_BAUDRATE);
	Serial.setTimeout(SERIAL_TIMEOUT);
	delay(1000);
}

void init_leds() {
	LEDS.setBrightness(max_bright);
	LEDS.addLeds<LED_TYPE, LED_PIN_ONE, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP);
	set_max_power_in_volts_and_milliamps(5, 1000);
}

void init_mqtt() {
	Ethernet.begin(mac, ip);
	client.setServer(mqtt_server, mqtt_port);
	client.setCallback(callback);
}
