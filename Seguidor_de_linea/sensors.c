/*
 * sensors.c
 *
 * Created: 04/06/2024 01:56:53 p. m.
 *  Author: tonoc
 */ 
#include "sensors.h"
#define NUM_SENSORS 6

void sensors_init() {
	// Configurar ADC
	ADMUX = (1 << REFS0); // Referencia AVcc
	ADCSRA = (1 << ADEN) | (1 << ADPS2); // Habilitar ADC, Prescaler 16
}

void start_adc_conversion(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Seleccionar canal
	ADCSRA |= (1 << ADSC); // Iniciar conversión
}

uint16_t get_adc_result() {
	while (ADCSRA & (1 << ADSC)); // Esperar a que termine la conversión
	return ADC;
}

uint16_t* read_all_sensors() {
	static uint16_t sensor_values[NUM_SENSORS];
	for (uint8_t i = 0; i < NUM_SENSORS; i++) {
		start_adc_conversion(i);
		sensor_values[i] = get_adc_result();
	}
	return sensor_values;
}