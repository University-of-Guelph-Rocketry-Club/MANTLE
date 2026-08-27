# Periodic Telemetry

This example sends a small status update from a flight computer to a ground station.

It uses [`format/`](../format/) for the telemetry message shape
[`encoder/`](../encoder/) for serialization and [`lora/`](../lora/) for radio
transmission.

## Message Intent

```text
kind: telemetry
source: flight computer
destination: ground station
sequence: next transmit sequence number
payload:
  mission time
  altitude
  battery voltage
```

The final protocol specification will define field identifiers, units, byte order, and payload encoding.

## Sender Flow

```text
read the sensors
build a telemetry message
assign the next sequence number
encode the message into a packet
transmit the packet through the LoRa driver
```

## Receiver Flow

```text
receive a packet from the LoRa driver
decode and validate the packet
discard it if validation fails
record or display the telemetry payload
```
