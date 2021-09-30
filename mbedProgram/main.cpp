/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdio>
#include <string>
#include <cmath>

#define centorX 256
#define maxPower 0.1

#define P 0.05

PwmOut a[]{
 PwmOut (A2),
 PwmOut (A1)
};

PwmOut b[]{
 PwmOut (A5),
 PwmOut (A3)
};

DigitalOut led(D13);

static UnbufferedSerial pc(USBTX, USBRX);

void setPower(float power,int motorNum){
    if(power>1){
        power=1.f;
    }else if(power<-1){
        power=-1;
    }
/*
    if(power>maxPower){
        power=maxPower;
    }else if(power<-maxPower){
        power=-maxPower
    }
*/
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

void getSerial(){
    led!=led;
}

int main()
{
    //printf("Hello, Mbed!\n");

    pc.baud(115200);

    pc.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );

    std::string str;

    str="hellow?\r\n";
    char readBuf[255];
    char buf[1];
    int charCount=0;

    std::string readStr;
    int kinds=1; // ラインの種類
    int x;
    int y;
    int w;

    int error=0;
    float f_error=0;

    //pc.attach(&getSerial,SerialBase::RxIrq);

    while(1){
        while(1){
            pc.read(buf,1);
            if(buf[0]=='q'){
                break;
            }
            readBuf[charCount]=buf[0];
            charCount++;
//            print("Count:%d\n",charCount);
        }

        kinds=readBuf[0]-'0';
        x=0;
        charCount=0;
        x=(readBuf[2]-'0')*100+(readBuf[3]-'0')*10+readBuf[4]-'0';

        readStr=to_string(kinds);
        readStr+=',';
        readStr+=to_string(x);
        readStr+='\n';

        //readStr = readBuf;
        pc.write(readStr.c_str(),readStr.size());
        readStr.clear();

        error=x-centorX;
        f_error=error/256.f;

        setPower(0.58+f_error*P,2);
        setPower(0.58-f_error*P,1);
        //pc.write(readBuf,2);
/*        pc.write(str.c_str(),str.size());
	    setPower(0.9,1);
        setPower(0.9,2);
*/	    //printf("output:0\t");
	    ThisThread::sleep_for(10);
/*
        setPower(0,1);
        setPower(0,2);
*/        //printf("output:0.8\n");
 /*       ThisThread::sleep_for(1000);

	    setPower(-0.9,1);
        setPower(-0.9,2);
*/	    //printf("output:0.8\n");
/*	    ThisThread::sleep_for(1000);

        setPower(0,1);
        setPower(0,2);
  */      //printf("output:0.8\n");
    //    ThisThread::sleep_for(1000);
    }
    return 0;
}
