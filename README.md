# Sharp GP2Y1010AU0F PM2.5 Optical Dust Monitor (Arduino Nano) 🌫️📊
> **Classroom Particulate Matter Telemetry Node with Microsecond Optical Pulse Timing & Linear Dust Density Calibration**

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![MCU: Arduino Nano](https://img.shields.io/badge/MCU-Arduino%20Nano%20(ATmega328P)-blue.svg)]()
[![Sensor: Sharp GP2Y1010](https://img.shields.io/badge/Sensor-Sharp%20GP2Y1010AU0F-lightgrey.svg)]()
[![Author: Haoran Ma](https://img.shields.io/badge/Author-Haoran%20Ma-orange.svg)](https://github.com/MarquantMa)

---

## 1. Overview
Developed for high school classroom and dormitory air quality auditing (IB Group 4 Project / RawSTEAM), this system integrates an **Arduino Nano** with the **Sharp GP2Y1010AU0F** optical dust sensor. By pulsing an internal infrared emitting diode (IRED) and measuring the scattered light with a phototransistor, it accurately quantifies airborne particulate matter concentrations (PM2.5) in $\mu\text{g}/\text{m}^3$.

### Key Technical Aspects:
- **Strict Microsecond Pulse Timing:** Pulses the IRED for exactly $320\mu\text{s}$, reading the ADC sample after $280\mu\text{s}$ settling delay to capture optical scatter at the peak of the light burst.
- **Empirical Calibration:** Converts analog photodiode output voltage into particulate density using Sharp's characteristic curve: $\rho = 0.172 \cdot V - 0.1\;[\text{mg}/\text{m}^3]$.
- **Noise Suppression:** Includes an RC filter (150$\Omega$ resistor + 220$\mu\text{F}$ capacitor) to shield the 10-bit ATmega328P ADC from current transients.

---

## 2. Timing Diagram

```
       +-----------------------+ 10,000 μs (10 ms) Period ---------------------+
       |                                                                        |
IRED:  |__ 280 μs __/-- 40 μs --\_______________________________________________|
       |  (Wait)    |  (Sample)  |                   9,680 μs Sleep
       |            v            |
ADC:   |       [analogRead(A0)]  |
```

---

## 3. Hardware Connections

```
    +----------------------------------+
    | Sharp GP2Y1010AU0F Dust Sensor   |
    |                                  |
    | Pin 1 (V-LED) <---+-- 150Ω Resistor <-- Arduino 5V
    |                   |
    |                [ 220μF Cap ]
    |                   |
    | Pin 2 (LED-GND) <-+------------------> Arduino GND
    | Pin 3 (LED)   <----------------------> Arduino Pin D2
    | Pin 4 (S-GND) <----------------------> Arduino GND
    | Pin 5 (Vo)    -----------------------> Arduino Pin A0
    | Pin 6 (Vcc)   <----------------------> Arduino 5V
    +----------------------------------+
```

---

## 4. Code Example

```cpp
// 1. Trigger Infrared Pulse
digitalWrite(ledPower, LOW); 
delayMicroseconds(280);

// 2. Sample Optical Voltage
float rawSignal = analogRead(dustPin);
delayMicroseconds(40);
digitalWrite(ledPower, HIGH); 
delayMicroseconds(9680);

// 3. Compute Density
float voltage = rawSignal * (5.0 / 1023.0);
float dustDensity = 0.172 * voltage - 0.1; // mg/m³
if (dustDensity < 0) dustDensity = 0;
float ugM3 = dustDensity * 1000.0;         // μg/m³
```

---

## 5. Author & License
- **Author:** Haoran Ma (Marquant) ([GitHub @MarquantMa](https://github.com/MarquantMa))
- **Email:** `marquant_voldemort@icloud.com`
- **License:** MIT License
