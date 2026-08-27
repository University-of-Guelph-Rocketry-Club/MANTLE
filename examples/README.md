# MANTLE Examples

These examples show how the different parts of MANTLE fit together while we
figure out the wire format and API. They are deliberately basic, so use them to
learn the flow rather than as a promise of what the final code will look like.

| Example | Project directories | Purpose |
| --- | --- | --- |
| [Periodic telemetry](telemetry.md) | [`format/`](../format/) [`encoder/`](../encoder/) [`lora/`](../lora/) | Build serialize and send sensor data |
| [Ping and reply](ping.md) | [`format/`](../format/) [`encoder/`](../encoder/) [`decoder/`](../decoder/) [`lora/`](../lora/) | Decode a request and send a matching reply |
| [Encode/decode loopback](loopback.md) | [`format/`](../format/) [`encoder/`](../encoder/) [`decoder/`](../decoder/) | Check serialization and parsing without a radio |
| [Flight-computer cycle](flight-cycle.md) | [`format/`](../format/) [`encoder/`](../encoder/) [`decoder/`](../decoder/) [`lora/`](../lora/) | Handle a command and transmit telemetry in one cycle |
| [Ground-station receiver](ground-station.md) | [`format/`](../format/) [`decoder/`](../decoder/) | Validate route and display received messages |

## C Examples

The [`c/`](c/) directory has matching C examples you can poke around in:

- [`telemetry.c`](c/telemetry.c) builds, encodes, and transmits telemetry.
- [`ping_responder.c`](c/ping_responder.c) validates a ping and sends a status reply.
- [`loopback.c`](c/loopback.c) checks an encoder/decoder round trip.
- [`flight_computer_cycle.c`](c/flight_computer_cycle.c) combines command handling and telemetry transmission.
- [`ground_station_receiver.c`](c/ground_station_receiver.c) validates, filters, and displays received packets.

For now [`mantle_example_api.h`](c/mantle_example_api.h) gives the examples a
small pretend API while the real one is still being built:

- message types stand in for [`format/`](../format/).
- `mantle_encode` stands in for [`encoder/`](../encoder/).
- `mantle_decode` stands in for [`decoder/`](../decoder/).
- `mantle_lora_send` stands in for [`lora/`](../lora/).

It does not define the real packet layout. We will swap it for the public
MANTLE headers once those are ready.

Syntax-check the examples with:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Iexamples/c -fsyntax-only examples/c/*.c
```

Use the real definitions from the matching project directories when they land.
