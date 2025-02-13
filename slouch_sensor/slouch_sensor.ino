#include <Wire.h>
#include <MPU6050.h>

// Pins
int buttonPin = 2;          // Button to toggle between LED and Buzzer mode
int ledPin = 13;            // LED pin
int buzzerPin = 8;          // Buzzer pin

MPU6050 mpu;                // MPU6050 object

// slouching and straight back position variables
int straight_x, straight_y, straight_z;
int slouch_x, slouch_y, slouch_z;
int current_x, current_y, current_z;
int threshold_angle = 90;         // angle threshold for slouching, temporary place holder

bool firstButtonClick = false;
bool buzzerMode = true;  // default buzzer mode on


void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  mpu.initialize();
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
}

void loop() {
  
}