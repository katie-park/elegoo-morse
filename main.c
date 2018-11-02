
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

struct _morse{
    char letter;
    char bits;
    char out;
}

struct _morse table[] = {
    {'A',0b01},
    {'B',0b0001},
    {'C',0b1010},
    {'D',0b100},
    {'E',0b0},
    {'F',0b0010},
    {'G',0b110},
    {'H',0b0000},
    {'I',0b00},
    {'J',0b0111},
    {'K',0b101},
    {'L',0b0100},
    {'M',0b11},
    {'N',0b10},
    {'O',0b111},
    {'P',0b0110},
    {'Q',0b1101},
    {'R',0b010},
    {'S',0b000},
    {'T',0b1},
    {'U',0b001},
    {'V',0b0001},
    {'W',0b011},
    {'X',0b1001},
    {'Y',0b1011},
    {'Z',0b1100},
    {'0',0b11111},
    {'1',0b0111},
    {'2',0b00111},
    {'3',0b00011},
    {'4',0b00001},
    {'5',0b00000},
    {'6',0b10000},
    {'7',0b11000},
    {'8',0b11100},
    {'9',0b11110},
};

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
