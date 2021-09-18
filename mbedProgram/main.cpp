/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdio>
#include <string>

PwmOut a[]{
 PwmOut (A1),
 PwmOut (A2)
};

PwmOut b[]{
 PwmOut (A3),
 PwmOut (A5)
};


static UnbufferedSerial pc(USBTX, USBRX);

void setPower(float power,int motorNum){
    if(power>1){
        power=1.f;
    }else if(power<-1){
        power=-1;
    }


    if (motorNum==1){
        if(power>0){
            a[0]=1.f;
            a[1]=1.f-power;
        }else{
            a[1]=1.f;
            a[0]=1.f-fabs(power);
        }
    }else if(motorNum==2){
        if(power>0){
            b[0]=1.f;
            b[1]=1.f-power;
        }else{
            b[1]=1.f;
            b[0]=1.f-fabs(power);
        }

    }
}

int main()
{
    //printf("Hello, Mbed!\n");

    pc.baud(9600);
    pc.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );

    std::string str;

    str="hellow?\r\n";

    while(1){
        pc.write(str.c_str(),str.size());
	    setPower(0.9,1);
        setPower(0.9,2);
	    //printf("output:0\t");
	    ThisThread::sleep_for(1000);

        setPower(0,1);
        setPower(0,2);
        //printf("output:0.8\n");
        ThisThread::sleep_for(1000);

	    setPower(-0.9,1);
        setPower(-0.9,2);
	    //printf("output:0.8\n");
	    ThisThread::sleep_for(1000);

        setPower(0,1);
        setPower(0,2);
        //printf("output:0.8\n");
        ThisThread::sleep_for(1000);
    }
    return 0;
}
