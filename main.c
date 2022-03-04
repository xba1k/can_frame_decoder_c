#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <assert.h>
#include <time.h>
#include "canbus_util.h"

// UDP port
#define LISTEN_PORT 1080

/*
 
 Decode and print CANBus frames sent by SMA SunnyIsland power inverter and compatible Battery Management Systems
 
 */

void print_frame(uint8_t *frame, int len) {

    uint32_t id = *((uint32_t*) frame);
    uint8_t *data = frame + 4;

    switch (id) {

        case SI_CHARGE_PARAMS_FRAME:
        {
            uint16_t finalChargeVoltage, maxChargeCurrent, maxDischargeCurrent, finalDischargeVoltage;
            parse_charge_params_frame(data, &finalChargeVoltage, &maxChargeCurrent, &maxDischargeCurrent, &finalDischargeVoltage);
            printf("Charge params: finalVoltage %0.2f, maxChargeCurrent %0.2f, maxDischargeCurrent %0.2f, finalDischargeVoltage %0.2f\n", finalChargeVoltage / 10.0,
                    maxChargeCurrent / 10.0, maxDischargeCurrent / 10.0, finalDischargeVoltage / 10.0);
            break;
        }
        case SI_VOLTAGE_FRAME:
        {
            uint16_t batteryVoltage, batteryCurrent, batteryTemp;
            parse_voltage_frame(data, &batteryVoltage, &batteryCurrent, &batteryTemp);            
            printf("Voltage params: batteryVoltage %0.2f, batteryCurrent %0.2f, batteryTemp %hu\n", batteryVoltage / 10.0, batteryCurrent / 10.0, batteryTemp);
            break;
        }
        case SI_SOC_FRAME:
        {
            uint16_t stateOfCharge, stateOfHealth, stateOfChargeHighPrecision;
            parse_soc_frame(data, &stateOfCharge, &stateOfHealth, &stateOfChargeHighPrecision);
            printf("States: stateOfCharge %hu, stateOfHealth %hu, stateofChargeHighPrecision %hu\n", stateOfCharge, stateOfHealth, stateOfChargeHighPrecision);
            break;
        }
        case SI_ID_FRAME:
        {
            struct _id_frame {
                uint16_t chemistry;
                uint16_t hw_ver;
                uint16_t capacity;
                uint16_t sw_ver;

            } *id_frame = (struct _id_frame*) data;

            printf("ID: chemistry %c%c, hw_ver %hu, capacity %0.2f, sw_ver %hu\n", (char) id_frame->chemistry, *((char*) &id_frame->chemistry + 1), id_frame->hw_ver, id_frame->capacity / 10.0, id_frame->sw_ver);
            break;
        }
        case SI_NAME_FRAME:
        {
            char bms_name[100];
            memcpy(bms_name, data, len - 4);
            bms_name[len - 4] = 0;
            printf("BMS Name: %s\n", bms_name);
            break;
        }
        case SI_FAULT_FRAME:
        {
            struct _faults {
                uint8_t f0, f1, f2, f3;
            } *faults = (struct _faults*) data;

            printf("Faults: f0 %hhx, f1 %hhx, f2 %hhx, f3 %hhx\n", faults->f0, faults->f1, faults->f2, faults->f3);
            break;
        }

        default:
        {
            int i;
            printf("unknown frame type 0x%04hx, data: ", id);
            for(i = 0; i < len; i++) {
                printf("0x%02hhx ", frame[i]);
            }
            printf("\n");
            break;
        }

    }

}

int main(int argc, char** argv) {

    struct sockaddr_in si_me, si_other;
    int sock;
    int broadcast = 1;
    uint8_t buf[2048];

    assert((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) != -1);
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof (broadcast));

    memset(&si_me, 0, sizeof (si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(LISTEN_PORT);
    si_me.sin_addr.s_addr = INADDR_ANY;

    assert(bind(sock, (struct sockaddr *) & si_me, sizeof (struct sockaddr)) != -1);

    printf("Waiting for packets...\n");

    while (1) {
        unsigned slen = sizeof (struct sockaddr);
        int bytes = recvfrom(sock, buf, sizeof (buf), 0, (struct sockaddr *) & si_other, &slen);
        time_t t = time(NULL);
        
        printf("%.19s %s ", ctime(&t), inet_ntoa(si_other.sin_addr));
        print_frame(buf, bytes);
    }

    return (EXIT_SUCCESS);

}

