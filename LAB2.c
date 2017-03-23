#include"EE3310_config.h"
#include<p24FJ64GA102.h>
#include "xc.h"
// LED
#define LED0 _RB3
#define LED1 _RB4
#define LED2 _RB5
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
    // Declare Variables
    
    // config_IO
    config_IO();

    while (1){
        /******************************** LED 6 ON **************************************/
        if(SW3 == OFF){ // if the switch is pushed
            while(SW3 == OFF);//Wait till the switch is RELEASED
            LED6 = ON; //turn led 6 on
            delay();
        } //END 1ST IF
        else {
            while(SW3==ON);
            while(SW3==OFF);
            LED6=ON;
            delay();
        }
               
        /******************************** LED 6 OFF **************************************/
        // the code got here meaning that led 6 is on 
        if(SW3 == OFF){ // if the switch is pushed 
            while(SW3 == OFF); // wait till the switch is released
            LED6=OFF; // turn led 6 off
            delay();
        } //end of 2nd if
        else{ // if it is not pressed yet 
            while( SW3 == ON); // wait till it is pressed
            while( SW3 == OFF); //wait till it is released
            LED6=OFF; // turn led 6 off  
            delay();
        } //end of 2nd else
        
       /******************************** LED 5 ON **************************************/
        if(SW3 == OFF){ //if the switch is pushed
            while(SW3==OFF); // wait till it is released
            LED5=ON; 
            delay();
        }//end of 3rd if
        else {
            while(SW3 == ON); //Wait till it is pressed 
            while(SW3 == OFF); // wait till it is released
            LED5=ON; 
            delay();
        } //end of 3rd else
        
       /******************************** LED 5 OFF **************************************/
        if(SW3 == OFF){ // if the switch is pushed
            while(SW3 == OFF); // wait till the switch is released
            LED5=OFF; 
            delay();
        } //end of 2nd if
        else{ // if it is not pressed yet 
            while( SW3 == ON); // wait till it is pressed
            while( SW3 == OFF); //wait till it is released
            LED5=OFF;
            delay();
        } //end of 2nd else
        
        /******************************** LED 4 ON **************************************/
        if(SW3 == OFF){ // if the switch is pushed
            LED4=ON;
            delay();}
        else{ // if the switch is not pushed
            while(SW3==ON); //wait till it is pushed
            LED4=ON; 
            delay();
        }
        
        /******************************** LED 4 OFF & LED 3 ON**************************************/
        while(SW3==OFF); // wait till it is released
        LED4=OFF;
        LED3=ON;
        delay();
        
        /******************************** LED 2 ON **************************************/
        if(SW3 == OFF){ //if the switch is pressed 
            LED2=ON;
            delay();}
        else{ // if the switch is not pushed
            while(SW3==ON); //wait till it is pushed
            LED2=ON;
            delay();
        }
        
        /******************************** LED 3 OFF & LED 1 ON **************************************/
        while(SW3 == OFF); // wait till iit is released
        LED3=OFF;
        LED1=ON;
        delay();
        /******************************** LED 0 ON & LED 1 OFF **************************************/
       if(SW3 == OFF){ //if the switch is pressed 
            LED0=ON;
            LED1=OFF;
       delay();}
        else{ // if the switch is not pushed
            while(SW3==ON); //wait till it is pushed
            LED0=ON;
            LED1=OFF;
            delay();
        }
        
        /******************************** LED 2 OFF & LED 0 OFF **************************************/
        while(SW3 == OFF); //wait till it is released
        LED2=OFF;
        LED0=OFF;
        delay();
    }

        return 0;
}
