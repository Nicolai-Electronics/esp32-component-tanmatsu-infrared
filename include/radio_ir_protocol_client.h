#pragma once

#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"

typedef enum {
    IR_PROTOCOL_CLIENT_TYPE_ACK           = 0x00,
    IR_PROTOCOL_CLIENT_TYPE_NACK          = 0x01,
    IR_PROTOCOL_CLIENT_TYPE_GET_SUPPORTED = 0x02,
    IR_PROTOCOL_CLIENT_TYPE_SET_CONFIG    = 0x03,
    IR_PROTOCOL_CLIENT_TYPE_SEND_NEC      = 0x10,
} ir_protocol_client_packet_type_t;

typedef struct {
    uint32_t sequence_number;
    uint32_t type;  // ir_protocol_client_packet_type_t
} __attribute__((packed)) ir_protocol_client_header_t;

// Body of the reply to IR_PROTOCOL_CLIENT_TYPE_GET_SUPPORTED
typedef struct {
    uint8_t available;
} __attribute__((packed)) ir_protocol_client_supported_t;

typedef struct {
    uint32_t frequency_hz;  // Carrier frequency, the radio enforces a minimum of 2kHz
    uint8_t  duty_cycle;    // Carrier duty cycle as a fraction of 256, the radio enforces a maximum of 128 (50%)
} __attribute__((packed)) ir_protocol_client_config_t;

typedef struct {
    uint16_t address;
    uint16_t command;
} __attribute__((packed)) ir_protocol_client_nec_scan_code_t;

// Functions

esp_err_t ir_protocol_client_init(void);

/// @brief Ask the radio whether it has an infrared transmitter
/// @return ESP_OK if infrared is available, ESP_ERR_NOT_SUPPORTED if the radio (or this target) has no infrared
///         transmitter, or another error code if communication with the radio failed
esp_err_t ir_protocol_client_get_supported(void);
esp_err_t ir_protocol_client_set_config(const ir_protocol_client_config_t* config);
esp_err_t ir_protocol_client_send_nec(const ir_protocol_client_nec_scan_code_t* scan_code);
