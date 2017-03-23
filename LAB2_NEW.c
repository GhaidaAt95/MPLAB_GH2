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
enum { ON=1, OFF=0 };

void config_IO(void){
    AD1PCFG = 0xFFFF  ;
    TRISA   = 0b01000;  ; // SW3 on _RA3  // 0b 0000 0000 0000 1000
    TRISB   = 0x0000  ; // LEDs on _RB3 through _RB9 
    PORTA   = 0b00000 ;
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
    int count =0;
    // config_IO
    config_IO();
   
    while(1){
        if( SW3 == OFF){
            count = count+1; //add 1 to the counter every time the button is pressed
        }//end if(1)
         
             if ( count >=1 && count<=4){ //For LED6 and LED5
                 while(SW3 == OFF); // wait till the push button is released 
             if(count == 1) { LED6=ON; delay();} // if this is the first time then turn led6 on
             else if(count ==2) LED6=OFF; //if this is the second time then turn led6 off
             else if(count ==3) { LED5=ON; delay();} //if this is the 3rd time then turn led5 on
             else if(count ==4) LED5=OFF;//if this is the 4th time then turn led5 off
             }//end if(2)
             if(count >= 5 && count<=7){ // Rest of the LEDs
                 if(count==5){
                     LED4=ON; //after Led5 is off and the next push occurs turn led4 on
                     while(SW3==OFF);//wait till the button is released
                     LED4=OFF; //turn led4 of
                     delay(); //delay that makes up for the bouncing of the switch
                     LED3=ON; //turn led3 on
                             }//end inner if(1)
                 else if(count==6){
                     LED2=ON; 
                     while(SW3==OFF);
                     LED3=OFF;
                      delay();
                     LED1=ON;
                 }
                 else if(count==7){
                     LED0=ON;
                      delay();
                     LED1=OFF;
                     while(SW3==OFF);
                     LED2=OFF; 
                      delay();
                     LED0=OFF;
                     count =0; //reset the counter
                 }
             }//end if(3)
        
       
        
          }
    return 0;
}
