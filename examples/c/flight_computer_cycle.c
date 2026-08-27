#include "mantle_example_api.h"

enum {
    FLIGHT_COMPUTER_ID = 1,
    GROUND_STATION_ID = 100,
    SOFTWARE_MAJOR = 0,
    SOFTWARE_MINOR = 1
};

/* telemetry has its own counter so every send gets a fresh number */
static uint16_t next_telemetry_sequence;

static bool send_status_reply(const mantle_message_t *request,
                              uint32_t uptime_ms)
{
    const mantle_message_t reply = {
        .kind = MANTLE_MESSAGE_STATUS,
        .source = FLIGHT_COMPUTER_ID,
        .destination = request->source,
        /* this reply points back to the ping that started it */
        .sequence = request->sequence,
        .payload.status = {
            .uptime_ms = uptime_ms,
            .software_major = SOFTWARE_MAJOR,
            .software_minor = SOFTWARE_MINOR,
        },
    };
    uint8_t reply_packet[MANTLE_MAX_PACKET_SIZE];
    size_t reply_length = 0;

    if (!mantle_encode(&reply,
                       reply_packet,
                       sizeof(reply_packet),
                       &reply_length)) {
        return false;
    }

    return mantle_lora_send(reply_packet, reply_length);
}

static bool handle_command_packet(const uint8_t *packet,
                                  size_t packet_length,
                                  uint32_t uptime_ms)
{
    mantle_message_t request;

    if (!mantle_decode(packet, packet_length, &request)) {
        return false;
    }

    /* other vehicles can use the radio too so leave their traffic alone */
    if (request.destination != FLIGHT_COMPUTER_ID) {
        return true;
    }

    if (request.kind == MANTLE_MESSAGE_PING) {
        return send_status_reply(&request, uptime_ms);
    }

    /* toss more command types in here later */
    return true;
}

/*
 * call this once each flight computer cycle
 * hand it fresh sensor readings plus a radio packet when one shows up
 */
bool flight_computer_run_cycle(uint32_t mission_time_ms,
                               int32_t altitude_cm,
                               uint16_t battery_mv,
                               uint32_t uptime_ms,
                               const uint8_t *received_packet,
                               size_t received_packet_length)
{
    if (received_packet_length != 0U) {
        if (received_packet == NULL ||
            !handle_command_packet(received_packet,
                                   received_packet_length,
                                   uptime_ms)) {
            return false;
        }
    }

    const mantle_message_t telemetry = {
        .kind = MANTLE_MESSAGE_TELEMETRY,
        .source = FLIGHT_COMPUTER_ID,
        .destination = GROUND_STATION_ID,
        .sequence = next_telemetry_sequence++,
        .payload.telemetry = {
            .mission_time_ms = mission_time_ms,
            .altitude_cm = altitude_cm,
            .battery_mv = battery_mv,
        },
    };
    uint8_t telemetry_packet[MANTLE_MAX_PACKET_SIZE];
    size_t telemetry_length = 0;

    if (!mantle_encode(&telemetry,
                       telemetry_packet,
                       sizeof(telemetry_packet),
                       &telemetry_length)) {
        return false;
    }

    return mantle_lora_send(telemetry_packet, telemetry_length);
}
