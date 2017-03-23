/*
 * File:   Lab02_GJA.c
 * Author: ghaida
 *
 * Created on February 14, 2017, 11:29 AM
 */
/* Start with all the LEDs off.
* 1. Press and Release the switch (SW3) one time. LED6->ON.
* 2. Press and Release SW3 again. LED6->OFF.
* 3. Press and Release SW3 LED5->ON.
* 4. Press and Release SW3 LED5->OFF.
* 5. Press SW3 LED4->ON.
* 6. Release SW3 LED4->OFF and LED3->ON.
* 7. Press SW3 LED2->ON.
* 8. Release SW3 LED3->OFF and LED1->ON.
* 9. Press SW3 LED0->ON and LED1->OFF.
* 10. Release SW3 LED2->OFF and LED0->OFF.
* 11. Return to Step 1 and repeat
 */
#include<p24FJ64GA102.h>
#include "xc.h"
// LED
#define LED0 _RB2
#define LED1 _RB3
#define LED2 _RB4
#define LED3 _RB6
#define LED4 _RB7
#define LED5 _RB8
#define LED6 _RB9
// Switch
#define SW3 _RA3
//ON & OFF value
enum state { ON=1, OFF=0};

void config_IO(void){
    AD1PCFG = 0xFFFF  ;
    TRISA   = 0x0008  ; // SW3 on _RA3  // 0b 0000 0000 0000 1000
    TRISB   = 0x0000  ; // LEDs on _RB3 through _RB9 
    PORTA   = 0x0000 ;
    PORTB   = 0x0000  ;
    _CN29PUE=1;
  }
void delay(void){
    int i,j;
    for(i=0;i<=10;i++){
        for(j=0;j<=100;j++){
                    }//end of second loop
    } //end of first loop
}
int main(void) {
      config_IO();

    while (1){
        // LED6 ON 
        if(SW3 == ON ){
            while(SW3 == ON);//Wait till the switch is off
            LED6 = ON; }
        else continue ; // if the switch is not on then start over 
        //LED6 OFF 
        if(SW3 == ON) { 
            while(SW3==ON);// wait till it is off
            LED6= OFF;
        }
        else { // if it is not on then it is off 
            while(SW3 == OFF); //wait till it is on
            while(SW3==ON); // wait till it is off 
            LED6= OFF;
        }
        //LED5 ON 
         if(SW3 == ON) {
            while(SW3==ON);//wait till it is off
            LED5= ON;
        }
         else { // if it is not on then
            while(SW3 == OFF); // wait till it is on
            while(SW3==ON); //wait till it is off
             LED5 =ON;
        }
        //LED5 OFF
        if(SW3 == ON) {
            while(SW3==ON);//wait till it is off
            LED5= OFF;
        }
        else {
            while(SW3 == OFF); // wait till it is on
            while(SW3==ON); //wait till it is off
            LED5= OFF;
        }
        //LED4 ON
        if(SW3==ON) LED4= ON;
        else { 
            while(SW3==OFF);
            LED4=ON;
        }
        //LED4 OFF AND LED 3 ON 
           while(SW3==ON);
            LED4=OFF;
            LED3=ON;
        // LED2 ON
            if(SW3 == ON) LED2 = ON;
            else {
                while(SW3==OFF);
                LED2=ON;
            }
        //LED3 OFF AND LED1 ON
            while(SW3==ON);
            LED3=OFF;
            LED1=ON;
        //LED0 ON and LED1 OFF
            while(SW3==OFF);
            LED0 = ON;
            LED1= OFF;
        //LED2 OFF and LED0 OFF
            while(SW3==ON);
            LED2 = OFF;
            LED0 = OFF;
               }
            return 0;
}
