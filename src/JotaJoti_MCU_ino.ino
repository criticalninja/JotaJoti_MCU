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

struct leds
  {
    volatile bool l1;
    volatile bool l2;
    volatile bool l3;
    volatile bool l4;
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

  // Setup our output pins

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // setup our input pins

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  // Say that we are ready to go if we can

  if(debug){
    Serial.println("Booted!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

void error() {

}

void simon() {
  
  #define rounds 5
  // The structure for the game
  leds game[rounds];

  // Get the game data from EEPROM
  for (int i = 0; i < rounds; i ++){
    game[i].l1 = eepromGet(0, i);
    game[i].l2 = eepromGet(1, i);
    game[i].l3 = eepromGet(2, i);
    game[i].l4 = eepromGet(3, i);
  }

  // Game tracking variables
  bool flag = false;
  uint32_t time = 0;
  bool buttons[4];

  // Until a button is pressed, we toggle the LED every second
  while(flag == false) {
    if(time+1000 < millis()){
      invertLed();
      time = millis();
    }

    buttons[0] = digitalRead(button1);
    buttons[1] = digitalRead(button2);
    buttons[2] = digitalRead(button3);
    buttons[3] = digitalRead(button4);

    for(int i = 0; i < 3; i++){
      if(buttons[i] == HIGH){
        flag = true;
      }
    }

  }

}

bool eepromGet(int bit, int offset){
  // Read the eeprom
  if(EEPROM.read(eepromProg) == checksum){
    uint8_t temp = EEPROM.read(eepromGame+offset);
    temp = temp >> bit;
    return temp;
  }
  return false;
}

void eepromGameUpdate(bool bit1, bool bit2, bool bit3, bool bit4, int round){
  uint8_t temp;
  bool bits[4];
  bits[0] = bit1;
  bits[1] = bit2;
  bits[2] = bit3;
  bits[3] = bit4;

  for (int i = 0; i < 4; i ++) {
    if (bits[i] == true) {
      temp = temp | (1 << i);
    } else if (bits [i] == false) {
      temp = !temp;
      temp = temp | (1 << i);
      temp = !temp;
    }
  }

  EEPROM.update((eepromGame+round), temp);

}

void invertLed() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}