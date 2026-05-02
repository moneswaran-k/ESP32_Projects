#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
float powergen = 0;
void temp_sens(void *p){
    float temp = -20;
    while(1){
        temp += ((rand()%5)-2)*0.5;
        printf("Climate Temp : %.2f\n",temp);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void battery_temp(void *p){
    float temp = 10;
    while(1){
        temp+=((rand()%5)-2)*0.5;
        printf("Battery Temp : %.2f\n",temp);
        if(temp>40){
            printf("ShutDown Protocol Initiated\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void airspeed(void *p){
    float rpm = 100;
    while(1){
        rpm += ((rand()%5)-2)*1000;
        powergen+=rpm/10;
        printf("Wind_Power:%.2f\n",powergen);
        printf("RPM : %.2f\n",rpm);
        if(rpm>1000){
            printf("Shutoff Terbine\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void powergen1(void *p){
    float s = 0;
    while(1){
        s = ((rand()%100))*10;
        powergen += s; //solar cells
        printf("Solar_Cell_Power:%.2f\n",s);
        printf("Total Power Generated : %.2f\n",powergen);
        powergen=0;
        vTaskDelay(1000/portTICK_PERIOD_MS);
}
}
void data_transmit(void *p){
    int antenna = 0;
    while(1){
        antenna = (rand()%2);
       if(antenna==1){
            printf("Antenna Online\n");
            printf("----------------------END-OF-TRANSMISSION-----------------------------\n");
        }
        else{
            printf("Antenna Offline\n");
            printf("----------------------------------------------------------------------\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}

void app_main(void)
{
        srand(time(NULL));
        xTaskCreatePinnedToCore(battery_temp,"Battery_Temperature",2048,NULL,5,NULL,0);
        xTaskCreatePinnedToCore(airspeed,"Wind_Energy",2048,NULL,5,NULL,0);
        xTaskCreatePinnedToCore(powergen1,"Power_generation",2048,NULL,4,NULL,0);
        xTaskCreatePinnedToCore(temp_sens,"Climate_Temp",2048,NULL,3,NULL,1);
        xTaskCreatePinnedToCore(data_transmit,"Transmission",2048,NULL,2,NULL,1);
}
