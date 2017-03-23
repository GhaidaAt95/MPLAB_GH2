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
   TRISA = 0b01000; //Setting _RA3 as an input
   TRISB = 0x0000; // Setting PortB as Output 
   PORTA = 0b00000;
   PORTB = 0x0000; // Output Zero on all bits
   _CN29PUE = 1;
   }//end of config_PORTS 
void config_Timer1(){
        T1CON=0x0000;
        T1CONbits.TCKPS = 0b11;//256
         PR1 =1784;
        _T1IP =1;
        _T1IF =0;
        _T1IE =0; // if you are going to only use the flag then do not enable the interrupt but 
                  // since we're using it here then enable it
        }
void Run_Timer1(int light){
    if (light == 1){
    PR1 =1784.714286;}
    if(light==2) {
    PR1 =3124;  }
    if(light==3){
        PR1=77;
    }
    T1CONbits.TON=1;
    while(!_T1IF);
    _T1IF=0;
     TMR1=0;
    T1CONbits.TON=0; 
}
void delay(void){
    int i,j;
    for(i=0;i<=12;i++){
        for(j=0;j<=200;j++){
                    }//end of second loop
    } //end of first loop
}
void config_CN(){
        _CNIP=7; 
        _CNIF=0;
        _CNIE=1;
        _CN29IE=1;
            }
void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void){
    int count =0;
    if(SW3==OFF){
        while(SW3==OFF){
            delay();
            count++;
        }
    }           
    if(count>=3){
              if(start == 3){
                       Dir_Led=descending;temp=start=9;}
              else if(start==9){
                       Dir_Led=ascending;temp=start=3; }     
                    }
    if(count!=3)count=0;
      _CNIF=0;
}
int main(void) {
    config_PORTS();
    config_Timer1();
    config_CN();
    while(1){
       for(temp=start;temp<=9 && temp>=3;temp=temp+Dir_Led ){
         PORTB &= 0; 
         power = (int) pow(2,temp);
         PORTB |= power; 
         Run_Timer1(1);
          
                                                             } 
       if(temp==10 || temp ==2) {
           Run_Timer1(2);
       }
    }
    return 0;
}
 