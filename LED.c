#include "../EE3310_config.h"
#include <p24FJ64GA102.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <xc.h>

void Config_IO (void){
    TRISA   =  0b00000 ; 
    PORTA = 0x0000;
    AD1PCFG = 0xFFFF;
    TRISB   = 0x0000; 
    PORTB = 0x0000;
   }  // end config_IO
void Config_T1 (void){
        T1CON=0x0000;
        T1CONbits.TCKPS = 0b11;//256
         PR1 =31249; //2sec
        _T1IF =0;
         TMR1 = 0;
        _T1IE =0;
}  // end C`onfig_T1
void Loop_Delay (void){
    T1CONbits.TON = 1;
    while (!_T1IF);
	T1CONbits.TON = 0;
	_T1IF=0;
	TMR1=0;
// Place your code here
}
int main(void) {
    int Red [8]   = {0x1F80,0x8DC0,0x2F80,0x4DC0,0x4F80,0x2DC0,0x8F80,0x1DC0};
    int Green [8] = {0x1F40,0x8BC0,0x2F40,0x4BC0,0x4F40,0x2BC0,0x8F40,0x1BC0};
    int Blue [8]  = {0x1EC0,0x87C0,0x2EC0,0x47C0,0x4EC0,0x27C0,0x8EC0,0x17C0};
    int all_Blue = 0xF6C0;
    int all_Red = 0xFD80;
    int all_green = 0xFB40;
	Config_IO();    // Input Output
    Config_T1();
    int i=0;
  //  int j=7;
    while(1){
      // j=7;
    for(i=0;i<8;i++){
   // PORTB=0x0000;
    //PORTB |= Red[i] ;
    Loop_Delay();
    PORTB=0x0000;
    PORTB |=all_green;
    //PORTB |= (Red[i] & Green[j] );
   // Loop_Delay();
    //j=j-1;
//    PORTB=0x0000;
   //PORTB |= Blue[i] ;
//    Loop_Delay();
        } 
    
    }
    return 0;}
