#include <Arduino.h>

#define RED_LED 13
#define GREEN_LED 12
#define BLUE_LED A1

#define RED_BTN 8
#define GREEN_BTN 7
#define BLUE_BTN 6

bool ledState = LOW;

unsigned long previousMillis = 0;
const unsigned long interval = 2000;

// Debounce
int debounceDelay = 50;
int currentStateRedBtn = HIGH;
int trueStateRedBtn = HIGH;
int lastStateRedBtn = HIGH;

int currentStateGreenBtn = HIGH;
int trueStateGreenBtn = HIGH;
int lastStateGreenBtn = HIGH;

int currentStateBlueBtn = HIGH;
int trueStateBlueBtn = HIGH;
int lastStateBlueBtn = HIGH;
unsigned long lastDebounceTime = 0;






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

    int currentStateRedBtn = digitalRead(RED_BTN);
    int currentStateGreenBtn = digitalRead(GREEN_BTN);
    int currentStateBlueBtn = digitalRead(BLUE_BTN);

    if(currentStateRedBtn != lastStateRedBtn){
        lastDebounceTime = millis();
    }

    if(currentStateGreenBtn != lastStateGreenBtn){
        lastDebounceTime = millis();
    }

    if(currentStateBlueBtn != lastStateBlueBtn){
        lastDebounceTime = millis();
    }

    if((millis() - lastDebounceTime) > debounceDelay){
        if(currentStateRedBtn != trueStateRedBtn){
            trueStateRedBtn = currentStateRedBtn;
            if(currentStateRedBtn == LOW){
                digitalWrite(RED_LED, !digitalRead(RED_LED));
            }
        }
    }
    lastStateRedBtn = currentStateRedBtn;

    }
