# Ping and Reply

A ping is a harmless first command-flow test: the ground station requests a reply and the flight computer returns a small status message.

It uses [`format/`](../format/) for the two message shapes
[`decoder/`](../decoder/) for the incoming ping [`encoder/`](../encoder/) for
the reply and [`lora/`](../lora/) for transmission.

## Request

```text
kind: ping
source: ground station
destination: flight computer
sequence: 7
payload: empty
```

## Reply

```text
kind: status reply
source: flight computer
destination: ground station
sequence: 7
payload:
  software version
  uptime
```

The reply should identify the request it answers, for example by reusing or explicitly referencing its sequence number once the format defines that behavior.

## Flow

```text
ground station encodes and transmits the ping
flight computer validates the packet and checks its destination
flight computer encodes and transmits a status reply
ground station validates the reply and matches it to the request
```
