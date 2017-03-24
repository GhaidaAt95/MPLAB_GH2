/*
 * File:   AsyncDemo.c
 * Author: sgibbs
 *
 * Created on February 25, 2016, 5:28 PM
 * Modified on October 18, 2016
 */

#include "RS232_Config.h"
#include <stdio.h>
#include <stdlib.h>
#include <p24FJ64GA102.h>

/*
 * Perform UART operation using the PIC24FJ64GA102
 */

// timing and baud rate calculations

#define BRGVAL   ___       // 19200 baud (BRGH=0)
#define CTS      _RB12
#define RTS      _RB10

void config_UART2(void){
    //unlock registers
    __builtin_write_OSCCONL(OSCCON & 0xBF);

    //Configure Input Functions (Table 10-2)
    ___________ = 14; // Set RX to RP14
    // Assign U2CTS To Pin RP12
    ___________ = 12;
    
    // Configure Output Functions (Table 10-3)
    ___________ = 5; // Set TX to RP11
    // Assign U2RTS To Pin RP10
    ___________ = 6;

    //lock registers
    __builtin_write_OSCCONL(OSCCON | 0x40);

} // end config_UART2

// initialize the UART2 serial port
void init_UART2( void)
{
    U2MODE = 0b___________________;
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

    U2STA  = 0b___________________;
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

    _U2RXIF = 0;    // 
    _U2TXIF = 0;    // 

    U2MODEbits.UARTEN = 1;  // 
    U2STAbits.UTXEN = 1;    // 
} // initU2

// function to send a character to the UART1 serial port
int putU2(int c)
{
    while (CTS); // 
    while (U2STAbits.UTXBF); // 
    U2TXREG = c;    // 
    _U2RXIF = 0; // 
    return c;
} // end putU2

  // function to receive a character from the UART1 serial port
 char getU2(void)
{
     RTS = 0;                   // 
     while (!U2STAbits.URXDA);  // wait for ________________________
     RTS = 1;   
     return U2RXREG;  // Return the (processed) Character
} // end getU2

int main (void) {

    int c;

    AD1PCFG = 0x______;
    TRISB = 0x______;
        // TRIS bits must be defined for PPS.
        // RXD (RB13) is an input.
        // CTS (RB12) is an ______.
        // TXD (RB11) is an ______.
        // RTS (RB10) is an ______.
    LATB = 0x______;
 

    config_UART2( );
    init_UART2();

    putU2('>');

    while (1) {
        //  Retrieve a character from the terminal
        c = getU2();

        // Process the character -   Create and insert your code here.

        // Return the (processed) Character
        putU2(c);

    } // end while

} // end main
