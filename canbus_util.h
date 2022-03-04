#ifndef CANBUS_UTIL_H
#define CANBUS_UTIL_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define mkShort(x,y) ((uint16_t)(y << 8 | x))

#define SI_CHARGE_PARAMS_FRAME 0x351
#define SI_VOLTAGE_FRAME 0x356
#define SI_SOC_FRAME 0x355
#define SI_ID_FRAME 0x35F
#define SI_NAME_FRAME 0x35E
#define SI_FAULT_FRAME 0x35A

#ifdef __cplusplus
extern "C" {
#endif

void parse_charge_params_frame(uint8_t frame[], uint16_t *finalChargeVoltage, uint16_t *maxChargeCurrent, uint16_t *maxDischargeCurrent, uint16_t *finalDischargeVoltage);
void parse_soc_frame(uint8_t frame[], uint16_t *stateOfCharge, uint16_t *stateOfHealth, uint16_t *stateOfChargeHighPrecision);
void parse_voltage_frame(uint8_t frame[], uint16_t *batteryVoltage, uint16_t *batteryCurrent, uint16_t *batteryTemp);

#ifdef __cplusplus
}
#endif

#endif /* CANBUS_UTIL_H */

