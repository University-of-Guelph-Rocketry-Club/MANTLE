# Flight-Computer Cycle

This example combines the two basic sender-side flows: it handles one incoming
command packet and sends the current telemetry in the same scheduled cycle.
The code is in [`c/flight_computer_cycle.c`](c/flight_computer_cycle.c).

It brings together [`format/`](../format/) message definitions
[`decoder/`](../decoder/) command parsing [`encoder/`](../encoder/) packet
serialization and [`lora/`](../lora/) radio transmission.

## Flow

```text
read sensors and uptime
if a radio packet arrived, decode it
if it is a ping for this flight computer, send a status reply
build telemetry with the next telemetry sequence number
encode and transmit the telemetry packet
```

`flight_computer_run_cycle()` takes the packet received by the radio driver as
an argument. Pass a null pointer and length zero when no packet arrived. A real
scheduler can call the function at the desired telemetry interval after it has
collected the latest sensor readings.

The status reply reuses the ping's sequence number so the ground station can
associate it with that request. Telemetry has its own incrementing sequence
stream. The final wire-format specification must define any stronger delivery,
retry, or command-ordering guarantees.
