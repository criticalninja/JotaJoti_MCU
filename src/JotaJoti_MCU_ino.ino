// Jota/Joti MCU Board
// Rev 1
// Based on Arduino (r) Uno (r)
#include <Arduino.h>
#include "pins.h"
#include <EEPROM.h>

volatile bool debug = false;

#define eepromVersion 0x00
#define eepromProg 0x0F
#define checksum 0xB5
#define eepromGame 0x10

bool ledState;

void ledInvert() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void ledLow() {
  ledState = LOW;
  digitalWrite(LED_BUILTIN, ledState);
}

void ledHigh() {
  ledState = HIGH;
  digitalWrite(LED_BUILTIN, ledState);
}

void setup() {
  // Setup onboard LED

  pinMode(LED_BUILTIN, OUTPUT);
  ledState = HIGH;
  digitalWrite(LED_BUILTIN, ledState);
  
  // Setup serial port
  Serial.begin(115200);
  while(!Serial && millis() < 2000) {
    // Wait for a serial connection, or give up after 2 seconds
  }
  if(Serial){
    debug = true;
  }

  ledState = LOW;
  digitalWrite(LED_BUILTIN, ledState);

  // Say that we are ready to go

  if(debug){
    Serial.println("Booted!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
