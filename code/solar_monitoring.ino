#define BLYNK_TEMPLATE_ID "TMPL3jePB3OQX"
#define BLYNK_TEMPLATE_NAME "mini project"
#define BLYNK_AUTH_TOKEN "F8KURffIpqp7EquNp8kf565H1hOYnpEJ"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Mini_project";
char pass[] = "kishorik";

#include <DHT.h>
#include <ESP32Servo.h>

// -------- DHT --------
#define DHT_PIN 15
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// -------- LDR --------
#define LDR_PIN 34

// -------- Voltage --------
#define VOLTAGE_PIN 36

const float ADC_Resolution = 4095.0;
const float Vref = 3.3;
const float voltageDividerRatio = 6.0 / 3.3;

// -------- Servo --------
Servo myServo;
int servoPin = 13;
 
// -------- Timer --------
BlynkTimer timer;

// -------- Function --------
void sendData() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  int ldrValue = analogRead(LDR_PIN);
  int adcValue = analogRead(VOLTAGE_PIN);

  float voltageAtPin = (adcValue / ADC_Resolution) * Vref;
  float actualVoltage = voltageAtPin * voltageDividerRatio;

  // ✅ LDR Scaling (IMPORTANT FIX)
  int ldrPercent = map(ldrValue, 0, 4095, 0, 100);

  // -------- SERIAL OUTPUT --------
  Serial.println("------ SENSOR DATA ------");

  if (isnan(t) || isnan(h)) {
    Serial.println("❌ DHT Error!");
  } else {
    Serial.print("🌡 Temp: ");
    Serial.print(t);
    Serial.print(" °C | 💧 Humidity: ");
    Serial.println(h);
  }

  Serial.print("🌞 LDR Raw: ");
  Serial.print(ldrValue);
  Serial.print(" | %: ");
  Serial.println(ldrPercent);

  Serial.print("🔋 Voltage: ");
  Serial.print(actualVoltage);
  Serial.println(" V");

  // -------- SERVO CONTROL --------
  if (ldrValue > 2000) {
    Serial.println("➡ Low Light → Servo 180°");
    myServo.write(180);
  } else {
    Serial.println("➡ Bright Light → Servo 0°");
    myServo.write(0);
  }

  Serial.println("--------------------------\n");

  // -------- SEND TO BLYNK --------
  Blynk.virtualWrite(V3, t);              // Temperature
  Blynk.virtualWrite(V4, h);              // Humidity
  Blynk.virtualWrite(V5, actualVoltage);  // Voltage
}

// -------- SETUP --------
void setup() {
  Serial.begin(115200);

  dht.begin();

  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400);

  Serial.println("Connecting to WiFi...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("✅ Connected to Blynk!");

  timer.setInterval(2000L, sendData);  // every 2 sec
}

// -------- LOOP --------
void loop() {
  Blynk.run();
  timer.run();
}
