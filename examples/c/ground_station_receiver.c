#include "mantle_example_api.h"

#include <inttypes.h>
#include <stdio.h>

enum {
    FLIGHT_COMPUTER_ID = 1,
    GROUND_STATION_ID = 100
};

/* this little demo follows telemetry from one flight computer */
static bool have_last_telemetry_sequence;
static uint16_t last_telemetry_sequence;

static void observe_telemetry_sequence(uint16_t sequence)
{
    if (have_last_telemetry_sequence &&
        (uint16_t)(last_telemetry_sequence + 1U) != sequence) {
        fprintf(stderr,
                "warning: telemetry sequence jumped from %u to %u\n",
                (unsigned int)last_telemetry_sequence,
                (unsigned int)sequence);
    }

    last_telemetry_sequence = sequence;
    have_last_telemetry_sequence = true;
}

/* pass each radio packet into this function */
bool ground_station_handle_packet(const uint8_t *packet, size_t packet_length)
{
    mantle_message_t message;

    if (packet == NULL || packet_length == 0U ||
        !mantle_decode(packet, packet_length, &message)) {
        return false;
    }

    /* decode first then see if this packet is for us */
    if (message.destination != GROUND_STATION_ID ||
        message.source != FLIGHT_COMPUTER_ID) {
        return true;
    }

    switch (message.kind) {
    case MANTLE_MESSAGE_TELEMETRY:
        observe_telemetry_sequence(message.sequence);
        printf("telemetry: time=%" PRIu32 " ms, altitude=%" PRId32
               " cm, battery=%u mV\n",
               message.payload.telemetry.mission_time_ms,
               message.payload.telemetry.altitude_cm,
               (unsigned int)message.payload.telemetry.battery_mv);
        return true;

    case MANTLE_MESSAGE_STATUS:
        printf("status: uptime=%" PRIu32 " ms, software=%u.%u\n",
               message.payload.status.uptime_ms,
               (unsigned int)message.payload.status.software_major,
               (unsigned int)message.payload.status.software_minor);
        return true;

    case MANTLE_MESSAGE_PING:
        /* pings usually head to the flight computer so skip them here */
        return true;

    default:
        return false;
    }
}
