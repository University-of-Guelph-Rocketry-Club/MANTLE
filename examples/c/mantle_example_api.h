#ifndef MANTLE_EXAMPLE_API_H
#define MANTLE_EXAMPLE_API_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* format sets the shared message shapes and packet size */
#define MANTLE_MAX_PACKET_SIZE 255U

typedef enum {
    MANTLE_MESSAGE_TELEMETRY,
    MANTLE_MESSAGE_PING,
    MANTLE_MESSAGE_STATUS
} mantle_message_kind_t;

typedef struct {
    uint32_t mission_time_ms;
    int32_t altitude_cm;
    uint16_t battery_mv;
} mantle_telemetry_t;

typedef struct {
    uint32_t uptime_ms;
    uint8_t software_major;
    uint8_t software_minor;
} mantle_status_t;

typedef struct {
    mantle_message_kind_t kind;
    uint16_t source;
    uint16_t destination;
    uint16_t sequence;
    /* a union lets messages share memory instead of carrying every payload */
    union {
        mantle_telemetry_t telemetry;
        mantle_status_t status;
    } payload;
} mantle_message_t;

/* encoder turns a message into packet bytes */
bool mantle_encode(const mantle_message_t *message,
                   uint8_t *packet,
                   size_t packet_capacity,
                   size_t *packet_length);

/* decoder turns packet bytes back into a message */
bool mantle_decode(const uint8_t *packet,
                   size_t packet_length,
                   mantle_message_t *message);

/* lora sends the finished packet over the radio */
bool mantle_lora_send(const uint8_t *packet, size_t packet_length);

#endif
