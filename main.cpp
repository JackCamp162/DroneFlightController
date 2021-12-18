/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "ADXL345.h"



#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

//#define WAIT_TIME_MS 500 
ADXL345 accelerometer(D7, D6, D4, D5);
Serial pc(USBTX, USBRX);

//PinName mosi, PinName miso, PinName sck, PinName cs

int main()
{
    printf("This is the bare metal blinking LED", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        led1 = !led1;
        thread_sleep_for(WAIT_TIME_MS);
    }

    int readings[3] = {0, 0, 0};
    
    printf("Starting ADXL345 test...\n");
    printf("Device ID is: 0x%02x\n", accelerometer.getDevId());

    //Go into standby mode to configure the device.
    accelerometer.setPowerControl(0x00);

    //Full resolution, +/-16g, 4mg/LSB.
    accelerometer.setDataFormatControl(0x0B);
    
    //3.2kHz data rate.
    accelerometer.setDataRate(ADXL345_3200HZ);

    //Measurement mode.
    accelerometer.setPowerControl(0x08);

    while (1) {
        
        accelerometer.getOutput(readings);
        
        //13-bit, sign extended values.
        printf("%i, %i, %i\n", (int16_t)readings[0], (int16_t)readings[1], (int16_t)readings[2]);

    }
}
