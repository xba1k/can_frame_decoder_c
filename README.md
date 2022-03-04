# can_frame_decoder

## Overview

This is an example native decoder for CAN frames broadcasted by the CANBridge via UDP. Compatible with SMA frame format.

## Installation

This code is intended for Ubuntu and similar Linux distributions. Run make to build.

## Demo

```
./can_frame_decoder
Waiting for packets...
Thu Mar  3 16:56:35 192.168.1.61 ID: chemistry Li, hw_ver 3844, capacity 66.00, sw_ver 5905
Thu Mar  3 16:56:36 192.168.1.61 States: stateOfCharge 85, stateOfHealth 80, stateofChargeHighPrecision 8500
Thu Mar  3 16:56:46 192.168.1.61 BMS Name: SIConfig
Thu Mar  3 16:56:46 192.168.1.61 ID: chemistry Li, hw_ver 3844, capacity 66.00, sw_ver 5905
Thu Mar  3 16:56:47 192.168.1.61 Charge params: finalVoltage 57.40, maxChargeCurrent 30.00, maxDischargeCurrent 100.00, finalDischargeVoltage 42.00
Thu Mar  3 16:56:48 192.168.1.61 States: stateOfCharge 85, stateOfHealth 80, stateofChargeHighPrecision 8500
Thu Mar  3 16:56:57 192.168.1.61 BMS Name: SIConfig
Thu Mar  3 16:56:58 192.168.1.61 ID: chemistry Li, hw_ver 3844, capacity 66.00, sw_ver 5905
Thu Mar  3 16:56:58 192.168.1.61 States: stateOfCharge 85, stateOfHealth 80, stateofChargeHighPrecision 8500
```