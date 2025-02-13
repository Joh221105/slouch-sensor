# Slouch Sensor


## Description
This project serves as a Slouch Detection System using an Arduino and the MPU6050 sensor. The system monitors and improve posture by detecting when a user is slouching and providing feedback in the form of either a buzzer or an LED indicator. This is a protoype of a potentially wearable device that allows users to toggle between feedback modes and set custom slouch detection thresholds.

## Features
- A long press of the button sets the feedback mode, allowing the user to choose how they receive alerts for slouching.
- The device can detect slouching by comparing current position to calculated threshold angle.
- When slouching is detected, the system provides feedback by either buzzer or LED depending on mode.
- The slouch threshold is custom set by recording the user's straight and slouched postures, providing flexibility for different users.

## Function
- The user can long press the button to switch between the buzzer and LED feedback modes.
- The user records their upright posture by pressing the button once during initialization.
- The user records their slouched posture by pressing a second time during initialization.
- The threshold angle is determined through a formula, adding more weight to the axis most affected by slouching.
- The device continuously checks the user's posture and provides feedback if the slouching threshold is exceeded.

## Components 
- Arduino 
- MPU6050
- Buzzer
- LED 
- Button 
- Resistors 

## Installation
Connect the MPU6050 sensor to the Arduino according to the wiring diagram.
Upload the code to your Arduino using the Arduino IDE.
Use the button to toggle between feedback modes, record your straight and slouched postures, and begin receiving posture feedback.

## Library
- MPU6050 Library: MPU6050 by Electronic Cats
