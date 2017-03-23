#include"EE3310_config.h"
#include<p24FJ64GA102.h>
#include "xc.h"
#include<math.h>
#define SW3 _RA3
enum  { ON = 1 , OFF =0 };
enum Direction { ascending = 2, descending =-2 };
enum Direction Dir_Led = ascending;
int start=0;
int temp=0;
int now  =-1;
int prev =-1;
int power;
void config_PORTS(){
   AD1PCFG=0xFFFF;
   TRISA = 0b01000; //Setting _RA3 as an input
   TRISB = 0x0000; // Setting PortB as Output 
   PORTA = 0b00000;
   PORTB = 0x0000; // Output Zero on all bits
   _CN29PUE = 1;
   }//end of config_PORTS 
void config_Timer(){
        T1CON=0x0010;//0b 0000 0000 0001 0000
        PR1 =30636.27451 ;//31249;//30636.27451 ; //1/16 sec
        _T1IP =4;
        _T1IF =0;
        _T1IE =1; // if you are going to only use the flag then do not enable the interrupt but 
                  // since we're using it here then enable it
        }
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void){
        T1CONbits.TON=0;
        TMR1=0;
        if(now <=7 ) now++;
        else now=0;
        _T1IF=0;       
           }
void config_CN(){
        _CNIP=6; //higher priority than the timer
        _CNIF=0;
        _CNIE=1;
        _CN29IE=1;
            }
void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void){
        if( SW3 == OFF ){
              T1CONbits.TON=0; // stop the timer
              PORTB &= 0;      // clear the port
              while(SW3==OFF); //wait till it is depressed 
                  if(start == 0){ // if it was going ascending 
			              Dir_Led=descending; // change the direction
			              temp=start=14; // change the start point(bit/ _RB) and the iterating variable 
			              power = (int) pow(2,temp); 
		                  PORTB |= power; // set the new start point (lines 50 & 51 can be removed and wont affect)
                                }//end if
	              else if(start==14){
                          Dir_Led=ascending;
			              temp=start=0;
                          power = (int) pow(2,temp);
		                  PORTB |= power; // set the new start point (lines 56 & 57 can be removed and wont affect)
                                    }//end else if
              T1CONbits.TON=1;// restart the timer again
                        }//end big if       
        _CNIF=0;//clear the flag
}//end of CNInterrupt

int main(void) {
    // Configure 
    config_PORTS();
    config_Timer();
    config_CN();
 while(1)
 { 
    for(temp=start;temp<=14 && temp>=0;temp=temp+Dir_Led ){
         if(prev == -1 && now==-1) T1CONbits.TON=1; // For the first time ever start the timer here 
         while( prev == now ); // if the state is not changed then the 1/16sec have not passed then wait 
         prev=now; // update the previous value
         PORTB &= 0; // clear
         power = (int) pow(2,temp);
         PORTB |= power; //set
         T1CONbits.TON=1; //start the timer again
                                                     }//End of For
    } // end of while loop
    return 0;
}

/* NOTES: 
 * 1) It work also without lines (50&51) & (57&58)
 * 2) I choose the start as bit _RB0 and the end as _RB14 
 */