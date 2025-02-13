#include <Wire.h>
#include <MPU6050.h>

// Pins
int buttonPin = 2;          // Button to toggle between LED and Buzzer mode
int ledPin = 13;            // LED pin
int buzzerPin = 8;          // Buzzer pin

MPU6050 mpu;                // MPU6050 object

// slouching and straight back position variables
float straight_x, straight_y, straight_z;
float slouch_x, slouch_y, slouch_z;
float current_x, current_y, current_z;
float threshold_angle = 0;         // angle threshold for slouching, temporary place holder

bool firstButtonClicked = false;
bool buzzerMode = true;  // default buzzer mode on
unsigned long pressStartTime = 0;
bool longPressDetected = false;
const int longPressDuration = 1000;  // 1 second threshold to be considered a long press
bool initialized = false;
bool buttonState = false;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  mpu.initialize();
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {  
        if (!buttonState) {
            buttonState = true;     // acknowledges button press, prevents multiple actions from one button press
            pressStartTime = millis();     // records start time of button press
        }

        if (!longPressDetected && millis() - pressStartTime > longPressDuration) {
            buzzerMode = !buzzerMode;     // toggles between buzzer and LED
            longPressDetected = true;
        }
    } 