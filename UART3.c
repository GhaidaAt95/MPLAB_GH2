#include "EE3310_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <p24FJ64GA102.h>
#include "xc.h"

// timing and baud rate calculations
#define BRGVAL    12       // 19200 baud (BRGH=0)
#define CTS      _RB12
#define RTS      _RB10
void config_UART2(void){
    //unlock registers
    __builtin_write_OSCCONL(OSCCON & 0xBF);

    //Configure Input Functions (Table 10-2)
   RPINR19bits.U2RXR = 14; // Set RX to RP14
    // Assign U2CTS To Pin RP12
   RPINR19bits.U2CTSR = 12;
    
    // Configure Output Functions (Table 10-3)
   RPOR5bits.RP11R= 5; // Set TX to RP11
   
    // Assign U2RTS To Pin RP10
   RPOR5bits.RP10R= 6;

    //lock registers
    __builtin_write_OSCCONL(OSCCON | 0x40);

} // end config_UART2
// initialize the UART2 serial port
void init_UART2( void)
{
    U2MODE = 0x0000;//0b0000000000000000;
 /*           0b0xxxxxxxxxxxxxxx; U2MODEbits.UARTEN = 0;  // Bit15 TX, RX DISABLED, ENABLE at end of func
             0b0xxxxxxxxxxxxxxx;                         // Bit14 N/A Ignore
             0bxx0xxxxxxxxxxxxx; U2MODEbits.USIDL = 0;   // Bit13 Continue in Idle
             0bxxx0xxxxxxxxxxxx; U2MODEbits.IREN = 0;    // Bit12 No IR translation
             0bxxxx0xxxxxxxxxxx; U2MODEbits.RTSMD = 0;   // Bit11 Flow Control Mode
             0bxxxxxxxxxxxxxxxx;                         // Bit10 N/A        
             0bxxxxxx00xxxxxxxx; U2MODEbits.UEN = 0;     // Bits8,9 TX,RX enabled, CTS,RTS not
             0bxxxxxxxx0xxxxxxx; U2MODEbits.WAKE = 0;    // Bit7 No Wake up (since we don't sleep here)
             0bxxxxxxxxx0xxxxxx; U2MODEbits.LPBACK = 0;  // Bit6 No Loop Back
             0bxxxxxxxxxx0xxxxx; U2MODEbits.ABAUD = 0;   // Bit5 No Autobaud (would require sending '55')
             0bxxxxxxxxxxx0xxxx; U2MODEbits.URXINV = 0;  // Bit4 IdleState = 1  (for dsPIC)
             0bxxxxxxxxxxxx0xxx; U2MODEbits.BRGH = 1;    // Bit3 16 clocks per bit period
             0bxxxxxxxxxxxxx00x; U2MODEbits.PDSEL = 0;   // Bits1,2 8bit, No Parity
             0bxxxxxxxxxxxxxxx0; U2MODEbits.STSEL = 0;   // Bit0 One Stop Bit
*/
    U2BRG = BRGVAL;         // Baud Rate setting for 19200

    U2STA  = 0x0000;
            //0b___________________;
 /*          0b0xxxxxxxxxxxxxxx; U2STAbits.UTXISEL1 = 0; //Bit15 Int when Char is transferred (1/2 config!)
             0bxxxxxxxxxxxxxxxx; U2STAbits.UTXINV = 0;   //Bit14 N/A, IRDA config
             0bxx0xxxxxxxxxxxxx; U2STAbits.UTXISEL0 = 0; //Bit13 Other half of Bit15
             0bxxx0xxxxxxxxxxxx;                         //Bit12 Not Implemented in PIC24FJ64GA102
             0bxxxx0xxxxxxxxxxx; U2STAbits.UTXBRK = 0;   //Bit11 Disabled
             0bxxxxx0xxxxxxxxxx; U2STAbits.UTXEN = 0;    //Bit10 TX pins controlled by peripheral
             0bxxxxxx0xxxxxxxxx; U2STAbits.UTXBF = 0;    //Bit9 *Read Only Bit*
             0bxxxxxxx0xxxxxxxx; U2STAbits.TRMT = 0;     //Bit8 *Read Only bit*
             0bxxxxxxxx00xxxxxx; U2STAbits.URXISEL = 0;  //Bits7,6 Interrupt on character received
             0bxxxxxxxxxx0xxxxx; U2STAbits.ADDEN = 0;    //Bit5 Address Detect Disabled
             0bxxxxxxxxxxx0xxxx; U2STAbits.RIDLE = 0;    //Bit4 *Read Only Bit*
             0bxxxxxxxxxxxx0xxx; U2STAbits.PERR = 0;     //Bit3 *Read Only Bit*
             0bxxxxxxxxxxxxx0xx; U2STAbits.FERR = 0;     //Bit2 *Read Only Bit*
             0bxxxxxxxxxxxxxx0x; U2STAbits.OERR = 0;     //Bit1 *Read Only Bit*
             0bxxxxxxxxxxxxxxx0; U2STAbits.URXDA = 0;    //Bit0 *Read Only Bit*
*/
    _U2RXIF = 0;    //  IFS1bits.U2RXIF , UART2 Receiver Interrupt Flag Status bit
    _U2TXIF = 0;    //  IFS1bits.U2tXIF , UART2 Transmitter Interrupt Flag Status bit
    U2MODEbits.UARTEN = 1;  // Enable UART2 , enable this bit before enabling the UTXEN bit in the status register
    U2STAbits.UTXEN = 1;    // Transmit bit enabled, UxTX pin is controlled by  UARTx
} // initU2

