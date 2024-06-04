/*
 * sensors.h
 *
 * Created: 04/06/2024 01:55:38 p. m.
 *  Author: tonoc
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_
#include <avr/io.h>
void sensors_init();
uint16_t read_sensor(uint8_t channel);
void start_adc_conversion(uint8_t channel);
uint16_t get_adc_result();
uint16_t* read_all_sensors();

#endif /* SENSORS_H_ */