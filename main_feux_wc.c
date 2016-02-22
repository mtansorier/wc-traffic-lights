/* 
 * File:   .c
 * Author: Mickaël Tansorier
 * e-mail: mickatans@orange.fr
 *
 * Created on 9 mars 2015, 18:44
 * 
 * License CC-BY-NC-SA
 * https://creativecommons.org/licenses/by-nc-sa/3.0/fr/
 */

/* CONFIGURATION */
#pragma config CP = ON           // Flash Program Memory Code Protection bit
#pragma config CCPMX = RB3       // CCP1 Pin Selection bit
#pragma config DEBUG = OFF       // In-Circuit Debugger Mode bit 
#pragma config WRT = OFF         // Flash Program Memory Write Enable bits
#pragma config CPD = ON          // Data EE Memory Code Protection bit 
#pragma config LVP = OFF         // Low-Voltage Programming Enable bit
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (desactiver si fonctionne en 3V)
#pragma config MCLRE = OFF       // RA5/MCLR/VPP Pin Function Select bit 
#pragma config PWRTE = ON        // Power-up Timer Enable bit (choix reset inten))
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
#pragma config FOSC = INTOSCIO

#include <pic16f87.h>
#include <xc.h>
#include <htc.h>

#define _XTAL_FREQ 8000000 //set your internal(or)external oscillator speed


/* Alias */
#define RED    PORTAbits.RA0
#define ORANGE PORTAbits.RA1
#define GREEN  PORTAbits.RA2

#define BUTTON_ON   PORTBbits.RB1
#define BUTTON_OFF  PORTBbits.RB2
#define BUTTON_CACA PORTBbits.RB3


/*FONCTIONS*/
void init_oscillator(void);

/*
 * MAIN
 */
int main(void) {
    
    /* init frequency */
    init_oscillator();
    
    /* declaration ports */
    TRISA=0x00; // portA output
    TRISB=0xFF; // portB input
    
    /* set ports */
    PORTA=0x00;
    PORTB=0x00;

    /* tempo */
    int nb_sec=0;
    
    while(1) //infinite loop
    {
        // set when you enter
        if(BUTTON_ON==0){
            __delay_ms(10);
            if(BUTTON_ON==0){
                RED = 0; ORANGE = 1; GREEN = 0;
                for(nb_sec=5;nb_sec>0;nb_sec--)
                    __delay_ms(1000);
                RED = 1; ORANGE = 0; GREEN = 0;
            }
        }
        // set when you exit
        if(BUTTON_OFF==0){
            __delay_ms(10);
            if(BUTTON_OFF==0){
                RED = 0; ORANGE = 1; GREEN = 0;
                for(nb_sec=5;nb_sec>0;nb_sec--)
                    __delay_ms(1000);
                RED = 0; ORANGE = 0; GREEN = 1;
            }
        }
        // set to warning
        if(BUTTON_CACA==0){
            __delay_ms(10);
            if(BUTTON_CACA==0){
                RED = 0; ORANGE = 1; GREEN = 0;
                for(nb_sec=60;nb_sec>0;nb_sec--)
                    __delay_ms(1000);
                RED = 0; ORANGE = 0; GREEN = 1;
            }
        }

    }
    return 0;
}

/*
 * Init frenquency
 */
void init_oscillator(void){
    OSCCONbits.IRCF = 0b111; //8MHz
    OSCCONbits.SCS = 0b00;   //Oscillator mode defined by FOSC
    OSCCONbits.IOFS = 1;     //Frequency is stable
}