// function to send a character to the UART1 serial port
int putU2(int c)
{
    while (CTS); // wait till RTS of the serial monitor tells CTS of pic that the serial monitor is ready to receive 
    while (U2STAbits.UTXBF); // Transmit Buffer full status bit (READ-ONLY) (1) Transmit buffer is full (0) Not full, at least one or more char 
    U2TXREG = c;    // Write data byte to the lower byte of the UxTXREG word.
    _U2RXIF = 0; //  clear the UART2 receiver interrupt flag 
    return c;
} // end putU2
int checkCHAR (int c){ 
    if(c <=0x5A && c>=0x41){
        c =c+ 0x20;
    }
    else { if (c <=0x7A && c>=0x61){
             c = c - 32;} }
   
    /*
     * Capital between 0x41 and 0x5A
       Small   between 0x61 and 0x7A
     */
    return (c);
}
  // function to receive a character from the UART1 serial port
 int getU2(void)
{
     RTS = 0;                   // Tell the CTS of the monitor that the pic is ready to receive
     while (!U2STAbits.URXDA);  // wait for Receive Buffer Data Available bit 
                                //(1) Receive buffer has data, at least one more character can be read
                                //(0) Receive buffer is empty
     RTS = 1;                   // Tell the CTS of the monitor that the pic is not ready to receive 
     return U2RXREG;  // Return the (processed) Character
} // end getU2

int main (void) {

    int c;
    int i=0;
     char array[30] ;
    
    
    AD1PCFG = 0x1FFF;    // for the pins we'll use for UART they MUST be DIGITAL
    TRISB = 0x5000;      //   [15 14 13 12] [11 10 9 8] [7 6 5 4] [3 2 1 0] 
                         //0b  0  1  0  1    0  0  0 0   0 0 0 0   0 0 0 0  // set pins 14 and 12 as INPUTS  
        // TRIS bits must be defined for PPS.
        // RXD (RB14) is an input.
        // CTS (RB12) is an input.
        // TXD (RB11) is an output.
        // RTS (RB10) is an output.
    LATB = 0x0000;
    config_UART2( );
    init_UART2();
    while (1) {
        
        do{
        c = getU2();
        if(c != 10){
        array[i]=c;
        putU2(c);
        i++;
        }
        else {
            break;
        }
        }while(i<(30-1));
        array[i+1]=NULL;
        putU2('\n');
        while(i>=0){
            putU2(array[i]);
                       array[i]=NULL;
                       i--;
        }
        putU2('\n');
         i=0;
         c=NULL;
    } // end while

} // end main
