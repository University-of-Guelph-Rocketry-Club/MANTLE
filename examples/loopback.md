# Encode/Decode Loopback

Use a loopback test to verify an encoder and decoder before introducing a radio.

It uses [`format/`](../format/) for the shared message shape
[`encoder/`](../encoder/) to create packet bytes and [`decoder/`](../decoder/)
to recover the message.

```text
original message = a small telemetry message
encoded packet = encode(original message)
decoded message = decode(encoded packet)
assert decoded message equals original message
```

Also test failure cases:

```text
change one byte in the encoded packet
decode the modified packet
assert validation rejects it
```

Once the format defines a CRC and length rules, this example should become an automated test in `tests/`.
