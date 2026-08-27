#include "mantle_example_api.h"

enum {
    FLIGHT_COMPUTER_ID = 1
};

bool handle_radio_packet(const uint8_t *packet,
                         size_t packet_length,
                         uint32_t uptime_ms)
{
    mantle_message_t request;

    /* turn weird radio bytes back into something humans can understand */
    if (!mantle_decode(packet, packet_length, &request)) {
        return false;
    }

    /* do not answer random messages or somebody elses mail */
    if (request.kind != MANTLE_MESSAGE_PING ||
        request.destination != FLIGHT_COMPUTER_ID) {
        return false;
    }

    /* reuse the sequence number so the ground station knows which ping this is */
    mantle_message_t reply = {
        .kind = MANTLE_MESSAGE_STATUS,
        .source = FLIGHT_COMPUTER_ID,
        .destination = request.source,
        .sequence = request.sequence,
        .payload.status = {
            .uptime_ms = uptime_ms,
            .software_major = 0,
            .software_minor = 1,
        },
    };
    /* the reply needs its own byte bucket before the radio can launch it */
    uint8_t reply_packet[MANTLE_MAX_PACKET_SIZE];
    size_t reply_length = 0;

    /* these address things let encode write into our variables */
    if (!mantle_encode(&reply,
                       reply_packet,
                       sizeof(reply_packet),
                       &reply_length)) {
        return false;
    }

    return mantle_lora_send(reply_packet, reply_length);
}
