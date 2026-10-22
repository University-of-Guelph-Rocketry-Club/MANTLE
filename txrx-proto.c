#include "txrx-proto.h"

#include "crc.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global packet ID to increment with each newly created packet.
uint32_t packet_id = 0x67;

bool gsc_new_packet(gsc_packet *p, const uint8_t dest, satellite_commands cmd, uint8_t *body, uint32_t body_size) {

    // If no packet or command is provided, or the body is too large to fit.
    if (p == NULL || cmd == 0 || body_size > GSC_MAX_PAYLOAD_SIZE)
        return false; 

    // Fill in the packet header.
    p->header.packet_id = __builtin_bswap32(packet_id); packet_id++;
    p->header.version   = GSC_PROTOCOL_VERSION;
    p->header.source_id = GSC_IDENTITY;
    p->header.dest_id   = dest;
    p->header.body_size = body_size;

    // Fill in remaining data.
    p->cmd = cmd;
    memcpy(p->body, body, body_size);
    p->checksum = gen_crc16(body, body_size);
    
    return true;
}

size_t gsc_packet_encode(const packet *input, uint8_t *output, size_t output_size)
{
    // Ensure non-NULL pointers and appropriate output size.
    if (input == NULL || output == NULL || output_size < (GSC_PACKET_OVERHEAD + input->header.body_size)) {
        return 0;
    }

    // Offset is the index of the next free byte in output.
    size_t offset = 0;

    // The magic string contains four characters, without the string terminator.
    memcpy(output, GSC_MAGIC_STRING, 4);
    offset += 4;

    // Dump the packet header.
    output[offset]   = input->header.packet_id; offset += 4;
    output[offset++] = input->header.version;
    output[offset++] = input->header.source_id;
    output[offset++] = input->header.dest_id;
    output[offset++] = input->header.body_size;

    // Dump remaining packet data then return.
    output[offset++] = (uint8_t)input->cmd;
    memcpy(output + offset, input->body, input->header.body_size);
    offset += input->header.body_size;
    output[offset] = input->checksum;
    offset += 2;
    return offset;
}
