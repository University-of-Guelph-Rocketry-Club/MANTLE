# MANTLE
MANTLE is our radio protocol for sending LoRa messages between club-built HAB
or rocket flight computers and their ground stations.

# Example
Below is output from the `tests/encode_decode.c` test case, showcasing MANTLE's packet encoding and decoding functionality:

```
Wrote 27 bytes for packet encoding
Raw packet stream bytes:
0x47 0x53 0x52 0x50 00 00 00 0x67 0x1 0xff 0x1 0xc 0xf1 0x48 0x65 0x6c 0x6c 0x6f 0x20 0x77 0x6f 0x72 0x6c 0x64 00 0x79 0x2f
Raw packet stream ASCII:
G S R P    g  �
                  � H e l l o   w o r l d  y /
Checksum passed (0x2f79 == 0x2f79)
Decoded body: Hello world
Packet magic: GSRP
Packet info: ID: 0x67, SRC: 0xff, DST: 0x1, CMD: 0xf1
```

## Contributing
Grab the latest `main` and make one focused feature branch:

```sh
git switch main
git pull --ff-only
git switch -c feature/<short-name>
```

Push the branch and open a pull request before merging it into `main`.
