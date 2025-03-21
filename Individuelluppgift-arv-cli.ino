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
#define RESET_BTN 2

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
volatile unsigned long lastResetTime = 0;

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

bool overrideRedLed = false;
bool overrideGreenLed = false;
bool overrideBlueLed = false;
bool overrideBlueLedPower = -1;

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

    pinMode(RESET_BTN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RESET_BTN), resetProgram, FALLING);

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

        if (!disableRedBlink && !disableRedButton && !overrideRedLed) {
            redLedState = !redLedState;
            digitalWrite(RED_LED, redLedState);
        }

        if (!disableGreenBlink && !disableGreenButton && !overrideGreenLed) {
            greenLedState = !greenLedState;
            digitalWrite(GREEN_LED, greenLedState);
        }

        if (!disableBlueBlink && !disableBlueButton && !overrideBlueLed) {
            blueLedState = !blueLedState;
            digitalWrite(BLUE_LED, blueLedState);
        }
    }
    if (overrideBlueLed){
        if(overrideBlueLedPower >= 0){
            int potValue = map(overrideBlueLedPower, 0, 10, 0, 255);
            analogWrite(BLUE_LED, potValue);
        }

    } else if(!disableBlueBlink && !disablePotentiometer){
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
       if(button == 2) disableGreenButton = true;
       if(button == 3) disableBlueButton = true;
    } else if(command.startsWith("enable button")){
       int button = command.substring(14).toInt();
       if(button == 1) disableRedButton = false;
       if(button == 2) disableGreenButton = false;
       if(button == 3) disableBlueButton = false;

    } else if(command == "disable pot"){
        disablePotentiometer = true;
    } else if(command == "enable pot"){
        disablePotentiometer = false;

    }else if(command.startsWith("LedOff")){
       int led = command.substring(7).toInt();
       if(led == 1) overrideRedLed = true;
       if(led == 2) overrideGreenLed = true;
       if(led == 3) overrideBlueLed = true;
    }else if(command.startsWith("LedOn")){
       int led = command.substring(6).toInt();
       if(led == 1) overrideRedLed = false;
       if(led == 2) overrideGreenLed = false;
       if(led == 3) overrideBlueLed = false;
    
    }else if (command.startsWith("LedPower")){
       int power = command.substring(9).toInt();
       if(power >= 0 && power <= 10){
        overrideBlueLed = true;
        overrideBlueLedPower = power;
       }else if(power == -1){
        overrideBlueLed = false;
        overrideBlueLedPower = -1;
       }

    }else if(command.startsWith("reset")){
        resetProgram();
        }

       Serial.println("Command executed: " + command);    
        }
    }

void resetProgram() {
    unsigned long currentTime = millis();
    if(currentTime - lastResetTime > debounceDelay) {
        lastResetTime = currentTime;

        Serial.println("Reset triggered!");

        redLedState = LOW;
        greenLedState = LOW;
        blueLedState = LOW;

        disableRedBlink = false;
        disableGreenBlink = false;
        disableBlueBlink = false;

        disableRedButton = false;
        disableGreenButton = false;
        disableBlueButton = false;

        disablePotentiometer = false;

        overrideRedLed = false;
        overrideGreenLed = false;
        overrideBlueLed = false;
        overrideBlueLedPower = -1;

        digitalWrite(RED_LED, redLedState);
        digitalWrite(GREEN_LED, greenLedState);
        digitalWrite(BLUE_LED, blueLedState);
    }
}