#!/usr/bin/env python3
import serial
import time
import sys

PORT = sys.argv[1] if len(sys.argv) > 1 else '/dev/cu.usbserial-110'
BAUD = 9600

print(f"Connecting to Dust Sensor on {PORT} at {BAUD} baud...")
try:
    ser = serial.Serial(PORT, BAUD, timeout=2)
    print("Connected. Logging PM2.5 readings (Press Ctrl+C to stop)...")
    while True:
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        if line:
            print(f"[{time.strftime('%H:%M:%S')}] {line}")
except KeyboardInterrupt:
    print("\nExiting logger.")
except Exception as e:
    print(f"Serial Error: {e}")
