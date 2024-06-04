
#include <avr/io.h>

void iniciar_puertos(){
    MCUCR |= (1 << PUD);
    DDRB = (1 << PINB1)|(1 << PINB2); //OC1A OC1B (PWM motor 1(OC1A) y motor 2(OC1B))
    DDRC = (1 << PINC0)|(1 << PINC1)|(1 << PINC2)|(1 << PINC3); //Control de motores
    DDRD = 0x00; //Sensores
}

