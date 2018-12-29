/**
* @file fnc.c
* @brief C file in order to operate cyBot.
* @author Younghoon Ji, Emily Kinne
* @date Nov 30, 2018
*/





#include "fnc.h"

void scan()
{

    int currTheta = 0;
    int CycleP[90]; //Distance data from Ping
    int CycleI[90]; //Distance data from IR
    int i = 0;
    char str[50];
    //scan area in front of cybot
    while (currTheta < 180)
    {
        int IR_value =  ADC0_readData();
        int IR = ADC0_getDistance(IR_value);
        int Ping = ping_getDistance();
        if (IR < 66)
        {
            sprintf(str, "\n\rIR Dist: %d    PING Dist: %d      Theta: %d", IR, Ping, currTheta);
            uart_sendStr(str);
        }
        lcd_printf("STARTING..\nIR Dist: %d\nPING Dist: %d\nTheta: %d", IR, Ping, currTheta);

        CycleP[i] = Ping;
        CycleI[i] = IR;
        currTheta += 2;
        servo_move(currTheta);
        timer_waitMillis(10);
        i += 1;
    }

    int flag = 0;


    int width[10]; //detected object information
    int diss[10];  //detected object information
    int objects = 0; //the number of objects
    int thetaA;
    int thetaB;
    int pingA;
    int pingB;
    //analysis data and find objects



    for (i = 0; i < 90; i += 1)
    {
        lcd_printf("detecting object");
        if (CycleI[i] > 70 && CycleI[i + 1] <= 70 && !flag) //hit an object
        {
            objects += 1;
            thetaA = i * 2;
            pingA = CycleP[i];
            flag = 1;
        }

        if (CycleI[i] < 70 && CycleI[i + 1] >= 70 && flag) //moving away from an object
        {
            char buffers[50];
            char buffer_dis[50]; //new
            thetaB = (i + 1) * 2;
            int center = (i + 1 + (thetaA / 2)) / 2;
            diss[objects] = CycleP[center];
            width[objects] = thetaB - thetaA;
            pingB = CycleP[i + 1];

            float Degree = (thetaB - thetaA) * 3.1415926536 / 180.0;


            //Equation for the object size.
            int size = (int) sqrt((pingA * pingA + pingB * pingB) - (2 * pingA * pingB * cos(Degree)));
//            sprintf(buffers, "\n\rObj: %d Distance: %d ThetaObj: %d WidthObj: %d Theta: %d\n",
//            objects, diss[objects], width[objects], size,(thetaA + thetaB) / 2);
//print data on putty
//            sprintf(buffers, "\n\rObj: %d Theta: %d Distance: %d WidthObj: %d \n",
//                        objects, diss[objects], (thetaA + thetaB) / 2, size);

            sprintf(buffers, "\n\r%d %d %d", (thetaA + thetaB) / 2, diss[objects], size);

            // the putty will displace the imporant information of distance and degree of objects
            // which is helpful to find the way to goal
            uart_sendStr(buffers);
            //printf("%d %d %d\n",((thetaA + thetaB) / 2), diss[objects], width[objects]);

              if(objects >= 2){
                  int dis_btw_obj = (int) sqrt(pow(diss[objects-1],2)+pow(diss[objects],2)
                          -(2*diss[objects-1]*diss[objects]*cos(thetaB-thetaA)));
                  sprintf(buffer_dis, "\n\n\rThe distance Between Obj: %d Obj: %d is %d\n\r",
                          objects-1, objects, dis_btw_obj);
                  uart_sendStr(buffer_dis);
              }


            lcd_printf("Finished!\n%d objects found.", objects);
            flag = 0;
        }
    }



    servo_move(0);
}

void flash()
{
    int i;
    for (i = 0; i < 50; i += 1)
    {
        if (i % 2)
        {
            oi_setLeds(1, 1, 0, 255);
        }
        else
        {
            oi_setLeds(1, 1, 255, 255);
        }
        timer_waitMillis(150);
    }
}

void LED (void) {

    oi_setLeds(1, 1, 255, 240);
    timer_waitMillis(500);
    oi_setLeds(1, 1, 0, 240);
    timer_waitMillis(500);
    oi_setLeds(1, 1, 255, 240);
    timer_waitMillis(500);
    oi_setLeds(1, 1, 0, 240);
    timer_waitMillis(500);
    oi_setLeds(1, 1, 255, 240);
    timer_waitMillis(500);
    oi_setLeds(1, 1, 0, 240);
    timer_waitMillis(500);
    oi_setLeds(1, 1, 255, 240);
    timer_waitMillis(500);
    oi_setLeds(1, 1, 0, 240);
}


void music() {
    unsigned char numberNotes = 20;
    unsigned char MusicNotes[19] = { 65, 66, 65,57,56,56,56,56,56 };

    unsigned char Frequency[19] = { 32, 14, 26, 46, 32, 12, 52, 35,
            12, 24, 48, 35, 12, 31, 31, 31, 34, 13, 33 };

    oi_loadSong(1, numberNotes, MusicNotes, Frequency);
    oi_play_song(1);
    timer_waitMillis(500);
}



