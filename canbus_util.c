#include "canbus_util.h"

void parse_charge_params_frame(uint8_t frame[], uint16_t *finalChargeVoltage, uint16_t *maxChargeCurrent, uint16_t *maxDischargeCurrent, uint16_t *finalDischargeVoltage) {

    *finalChargeVoltage = mkShort(frame[0], frame[1]);
    *maxChargeCurrent = mkShort(frame[2], frame[3]);
    *maxDischargeCurrent = mkShort(frame[4], frame[5]);
    *finalDischargeVoltage = mkShort(frame[6], frame[7]);

}

void parse_soc_frame(uint8_t frame[], uint16_t *stateOfCharge, uint16_t *stateOfHealth, uint16_t *stateOfChargeHighPrecision) {

    *stateOfCharge = mkShort(frame[0], frame[1]);
    *stateOfHealth = mkShort(frame[2], frame[3]);
    *stateOfChargeHighPrecision = mkShort(frame[4], frame[5]);

}

void parse_voltage_frame(uint8_t frame[], uint16_t *batteryVoltage, uint16_t *batteryCurrent, uint16_t *batteryTemp) {

    *batteryVoltage = mkShort(frame[0], frame[1]);
    *batteryCurrent = mkShort(frame[2], frame[3]);
    *batteryTemp = mkShort(frame[4], frame[5]);

}
