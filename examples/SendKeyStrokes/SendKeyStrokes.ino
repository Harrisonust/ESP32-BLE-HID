/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("STM32Keyboard");
#define RXp2 16
#define TXp2 17

void setup() {
	Serial.begin(115200);
	Serial.println("Starting BLE!!! work!");
	Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
	bleKeyboard.begin();
}

bool empty(const uint8_t* buffer, const uint8_t size){
	for(int i = 0; i < size; i++){
		if(buffer[i] != 0){
			return false;
		}
	}
	return true;
}

void loop() {
  	if(bleKeyboard.isConnected()) {
		uint8_t buffer[6];	
		Serial2.readBytes(buffer, 6);
		if(!empty(buffer, 6)){
			for(int i = 0; i < 6; i++){	
				bleKeyboard.write(buffer[i]);
			}
		}
	}
	delay(1);
}
