# MANTLE

MANTLE is our radio protocol for sending LoRa messages between club-built HAB
or rocket flight computers and their ground stations.

## What lives where

```text
MANTLE/
|-- format/                 Protocol and packet specifications
|-- encoder/                Packet serialization
|-- decoder/                Packet parsing and validation
|-- lora/                   LoRa integration
|-- tests/                  Automated tests and packet fixtures
|-- docs/                   Design and usage documentation
|-- examples/               Starter protocol workflows
`-- learning/               Informal experiments and practice code
```

## Keeping it portable

Board code will change, even between STM32s, and that is fine. MANTLE should
only define messages, turn them into bytes, and turn those bytes back into
messages. It should not know about STM32 HAL, SPI handles, GPIO pins, FreeRTOS,
or a specific radio driver.

The flight-computer repo owns that board-specific code and passes complete byte
buffers to and from MANTLE. This keeps the packet format the same when the board
or radio changes.

Use `examples/` for maintained starter material and `learning/` for experiments.

Quick heads up: the code in `examples/` is deliberately basic. It shows the
general ideas, not the final API or production architecture, so the finished
MANTLE code will probably look different.

The wire format is still being worked out and is not stable yet.

## Contributing

For each new feature in `format/`, `encoder/`, `decoder/`, `lora/`, or `docs/`,
grab the latest `main` and make one focused feature branch:

```sh
git switch main
git pull --ff-only
git switch -c feature/<short-name>
```

Push the branch and open a pull request before merging it into `main`.
`learning/`, `tests/`, and `examples/` are the relaxed spaces for experiments,
fixtures, and starter code, so this feature-branch rule is for the main project
directories above.
