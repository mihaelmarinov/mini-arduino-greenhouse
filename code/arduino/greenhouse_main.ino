
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

// ----- Pin Definitions -----
const int soilMoisturePin = A0;
const int lightSensorPin = A1;
const int waterPumpPin = 4;
const int fanPin = 5; // PWM pin
const int lightPin = 6;
const int dhtPin = 2;
const int chipSelect = 10;

// ----- Sensor Thresholds -----
const int soilDryThreshold = 400;
const int lightThreshold = 300;  // Lower = darker

// ----- DHT Sensor -----
#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);

// ----- LCD -----
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ----- SD Logging -----
File logFile;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Greenhouse Boot");

  // Set pin modes
  pinMode(waterPumpPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card failed!");
  } else {
    Serial.println("SD card initialized.");
    logFile = SD.open("datalog.csv", FILE_WRITE);
    if (logFile) {
      logFile.println("Time,Temp,Humidity,Soil,Light,Fan,Water");
      logFile.close();
    }
  }

  delay(2000);
  lcd.clear();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = analogRead(soilMoisturePin);
  int lightLevel = analogRead(lightSensorPin);

  // Fan speed based on temperature
  int fanSpeed = map(temperature, 20, 40, 0, 255);
  fanSpeed = constrain(fanSpeed, 0, 255);
  analogWrite(fanPin, fanSpeed);

  // Watering logic
  bool pumpOn = false;
  if (soilMoisture > soilDryThreshold) {
    digitalWrite(waterPumpPin, HIGH);
    pumpOn = true;
  } else {
    digitalWrite(waterPumpPin, LOW);
  }

  // Light control
  if (lightLevel < lightThreshold) {
    digitalWrite(lightPin, HIGH);
  } else {
    digitalWrite(lightPin, LOW);
  }

  // LCD display
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" H:");
  lcd.print(humidity);

  lcd.setCursor(0, 1);
  lcd.print("Soil:");
  lcd.print(soilMoisture);
  lcd.print(" L:");
  lcd.print(lightLevel);

  // SD Logging
  logFile = SD.open("datalog.csv", FILE_WRITE);
  if (logFile) {
    logFile.print(millis());
    logFile.print(",");
    logFile.print(temperature);
    logFile.print(",");
    logFile.print(humidity);
    logFile.print(",");
    logFile.print(soilMoisture);
    logFile.print(",");
    logFile.print(lightLevel);
    logFile.print(",");
    logFile.print(fanSpeed);
    logFile.print(",");
    logFile.println(pumpOn ? "ON" : "OFF");
    logFile.close();
  }

  delay(5000); // Delay 5 seconds between cycles
}
