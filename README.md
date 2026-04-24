# Autonomous Timed Delivery Robot (Arduino + Bluetooth)
<img width="706" height="574" alt="image" src="https://github.com/user-attachments/assets/2a94db77-35fe-4426-a070-2b7ac78ce74c" />

## Overview
This project implements an autonomous delivery robot using an Arduino microcontroller. The robot can operate in two modes:

1. Manual Mode – Controlled via Bluetooth commands
2. Autonomous Mode – Executes a predefined timed navigation path

The robot also uses an ultrasonic sensor to detect obstacles and stop automatically if something blocks its path.

---

## Features

- Manual control using Bluetooth
- Autonomous delivery navigation
- Obstacle detection using ultrasonic sensor
- Automatic stop when obstacle is detected
- LED indicator for delivery point
- Timed movement using Arduino millis()
- Motor control for forward, backward, left, and right movement

---

## Hardware Requirements

- Arduino Uno / Arduino Nano
- L298N Motor Driver
- 2 DC Motors
- HC-05 Bluetooth Module
- HC-SR04 Ultrasonic Sensor
- LED
- Robot chassis with wheels
- Jumper wires
- Battery pack

---

## Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| Left Motor A | 4 |
| Left Motor B | 5 |
| Right Motor A | 6 |
| Right Motor B | 7 |
| Ultrasonic TRIG | 9 |
| Ultrasonic ECHO | 8 |
| Bluetooth RX | 10 |
| Bluetooth TX | 11 |
| LED | 12 |

---

## Manual Control Commands

When autonomous mode is OFF, the robot can be controlled using Bluetooth commands.

| Command | Action |
|-------|--------|
| 2 | Move Forward |
| 3 | Move Backward |
| 4 | Turn Left |
| 5 | Turn Right |
| 6 | Stop |

---

## Autonomous Delivery Mode
Autonomous mode starts when the robot receives the command:1


The robot then performs the following sequence:

1. Move forward
2. Turn right
3. Move forward
4. Turn ON delivery LED (simulating package drop)
5. Turn 180°
6. Move forward
7. Turn left
8. Move forward

After completing the steps, the robot stops and exits autonomous mode.

---

## Obstacle Detection

The robot uses the HC-SR04 ultrasonic sensor to measure distance.

If an object is detected closer than **8 cm**, the robot will:

- Immediately stop
- Pause the current step
- Continue only when the obstacle is removed

Distance formula used:
distance = duration × 0.034 / 2


---

## Software Library Used
SoftwareSerial.h


This library is used for communication with the HC-05 Bluetooth module.

---

## How to Run the Project

1. Upload the Arduino code to the board.
2. Connect all components according to the pin configuration.
3. Pair your phone with the HC-05 Bluetooth module.
4. Use a Bluetooth terminal app.
5. Send commands to control the robot.

Start autonomous mode: 1

Stop the robot: 0


---

## Applications

- Autonomous delivery robots
- Warehouse automation
- Robotics learning projects
- Embedded systems practice
- Obstacle avoidance robots

---

## Future Improvements

- Line following navigation
- Mobile application interface
- Camera-based obstacle detection
- GPS based delivery
- AI path planning

---

## Author

saajina s
Computer Science Engineering Student

Project: Autonomous Timed Delivery Robot using Arduino




Autonomous mode starts when the robot receives the command:
