/*
 * Copyright (c) 2022 Mr. Green's Workshop https://www.MrGreensWorkshop.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* PicoDRO 
 * DIY digital readout with Linear scales using Raspberry Pi Pico
 */

#include <stdio.h>
#include "qdec/QuadratureDecoder.h"

#define LED_PIN PICO_DEFAULT_LED_PIN

void flashLedOnce(void) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // Led ON
    gpio_put(LED_PIN, 1);
    sleep_ms(200);
    // Led OFF
    gpio_put(LED_PIN, 0);
}

int main(void)
{
    QuadratureDecoder qdec; 
    // As long as there are two pins in a row, any two pins can be assigned for each axis.
                        //  X:A X:B Y:A Y:B Z:A Z:B
    const char pinList[] = {16, 17, 18, 19, 20, 21};
    const char pinCnt = sizeof(pinList);
    const char axisCnt = pinCnt / 2;
    const char axisNames[] = {'X', 'Y', 'Z'};
    // readInterval < sendIntervalMin < sendIntervalMax
    // I didn't test the minimum response time of the system.
    // Time interval between encoder readings. (in milliseconds)
    const uint32_t readInterval = 9;
    // Minimum time interval between sending encoder values to the host when the encoder value has changed. (in milliseconds)
    const uint32_t sendIntervalMin = 10;
    // Maximum time interval between sending encoder values to the host when the encoder value has not changed. (in milliseconds)
    const uint32_t sendIntervalMax = 1000;

    int32_t stateMachineList[axisCnt];
    int32_t axisValList[axisCnt];
    int32_t axisValListOld[axisCnt];

    stdio_init_all();

    flashLedOnce();

    qdec.init(pio0);

    int x = 0;
    for(int i = 0; i < pinCnt; i++) {
        gpio_init(pinList[i]);
        gpio_disable_pulls(pinList[i]);
        if (i % 2 == 0) {
            stateMachineList[x++] = qdec.addQuadratureEncoder(pinList[i]);
        }
    }

    absolute_time_t readIntervalTime = nil_time;
    absolute_time_t sendIntervalTime = nil_time;
    bool setNextIntervalFlg = false;
    while (1) {
        if (absolute_time_diff_us(get_absolute_time(), readIntervalTime) < 0) {
            for(int i = 0; i < axisCnt; i++) {
                axisValList[i] = qdec.getCount(stateMachineList[i]);
                
                if (axisValListOld[i] != axisValList[i]) {
                    if (setNextIntervalFlg == false) {
                        sendIntervalTime = make_timeout_time_ms(sendIntervalMin);
                        setNextIntervalFlg = true;
                    }
                    axisValListOld[i] = axisValList[i];
                }
            }
            readIntervalTime = make_timeout_time_ms(readInterval);
        }

        if (absolute_time_diff_us(get_absolute_time(), sendIntervalTime) < 0) {
            for(int i = 0; i < axisCnt; i++) {
                printf("%c%d;", axisNames[i], axisValList[i]);
            }
            sendIntervalTime = make_timeout_time_ms(sendIntervalMax);
            setNextIntervalFlg = false;
        }
    }
}
