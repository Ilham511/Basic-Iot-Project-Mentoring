# Vehicle Parking Sensor

## Project Overview

This project is an ESP32-based vehicle parking sensor prototype developed as part of a group-based IoT project learning activity.

The system uses an ultrasonic sensor to detect the distance between the vehicle and an obstacle. LED indicators and a buzzer provide visual and audio warnings based on the detected distance.

## Hardware

- ESP32
- HC-SR04 ultrasonic sensor
- Green LED
- Yellow LED
- Red LED
- Buzzer
- Breadboard
- Jumper wires
- LCD I2C

## Distance Status

| Distance | Status |
|---|---|
| 30–25 cm | SAFE |
| 25–15 cm | WARNING |
| 15–0 cm | DANGER |
| >30 cm | OUT OF RANGE |

## System Concept

The HC-SR04 measures the distance to an obstacle. The ESP32 processes the distance data and determines the corresponding warning status.

The LED indicators and buzzer are activated according to the detected distance.

## Project Context

This prototype was developed by a group of new Automotive Engineering students under the guidance of student facilitators.

The code in this repository is a reimplemented version based on the project specifications and activity documentation. It is not the original source code used during the activity.
