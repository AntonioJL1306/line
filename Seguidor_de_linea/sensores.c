
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motores.h"

void iniciar_sensores(){
    TIMSK0 |= (1 << TOIE0);
    TCCR0B |= (1 << CS02)|(1 << CS00);
    TCNT0 = 0;
}

uint8_t leer_sensores(){
    uint8_t valores = PIND;
    return valores;
}

void actualizar(){
    uint8_t valores = PIND;
    if(bit_is_set(valores, PD7)){
	mover_motores(800, 2200);
    }
    else if(bit_is_set(valores, PD0)){
	mover_motores(2200, 800);
    }
    else{
	mover_motores(2000, 2000);
    }
}

ISR(TIMER0_OVF_vect){
    actualizar();
}

