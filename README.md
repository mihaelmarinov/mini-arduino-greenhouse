# Smart Automated Greenhouse (Arduino + AI)

Welcome to the **Smart Automated Greenhouse** project — a compact, intelligent, and expandable system designed to monitor and optimize plant growth using a combination of microcontrollers, sensors, actuators, and AI-powered pest detection.

This DIY-friendly greenhouse prototype automates watering, lighting, and climate control, logs environmental data, and uses a trained Convolutional Neural Network (CNN) to identify pests via a camera module. It’s ideal for research, personal experimentation, education, or as a foundation for a future agri-tech product.

---

##  Features

- ** Automated Irrigation** — based on real-time soil moisture readings
- ** Smart Cooling System** — fan speed adjusts based on temperature and humidity
- ** Light Control** — LED grow lights switch based on ambient light levels
- ** LCD Monitoring** — displays current temperature, humidity, soil moisture, and light
- ** SD Card Logging** — stores data for trend analysis and diagnostics
- ** CNN-Based Pest Detection** — detects common greenhouse pests using AI
- ** IoT-Ready Architecture** — easily expandable with Blynk, MQTT, or cloud services
- ** Optional Solar Panel Integration** — supports sustainable off-grid operation

---

##  Tech Stack

### Hardware

- **Microcontroller:** Arduino Uno
- **Sensors:**
  - DHT11 or DHT22 (Temperature & Humidity)
  - Soil Moisture Sensor
  - LDR (Light Sensor)
- **Actuators:**
  - Water Pump
  - Cooling Fan (PWM controlled)
  - Grow Light (LED)
- **Other Modules:**
  - 16x2 LCD with I2C
  - MicroSD Card Module
  - ESP32-CAM or Raspberry Pi Camera (for CNN pest detection)
- **Power Options:** USB, battery, or solar panel

### Software

- **Arduino IDE** — for main control code
- **Python (TensorFlow, Keras)** — for pest classifier model training and inference
- **OpenCV** — for camera image preprocessing
- **Jupyter Notebook** — for AI model development
- **Flask (optional)** — for web-based control and alerts
