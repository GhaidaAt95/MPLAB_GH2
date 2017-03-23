#include "EE3310_config.h"
#include "xc.h"
#include<p24FJ64GA102.h>
#include<math.h>
#define SW3 _RA3
#define Upper_LED 9
#define Lower_LED 3
enum  { ON = 1 , OFF =0 };
enum Direction { ascending = 1, descending =-1 };
enum Direction Dir_Led = ascending;
int start=3 ;
int temp=0;
int power;
int now  =-1;
int prev =-1;
void config_PORTS(){
   AD1PCFG=0xFFFF;
   TRISA = 0b01000; 
   TRISB = 0x0000;
   PORTA = 0b00000;
   PORTB = 0x0000; 
   _CN29PUE = 1;
   }
void config_Timer1(){
        T1CON=0x0000;
        T1CONbits.TCKPS = 0b11;//256
         PR1 =77; 
        _T1IP =4;
        _T1IF =0;
        _T1IE =1;  }
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void){
    T1CONbits.TON=0; 
    static int Sw_Count=0;
    static int Out_Count=1;
        if(SW3==OFF) {
            Sw_Count++;}
           else Sw_Count=0;
        if(Sw_Count>=3) {
                  PORTB &= 0; 
              if(start == 3){
                     Dir_Led=descending;
                     temp=start=10;
                            }
              else if(start==10){
                          Dir_Led=ascending;
                          temp=start=3; 
                                } 
                        Sw_Count=0;// Out_Count=1; now=1;
        }
        Out_Count++;
        if(Out_Count==20) {
                if(now<=7){
                     now++;
                     Out_Count=1;} 
                else{
                     now=9;
                    }
                          }
        if(Out_Count==40){
                   now=1;
                   Out_Count=1;
                         }
    _T1IF =0;
    TMR1=0;
    T1CONbits.TON=1;
    }
int main(void) {
    config_PORTS();
    config_Timer1();    
     while(1){
         for(temp=start;temp<=10 && temp>=3;temp=temp+Dir_Led ){
       if(prev == -1 && now==-1) T1CONbits.TON=1;
             PORTB &= 0;
         power = (int) pow(2,temp);
         PORTB |= power;
         while( prev == now );  
         prev=now;
       }
         if(now==9) while(now==9);
    }
 return 0;
}
