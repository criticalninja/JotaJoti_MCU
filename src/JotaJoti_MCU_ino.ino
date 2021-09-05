// Jota/Joti MCU Board
// Rev 1
// Based on Arduino (r) Uno (r)
#include <Arduino.h>
#include "pins.h"
#include <EEPROM.h>

#define S_DEBUG

#ifdef S_DEBUG
#define s_print(x) Serial.print(x)
#define s_println(x) Serial.println(x)
#else
#define s_print(x)
#define s_println(x, y)
#endif

volatile bool debug = false;

#define eepromVersion 0x00
#define eepromProg 0x0F
#define checksum 0xB5
#define eepromGame 0x10

bool ledState;

uint32_t time;
uint32_t refresh;

void ledInvert() {
  if(ledState == true){
    ledState = false;
  } else {
    ledState = true;
  }
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

    void m_update() {
      for(int i = 0; i < 4; i++){
        // Gets value but reads as inverse to show pressed/not pressed, rather than high/low
        bool temp1 = (!(digitalRead(m_buttonPins[i])));
        // Delay for debouncing
        delay(10);
        bool temp2 = (!(digitalRead(m_buttonPins[i])));
        if (temp1 == temp2) {
          if(temp2 != m_buttonState[i]){
          m_buttonState[i] = temp2;
          }
        }
      }
    }

  public:

    buttons(int pin1, int pin2, int pin3, int pin4) {
      m_buttonPins[0] = pin1;
      m_buttonPins[1] = pin2;
      m_buttonPins[2] = pin3;
      m_buttonPins[3] = pin4;
      for(int i = 0; i < 4; i++){
        pinMode(m_buttonPins[i], INPUT);
      }
    }

    bool buttonState(int pin){
      m_update();
      return m_buttonState[pin];
    }

    int lowestButton() {
      m_update();
      for (int i = 0; i < 4; i++) {
        if (m_buttonState[i] == true){
          return (i+1);
          } 
        }
        return 0;
      }
};

class leds {
  private:
    int m_ledPins[4];
    bool m_ledState[4];
    uint8_t m_ledPWM[4];

    void m_update() {
      for (int i = 0; i < 4; i ++) {
        digitalWrite(m_ledPins[i], m_ledState[i]);
      }
    }

    void m_pwmUpdate() {
      for (int i = 0; i < 4; i ++) {
        analogWrite(m_ledPins[i], m_ledPWM[i]);
      }
    }

  public:

    leds(int l1, int l2, int l3, int l4){
      m_ledPins[0] = l1;
      m_ledPins[1] = l2;
      m_ledPins[2] = l3;
      m_ledPins[3] = l4;
      for (int i = 0; i < 4; i++){
        pinMode(m_ledPins[i], OUTPUT);
        digitalWrite(m_ledPins[i], LOW);
      }
    }

    void digital (int pin, bool val) {
      m_ledState[pin] = val;
    }

    void toggle (int pin) {
      m_ledState[pin] = !m_ledState[pin];
      m_update();
    }

    void analog (int pin, uint8_t val) {
      m_ledPWM[pin] = val;
    }

    void displayDigital() {
      m_update();
    }

    void displayPWM() {
      m_pwmUpdate();
    }

};

buttons Buttons(button1, button2, button3, button4);
leds Leds(led1, led2, led3, led4);

void setup() {
  // Setup onboard LED

  pinMode(LED_BUILTIN, OUTPUT);
  ledHigh();
  
  // Setup serial port
  Serial.begin(9600);
  while(!Serial.available() && millis() < 2000) {
    // Wait for a serial connection, or give up after 2 seconds
  }

  ledLow();

  // Say that we are ready to go
  Serial.println("Booted!");

}

void loop() {
  // put your main code here, to run repeatedly:
  if((time+1000) < millis()){
    time = millis();
    ledInvert();
  }

  if (refresh+100 < millis()) {
    refresh = millis();
    switch(Buttons.lowestButton()) {
      case 1:
        s_println("it's a one!");
        Leds.toggle(0);
        break;
      case 2:
        s_println("it's a two!");
        Leds.toggle(1);
        break;
      case 3:
        s_println("it's a three!");
        Leds.toggle(2);
        break;
      case 4:
        s_println("it's a four!");
        Leds.toggle(3);
        break;
      default:
        break;
    }
  }
  
  


}
