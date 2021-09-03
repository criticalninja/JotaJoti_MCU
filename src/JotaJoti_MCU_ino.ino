// Jota/Joti MCU Board
// Rev 1
// Based on Arduino (r) Uno (r)
#include <Arduino.h>
#include "pins.h"

volatile bool debug = false;

void setup() {
  // Setup onboard LED

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  // Setup serial port
  Serial.begin(115200);
  while(!Serial && millis() < 2000) {
    // Wait for a serial connection, or give up after 2 seconds
  }
  if(Serial){
    debug = true;
  }

  digitalWrite(LED_BUILTIN, LOW);

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
