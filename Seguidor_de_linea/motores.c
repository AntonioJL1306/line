
#include <avr/io.h>

void iniciar_motores(){

    TCNT1 = 0;
    TIMSK1 = 0x00;

    TCCR1A = (1 << WGM11)|(1 << COM1A0)|(1 << COM1A1)|(1 << COM1B1)|(1 << COM1B0);	    
    TCCR1B = (1 << WGM12)|(1 << WGM13);					    
    TCCR1B |= (1 << CS10)|(1 << CS11);						
    
    ICR1 = 2499;

    OCR1A, OCR1B = ICR1/2; // Velocidad inicial

}

void mover_motores(uint16_t vel_izquierda, uint16_t vel_derecha){
    PORTC |= (1 << PINC0)|(1 << PINC2);
    PORTC &= ~((1 << PINC1)|(1 << PINC3));
    if(vel_izquierda >= 2400){
	OCR1A = 2400;
    }
    else if(vel_derecha >= 2400){
	OCR1B = 2400;
    }
    else if(vel_izquierda <= 200){
	OCR1A = 200;
    }
    else if(vel_derecha <= 200){
	OCR1B = 200;
    }
    else {
	OCR1A = vel_izquierda;
	OCR1B = vel_derecha;
    }
}

void detener(){
    PORTC &= ~((1 << PINC0)|(1 << PINC1)|(1 << PINC2)|(1 << PINC3));
}
