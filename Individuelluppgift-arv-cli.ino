#include <Arduino.h>

#define RED_LED 13
#define GREEN_LED 12
#define BLUE_LED A1

#define RED_BTN 8
#define GREEN_BTN 7
#define BLUE_BTN 6

unsigned long previousMillis = 0;
const unsigned long interval = 2000;
bool ledState = LOW;

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    pinMode(RED_BTN, INPUT_PULLUP);
    pinMode(GREEN_BTN, INPUT_PULLUP);
    pinMode(BLUE_BTN, INPUT_PULLUP);
    

}

void loop() {
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= interval){
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(RED_LED, ledState);
        digitalWrite(GREEN_LED, ledState);
        digitalWrite(BLUE_LED, ledState);
    }
    }
