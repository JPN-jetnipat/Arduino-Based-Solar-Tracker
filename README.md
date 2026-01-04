# Arduino-Based Solar Tracker with Dust Detection and Vibration Cleaning System

## Overview
This project is an **Arduino-based Solar Tracker** integrated with **Dust Detection** and **Vibration Cleaning**. It uses sensors to measure dust levels and adjusts the solar panel's position based on sunlight intensity.

### Inspiration:
Inspired by space missions and Mars rovers, this system can be applied to residential rooftops, improving solar panel efficiency through automatic cleaning.

## Key Features:
- **Dust Detection & Vibration Cleaning**: Measures dust and triggers a vibration motor to clean the panel.
- **Dual-Axis Solar Tracking**: Rotates the panel based on sunlight intensity in two axes.
- **Alert System**: Buzzer and LCD display for dust and tracking info.

## Components:
- **Arduino UNO (ATmega328P)**
- **LDRs, Servo Motors (SG90/MG90S), Dust Sensor**
- **Vibration Motor, LCD Display, Buzzer, Push Button**

## How It Works:
- **Dust Detection**: Dust levels are measured, and the motor is triggered for cleaning.
- **Solar Tracking**: LDR sensors detect sunlight and adjust the panel's position.
- **Alert System**: Alerts for cleaning when dust is high and updates on panel position.

## Arduino Code:
- **Initialization**: Sets up servo motor, LCD, and sensor pins.
- **Sensor Readings**: Reads LDR and dust sensor values to adjust the panel.
- **LED Indicators**: Uses LEDs to show dust levels (Red, Yellow, Green).
- **Vibration Control**: Activates cleaning motor if dust is high.

```cpp
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Definitions
int ldrLeft = A0, ldrRight = A1, servoPin = 9, dustSensorPin = A2;
