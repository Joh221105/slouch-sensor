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
  } else {  
    if (buttonState) {
      if (!longPressDetected) {
        if (!firstButtonClicked) {
          recordStraightPosture();    // calls function to record straight posture x y z values
          firstButtonClicked = true;
        } else if (!initialized) {
            recordSlouchPosture();    // if it is the second time short pressing button, record slouch x y z values
            initialized = true;
            threshold_angle = calculateThreshold();    // calculate threshold angle based on straight and slouch x y z readings
        }
      }
      buttonState = false;
      longPressDetected = false;
    }
}
 if (initialized) {
        checkSlouch();    // if initialization is complete, checks if the user is slouching
    }
    delay(500);
}

void recordStraightPosture() {
    getMPUData(straight_x, straight_y, straight_z);    // retrieves and updates straight xyz values
}

void recordSlouchPosture() {
    getMPUData(slouch_x, slouch_y, slouch_z);    // retrieves and updates slouch xyz values
}

float calculateThreshold() {                        // calculates threshold angle, addw weight to directions more affected by slouching posture
    return (2.0 * abs(straight_x - slouch_x)) + 
           (1.0 * abs(straight_y - slouch_y)) + 
           (0.5 * abs(straight_z - slouch_z));
}

void getMPUData(float &x, float &y, float &z) {
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);      // retrieves and calculates angle in degrees for x y and z
    x = atan2(ay, az) * 180 / PI;
    y = atan2(ax, az) * 180 / PI;
    z = atan2(ax, ay) * 180 / PI;
}

void checkSlouch() {
    getMPUData(current_x, current_y, current_z);
    float currentAngle = (2.0 * abs(straight_x - current_x)) + 
                         (1.0 * abs(straight_y - current_y)) + 
                         (0.5 * abs(straight_z - current_z));

    if (currentAngle >= threshold_angle) {
        if (buzzerMode) {
            digitalWrite(buzzerPin, HIGH);
        } else {
            digitalWrite(ledPin, HIGH);
        }
    } else {
        digitalWrite(buzzerPin, LOW);
        digitalWrite(ledPin, LOW);
    }
}

