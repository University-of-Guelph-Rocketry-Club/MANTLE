# Ground-Station Receiver

This example shows the receiving side of an application rather than only a
single encode/decode operation. The code is in
[`c/ground_station_receiver.c`](c/ground_station_receiver.c).

It uses [`format/`](../format/) for the expected message shapes and
[`decoder/`](../decoder/) for validation and parsing. Radio reception belongs
to [`lora/`](../lora/) and hands complete packets into this example.

## Flow

```text
receive bytes from the radio driver
decode and validate them
ignore packets not addressed to this ground station or from this flight computer
display telemetry or status data
warn if telemetry sequence numbers skip a value
```

Give each radio packet to `ground_station_handle_packet()`. The example tracks
telemetry from one expected flight computer and accepts normal 16-bit sequence
wraparound from `65535` to `0`. A multi-vehicle ground station would keep this
state separately for every source ID.
