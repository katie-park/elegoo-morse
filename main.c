
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <ctype.h>
#include <util/delay.h>
#include "serial.h"

#define LED 0x20

#define TU 50

char message[100];
int read(char *message);

int dot(void){
    PORTB |= LED;
    _delay_ms(TU);
    PORTB &= ~LED;
    return 0;
}

int dash(void){
    PORTB |= LED;
    _delay_ms(TU*3);
    PORTB &= ~LED;
    return 0;
}

int cspace(void){
    _delay_ms(TU);
    return 0;
}

int lspace(void){
    _delay_ms(TU*3);
    return 0;
}

int wspace(void){
    _delay_ms(TU*7);
    return 0;
}

int translate(char character){
    switch(character){
        case 'A':
            dot();
            cspace();
            dash();
            break;
        case 'B':
            dash();
            cspace();
            dot();
            cspace();
            dot();
            cspace();
            dot();
            break;
        case 'C':
            dash();
            cspace();
            dot();
            cspace();
            dash();
            cspace();
            dot();
            break;
        case 'D':
            dash();
            cspace();
            dot();
            cspace();
            dot();
            break;
        case 'E':
            dot();
            break;
        case 'F':
            dot();
            cspace();
            dot();
            cspace();
            dash();
            cspace();
            dot();
            break;
        case 'G':
            dash();
            cspace();
            dash();
            cspace();
            dot();
            break;
        case 'H':
            dot();
            cspace();
            dot();
            cspace();
            dot();
            cspace();
            dot();
            break;
        case 'I':
            dot();
            cspace();
            dot();
            break;
        case 'J':
            dot();
            cspace();
            dash();
            cspace();
            dash();
            cspace();
            dash();
    }
    return 0;
}

int read(char *message){
    int i;
    for(i = 0; i < strlen(message); i++){
        if(message[i] == ' ') wspace();
        else{
            translate(toupper(message[i]));
            lspace();
        }
    }
    return 0;
}
int main(void){
    DDRB = LED;
    OpenConsole();

    while(1){

        // PORTB |= LED;
        // _delay_ms(tu);
        // PORTB &= ~LED;
        // _delay_ms(tu);

        printf("Enter string to send: ");
        while ( ! getstr(message, 99));
        printf ("\r\nMorse out %s\r\n", message);
        //scanf("%s",message);

        read(message);
    }
    return 0;
}
