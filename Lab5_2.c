#include "EE3310_config.h"
#include "xc.h"
#include<p24FJ64GA102.h>
#include<math.h>
#define SW3 _RA3
enum  { ON = 1 , OFF =0 };
enum Direction { ascending = 1, descending =-1 };
enum Direction Dir_Led = ascending;
int start=3 ;
int temp=0;
int power;
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
        T1CONbits.TCKPS = 0b10;//64
         PR1 =6249;//0.1SEC 
        _T1IP =1;
        _T1IF =0;
        _T1IE =0;  }
void config_Timer2(){
        T2CON=0x0000;
        T2CONbits.TCKPS = 0b11;//256
         PR2 =77; 
        _T2IP =4;
        _T2IF =0;
        _T2IE =1;  }
void Run_Timer1(int light){
    if (light == 1){
    PR1 =6249;}
    if(light==2) {
    PR1 =12499;  }
    T1CONbits.TON=1;
    while(!_T1IF);
    _T1IF=0;
     TMR1=0;
    T1CONbits.TON=0; 
}
void __attribute__((__interrupt__,no_auto_psv)) _T2Interrupt(void){
    T2CONbits.TON=0; 
    static int Sw_Count=0;
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
                        Sw_Count=0;}
    _T2IF=0;
     TMR2=0;
    T2CONbits.TON=1;
    }
int main(void) {
    config_PORTS();
    config_Timer1(); 
    config_Timer2();
    T2CONbits.TON=1;
     while(1){
         for(temp=start;temp<=10 && temp>=3;temp=temp+Dir_Led ){
         PORTB &= 0; 
         power = (int) pow(2,temp);
         PORTB |= power; 
         Run_Timer1(1);} 
       if(temp==11 || temp ==2) {
           Run_Timer1(2);}
    }
 return 0;
}
