# Smart Solar Monitoring

This project monitors solar panel conditions using an ESP32, DHT11 temperature/humidity sensor, an LDR for light detection, and a voltage sensor.

## Project Structure

- `code/solar_monitoring.ino` - Arduino sketch for ESP32 with Blynk integration.
- `images/` - Store files for the project visuals.
  - `images/circuit-diagram.png` - circuit wiring diagram first
  - `images/project-photo-1.png` - actual project photos after the diagram
  - `images/project-photo-2.png`

## Circuit Diagram

Add your wiring and connection diagram first. This should show:

- ESP32 pin connections
- DHT11 sensor wiring
- LDR connection
- Voltage divider connections
- Servo power and signal wiring

## Code

The main sketch is in `code/solar_monitoring.ino`.

Example from the project:

```cpp
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h>

#define DHT_PIN 15
#define DHTTYPE DHT11
```

## Features

- Reads temperature and humidity from a DHT11 sensor.
- Measures ambient light using an LDR.
- Calculates voltage using an analog voltage divider.
- Sends sensor data to a Blynk dashboard.
- Controls a servo motor based on light levels.

## Hardware

Recommended components:

- ESP32 development board
- DHT11 temperature/humidity sensor
- Light Dependent Resistor (LDR)
- Voltage divider circuit for analog voltage measurement
- Servo motor
- Breadboard, jumper wires, and power supply

## Configuration

Update these values in `code/solar_monitoring.ino`:

- `BLYNK_AUTH_TOKEN` - your Blynk project token
- `ssid` - your Wi-Fi network name
- `pass` - your Wi-Fi password

## Usage

1. Open `code/solar_monitoring.ino` in the Arduino IDE.
2. Install required libraries: `WiFi`, `WiFiClient`, `BlynkSimpleEsp32`, `DHT`, `ESP32Servo`.
3. Configure the Blynk app with matching virtual pins:
   - V3: temperature
   - V4: humidity
   - V5: voltage
4. Upload the sketch to the ESP32.
5. Monitor serial output at `115200` baud.

## Notes

- The sketch maps LDR values to a percentage and moves the servo to 180° in low light.
- Ensure the voltage divider safely scales your voltage into the ESP32 analog input range.

## Improvements

- Add error handling for Blynk connection loss.
- Add calibration for the LDR and voltage measurements.
- Add diagrams to `images/` for wiring clarity.
