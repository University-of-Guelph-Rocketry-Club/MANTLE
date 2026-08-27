#include "mantle_example_api.h"

#include <stdio.h>

enum {
    FLIGHT_COMPUTER_ID = 1,
    GROUND_STATION_ID = 100
};

/* static means this number remembers where it was last time */
static uint16_t next_sequence;

static bool send_telemetry(uint32_t mission_time_ms,
                           int32_t altitude_cm,
                           uint16_t battery_mv)
{
    /* naming every field means fewer mystery numbers to figure out */
    mantle_message_t message = {
        .kind = MANTLE_MESSAGE_TELEMETRY,
        .source = FLIGHT_COMPUTER_ID,
        .destination = GROUND_STATION_ID,
        .sequence = next_sequence++,
        .payload.telemetry = {
            .mission_time_ms = mission_time_ms,
            .altitude_cm = altitude_cm,
            .battery_mv = battery_mv,
        },
    };
    /* this byte bucket is where the message gets ready for the radio */
    uint8_t packet[MANTLE_MAX_PACKET_SIZE];
    size_t packet_length = 0;

    /* packet length does weird pointer stuff so encode can fill it in */
    if (!mantle_encode(&message, packet, sizeof(packet), &packet_length)) {
        return false;
    }

    /* the radio only sees bytes it has no clue they came from a rocket */
    return mantle_lora_send(packet, packet_length);
}

int main(void)
{
    /* pretend these readings came from sensors somewhere way more exciting */
    if (!send_telemetry(12500U, 183420, 3980U)) {
        fputs("telemetry transmission failed\n", stderr);
        return 1;
    }

    return 0;
}
