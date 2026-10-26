# Sharp GP2Y1010AU0F to Arduino Nano Wiring

| Pin # | Wire Color | Sensor Pin | Connection | Description |
|---|---|---|---|---|
| **1** | White | V-LED | Connect to 5V through 150Ω Resistor | LED Power Supply |
| **2** | Blue | LED-GND | Arduino GND | LED Ground |
| **3** | Green | LED | Arduino Digital Pin **D2** | Microsecond Pulse Trigger |
| **4** | Yellow | S-GND | Arduino GND | Sensor Ground |
| **5** | Black | Vo | Arduino Analog Pin **A0** | Photodiode Analog Output |
| **6** | Red | Vcc | Arduino **5V** | Sensor Power Supply |

### Passive Filtering Network
- Place a **220 μF electrolytic capacitor** across Pin 1 (V-LED) and Pin 2 (GND) to stabilize the infrared emitter current pulse.
- Place a **150 Ω current-limiting resistor** between Arduino 5V and Pin 1.
