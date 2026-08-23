# MANTLE

**MANTLE** is a lightweight radio protocol for telemetry and command communication between student-built aerospace vehicles and ground systems.

Designed primarily around **LoRa**, MANTLE aims to provide a small, understandable, and robust packet format suitable for rockets, high-altitude balloons, and future flight-computer projects.

## Goals

* Minimal packet overhead
* Binary telemetry and commands
* CRC-based corruption detection
* Sequence numbers and device addressing
* Simple embedded implementation
* Extensible message types
* Hardware-independent design

## Architecture

```text
Sensors / Flight Software
          │
          ▼
       MANTLE
   encode / decode
          │
          ▼
      LoRa Driver
          │
          ▼
          RF
          │
          ▼
   Ground Station
```

MANTLE is currently under active development and its wire format is **not yet stable**.
