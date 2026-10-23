// Simple encode-decode test to check if copy operations and packet creation work properly.
// Compile using the Makefile in this directory.

#include "../mantle.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
    // Create a packet with a basic payload.
    uint8_t hello[] = "Hello world";
    int len = strlen((char*)hello);
    gsc_packet p = {};
    if (gsc_new_packet(&p, 0x01, GSC_RAW_DATA, hello, len + 1)) {
        uint8_t output[128] = {};
        int size = gsc_packet_encode(&p, output, 128);
        printf("Wrote %d bytes for packet encoding\n", size);
        uint8_t magic[5] = {0};
        uint8_t body[128] = {0};
        uint32_t packet_id = 0;
        uint8_t source_id = 0, dest_id = 0, cmd = 0;
        uint16_t packet_checksum = 0;
        uint16_t expected_checksum = gen_crc16(hello, len + 1);
        gsc_packet_decode(output, &packet_id, &source_id, &dest_id, magic, body, 128, &cmd, &packet_checksum);
        printf("Raw packet stream bytes:\n");
        for (int i = 0; i < size; i++) {
            printf("%#02x ", output[i]);
        }
        printf("\nRaw packet stream ASCII:\n");
        for (int i = 0; i < size; i++) {
            printf("%c ", output[i]);
        }
        printf("\n");
        if (packet_checksum == expected_checksum) {
            printf("Checksum passed (%#02x == %#02x)\n", packet_checksum, expected_checksum);
        } else {
            printf("Checksum failed (%#02x != %#02x)\n", packet_checksum, expected_checksum);
        }
        printf("Decoded body: %s\n", body);
        printf("Packet magic: %s\n", magic);
        printf("Packet info: ID: %#02x, SRC: %#02x, DST: %#02x, CMD: %#02x\n", packet_id, source_id, dest_id, cmd); 
    } else {
        printf("Packet creation failed!\n");
    }
    return 0;
}
