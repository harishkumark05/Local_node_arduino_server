# Arduino Sensor Monitoring System

This project demonstrates a sensor monitoring system using an Arduino board. It reads data from temperature, smoke, and motion sensors, 
displays it on an LCD screen, and sends it over Bluetooth.

## Components Used
- Arduino board (e.g., Arduino Uno)
- LM35 temperature sensor
- Smoke sensor
- PIR motion sensor
- 16x2 LCD display
- Bluetooth module (e.g., HC-05)

## Libraries Used
- SoftwareSerial: Allows communication on digital pins using software (for Bluetooth communication).
- LiquidCrystal: Enables easy control of LCD displays.

## Pin Configuration
- LM35 Temperature Sensor:
  - Signal Pin: A1
  - Power Pin: 5V
  - Ground Pin: GND

- Smoke Sensor:
  - Signal Pin: A0
  - Power Pin: 5V
  - Ground Pin: GND

- PIR Motion Sensor:
  - Signal Pin: D6
  - Power Pin: 5V
  - Ground Pin: GND

- LCD Display:
  - RS Pin: 12
  - Enable Pin: 11
  - D4 Pin: 5
  - D5 Pin: 4
  - D6 Pin: 3
  - D7 Pin: 2
  - Power Pins: 5V (VCC), GND

- Bluetooth Module (HC-05):
  - RX Pin: D9
  - TX Pin: D10
  - Power Pins: 5V (VCC), GND

## Setup
1. Connect the components according to the specified pin configurations.
2. Upload the provided code to your Arduino board.
3. Open a serial monitor to view the sensor data (optional).
4. Connect to the Arduino via Bluetooth to receive sensor data remotely.

## Functionality
- Reads temperature data using the LM35 sensor and converts it to Celsius.
- Reads smoke data from the smoke sensor.
- Detects motion using the PIR motion sensor.
- Displays temperature and smoke status on the LCD screen.
- Sends sensor data as JSON over Bluetooth for remote monitoring.


# Node.js Sensor Data Logger

This Node.js application logs sensor data from a serial port and sends it to a RabbitMQ message broker for further processing.
It includes functionality to handle temperature, smoke, and motion sensor data.

## Prerequisites
- Node.js installed on your system
- Serial port device connected to your system
- RabbitMQ server or cloud-based service credentials (for message queueing)

