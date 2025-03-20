#include <Arduino.h>

#define RED_LED 13
#define GREEN_LED 12
#define BLUE_LED A1

const int RED_RGB = 11;
const int GREEN_RGB = 10;
const int BLUE_RGB = 9;

#define RED_BTN 8
#define GREEN_BTN 7
#define BLUE_BTN 6

#define POT_PIN A0
#define POT_RED A2
#define POT_GREEN A3
#define POT_BLUE A4


bool redLedState = LOW;
bool greenLedState = LOW;
bool blueLedState = LOW;

unsigned long previousMillis = 0;
const unsigned long interval = 2000;

// Debounce
const int debounceDelay = 50;
unsigned long lastDebounceTimeRed = 0;
unsigned long lastDebounceTimeGreen = 0;
unsigned long lastDebounceTimeBlue = 0;

int lastStateRedBtn = HIGH;
int lastStateGreenBtn = HIGH;
int lastStateBlueBtn = HIGH;

bool disableRedBlink = false;
bool disableGreenBlink = false;
bool disableBlueBlink = false;

bool disableRedButton = false;
bool disableGreenButton = false;
bool disableBlueButton = false;
bool disablePotentiometer = false;

void setup() {

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    pinMode(RED_RGB, OUTPUT);
    pinMode(GREEN_RGB, OUTPUT);
    pinMode(BLUE_RGB, OUTPUT);

    pinMode(RED_BTN, INPUT_PULLUP);
    pinMode(GREEN_BTN, INPUT_PULLUP);
    pinMode(BLUE_BTN, INPUT_PULLUP);

    digitalWrite(RED_LED, redLedState);
    digitalWrite(GREEN_LED, greenLedState);
    digitalWrite(BLUE_LED, blueLedState);
    Serial.begin(9600);
}

void loop() {
    handleSerialCommands();
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (!disableRedBlink && !disableRedButton) {
            redLedState = !redLedState;
            digitalWrite(RED_LED, redLedState);
        }

        if (!disableGreenBlink && !disableGreenButton) {
            greenLedState = !greenLedState;
            digitalWrite(GREEN_LED, greenLedState);
        }

        if (!disableBlueBlink && !disableBlueButton) {
            blueLedState = !blueLedState;
            digitalWrite(BLUE_LED, blueLedState);
        }
    }

    if(!disableBlueBlink && !disablePotentiometer){
        setBrightness(POT_PIN, BLUE_LED);
    }

    setBrightness(POT_RED, RED_RGB);
    setBrightness(POT_GREEN, GREEN_RGB);
    setBrightness(POT_BLUE, BLUE_RGB);


    handleButton(RED_BTN, lastStateRedBtn, lastDebounceTimeRed, disableRedBlink, redLedState, RED_LED);
    handleButton(GREEN_BTN, lastStateGreenBtn, lastDebounceTimeGreen, disableGreenBlink, greenLedState, GREEN_LED);
    handleButton(BLUE_BTN, lastStateBlueBtn, lastDebounceTimeBlue, disableBlueBlink, blueLedState, BLUE_LED);
}

void handleButton(int btnPin, int &lastStateBtn, unsigned long &lastDebounceTime, bool &disableBlink, bool &ledState, int ledPin) {
    int currentStateBtn = digitalRead(btnPin);

    if (currentStateBtn != lastStateBtn) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentStateBtn == LOW) {
            if (!disableBlink) {
                disableBlink = true; 
                ledState = LOW; 
                digitalWrite(ledPin, ledState);
            } else {
                ledState = !ledState;
                digitalWrite(ledPin, ledState);
            }
        }
    }

    lastStateBtn = currentStateBtn;
}

void setBrightness(int potPin, int ledPin){
    int potValue = analogRead(potPin);
    int brightness = map(potValue, 0, 1023, 0, 255);
    analogWrite(ledPin, brightness);
}

void handleSerialCommands(){
    if(Serial.available() > 0){
        String command = Serial.readStringUntil('\n');
        command.trim();

    if(command.startsWith("disable button")){
       int button = command.substring(15).toInt();
       if(button == 1) disableRedButton = true;
       Serial.println("Command executed: " + command);    
        }
    }
}