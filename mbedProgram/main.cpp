/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

PwmOut a1(A1);


void setPower(float power,int motorNum){
    if(power>0){
        a1=1.f;
    }else{
        a1=power;
    }
}

int main()
{
    printf("Hello, Mbed!\n");

    while(1){
	    a1=0.f;
	    printf("output:0\t");
	    ThisThread::sleep_for(1000);

	    a1=0.8f;
	    printf("output:0.8\n");
	    ThisThread::sleep_for(1000);
    }
    return 0;
}
