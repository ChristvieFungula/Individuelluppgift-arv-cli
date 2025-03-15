#include <Arduino.h>

#define RED_LED 13
#define GREEN_LED 12
#define BLUE_LED A1

#define RED_BTN 8
#define GREEN_BTN 7
#define BLUE_BTN 6



void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    pinMode(RED_BTN, INPUT_PULLUP);
    pinMode(GREEN_BTN, INPUT_PULLUP);
    pinMode(BLUE_BTN, INPUT_PULLUP);
    

}

void loop() {
    if(digitalRead(RED_BTN) == LOW){
        digitalWrite(RED_LED, HIGH);
    } else {
        digitalWrite(RED_LED, LOW);
    }

    if(digitalRead(GREEN_BTN) == LOW){
        digitalWrite(GREEN_LED, HIGH);
    } else {
        digitalWrite(GREEN_LED, LOW);
    }

    if(digitalRead(BLUE_BTN) == LOW){
        digitalWrite(BLUE_LED, HIGH);
    } else {
        digitalWrite(BLUE_LED, LOW);
    }
}
