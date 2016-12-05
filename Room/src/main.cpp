#include <FastLED.h>

#define frontNo 115
#define rightNo 89
#define backNo  115
#define leftNo  89

#define totalNo (frontNo + rightNo + backNo + leftNo)

CRGB frontLeds[frontNo];
CRGB backLeds[backNo];
CRGB leftLeds[leftNo];
CRGB rightLeds[rightNo];

CRGB allLeds[totalNo];

void setup() {
	FastLED.addLeds<NEOPIXEL, 4>(rightLeds, rightNo);
	FastLED.addLeds<NEOPIXEL, 5>(frontLeds, frontNo);
	FastLED.addLeds<NEOPIXEL, 2>(backLeds, backNo);
	FastLED.addLeds<NEOPIXEL, 3>(leftLeds, leftNo);
	Serial.begin(115200);
	leftLeds[25].setRGB(0,0,0);
	FastLED.show();
}

void setColor(int index, int hue, int sat, int brt) {
	int position = index % totalNo;

	if ((position >= 0) && (position < frontNo)) {
		frontLeds[frontNo - position].setHSV(hue, sat, brt);
	} else if ((position >= frontNo) && (position < (frontNo + rightNo))) {
		rightLeds[position - frontNo].setHSV(hue, sat, brt);;
	} else if ((position >= (frontNo + rightNo)) && (position < (frontNo + rightNo + backNo))) {
		backLeds[(frontNo + rightNo + backNo) - position].setHSV(hue, sat, brt);
	} else if ((position >= (frontNo + rightNo + backNo)) && (position < totalNo)) {
		leftLeds[position - (frontNo + rightNo + backNo)].setHSV(hue, sat, brt);
	}
}

void makeRainbow(){
	for( int i = 0; i < 255; i++){
		fill_rainbow(frontLeds, frontNo, i, 3);
		fill_rainbow(rightLeds, rightNo, 255-(i+frontNo), 3);
		fill_rainbow(backLeds, backNo, i+frontNo+rightNo, 3);
		fill_rainbow(leftLeds, leftNo, 255-(i+frontNo+rightNo+backNo), 3);
		FastLED.show();
	}
}

void seizure(){
	for(int i = 0; i < leftNo-11; i=i+11){
		fill_solid(leftLeds+i, 11, CHSV((int)random8(), (int)random8()/2, 255));
		fill_solid(rightLeds+i, 11, CHSV((int)random8(), (int)random8()/2, 255));
	}
	for(int i = 0; i < frontNo; i=i+23){
		fill_solid(frontLeds+i, 23, CHSV((int)random8(), (int)random8()/2, 255));
		fill_solid(backLeds+i, 23, CHSV((int)random8(), (int)random8()/2, 255));
	}
	FastLED.show();
	delay(100);
}

void allFade(){
	for(int color = 0; color < 255; color++){
		for(int i = 0; i < totalNo; i++){
			setColor(i, color, 255, 255);
		}
		FastLED.show();
	}
}

void trail(){
	for(int i = 0; i < totalNo; i++){
		// the head
		for(int j = 0; j < 5; j++){
			setColor(i+j+15+75, 0, 200, 255);
		}
		// the tail
		for(int j = 0; j < 15; j++){
			setColor(i+j+75, 100, 200, 255);
		}
		// even longer tail
		for(int j = 0; j < 75; j++){
			setColor(i+j, 200, 200, 255);
		}
		FastLED.show();
		// black out the last part of the tail
		setColor(i, 0, 0, 0);
	}
}

void setByReceive(){
	char rxdata[3];
	if (Serial.available() > 0){
		Serial.readBytes(rxdata, 3);
		fill_solid(leftLeds, leftNo, CRGB((int)rxdata[0], (int)rxdata[1], (int)rxdata[2]));
		fill_solid(rightLeds, rightNo, CRGB((int)rxdata[0], (int)rxdata[1], (int)rxdata[2]));
		fill_solid(backLeds, backNo, CRGB((int)rxdata[0], (int)rxdata[1], (int)rxdata[2]));
		fill_solid(frontLeds, frontNo, CRGB((int)rxdata[0], (int)rxdata[1], (int)rxdata[2]));
		FastLED.show();
	}
}

void loop() {
	setByReceive();
}
