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

class buttons {
  private:
    int m_buttonPins[4];
    bool m_buttonState[4];

  public:
    bool flag;

    buttons(int pin1, int pin2, int pin3, int pin4) {
      m_buttonPins[0] = pin1;
      m_buttonPins[1] = pin2;
      m_buttonPins[2] = pin3;
      m_buttonPins[3] = pin4;
      for(int i = 0; i < 4; i++){
        pinMode(m_buttonPins[i], INPUT);
      }
      flag = false;
    }

    bool update() {
      bool temp[4];
      bool change;
      for(int i = 0; i < 4; i++){
        temp[i] = digitalRead(m_buttonPins[i]);
        if(temp[i] != m_buttonState[i]){
          flag = true;
          change = true;
          m_buttonState[i] = temp[i];
        }
      }
    }

};

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
