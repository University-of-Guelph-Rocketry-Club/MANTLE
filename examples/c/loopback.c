#include "mantle_example_api.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    /* this is the message we know should work */
    const mantle_message_t original = {
        .kind = MANTLE_MESSAGE_TELEMETRY,
        .source = 1,
        .destination = 100,
        .sequence = 42,
        .payload.telemetry = {
            .mission_time_ms = 12500U,
            .altitude_cm = 183420,
            .battery_mv = 3980U,
        },
    };
    /* no radio here the bytes take a little trip through local memory */
    uint8_t packet[MANTLE_MAX_PACKET_SIZE];
    size_t packet_length = 0;
    mantle_message_t decoded;

    /* assert stops everything if reality disagrees with us */
    assert(mantle_encode(&original, packet, sizeof(packet), &packet_length));
    assert(mantle_decode(packet, packet_length, &decoded));

    /* compare fields one by one because structs can have
     * weird invisible padding bytes hiding inside */
    assert(decoded.kind == original.kind);
    assert(decoded.source == original.source);
    assert(decoded.destination == original.destination);
    assert(decoded.sequence == original.sequence);
    assert(decoded.payload.telemetry.mission_time_ms ==
           original.payload.telemetry.mission_time_ms);
    assert(decoded.payload.telemetry.altitude_cm ==
           original.payload.telemetry.altitude_cm);
    assert(decoded.payload.telemetry.battery_mv ==
           original.payload.telemetry.battery_mv);

    puts("loopback passed");
    return 0;
}
