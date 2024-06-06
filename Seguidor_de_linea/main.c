/*
 * Seguidor_de_linea.c
 *
 * Created: 29/05/2024 03:29:34 p. m.
 * Author : tonoc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sensors.h"
#include "PID.h"

#define MOTOR_LEFT_PWM PIND6
#define MOTOR_RIGHT_PWM PIND5
#define MOTOR_LEFT_IN1 PIND2
#define MOTOR_LEFT_IN2 PIND3
#define MOTOR_RIGHT_IN3 PIND4
#define MOTOR_RIGHT_IN4 PIND7

void setup() {
	// Configurar pines de PWM como salida
	DDRD |= (1 << MOTOR_LEFT_PWM) | (1 << MOTOR_RIGHT_PWM);
	// Configurar pines de dirección como salida
	DDRD |= (1 << MOTOR_LEFT_IN1) | (1 << MOTOR_LEFT_IN2) | (1 << MOTOR_RIGHT_IN3) | (1 << MOTOR_RIGHT_IN4);

	// Configurar Timer0 para PWM, modo Fast PWM, prescaler 64
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1);
	TCCR0B = (1 << CS01) | (1 << CS00);
	sensors_init();
	pid_init(2.5, 0.05, 3); // Valores ajustados para mayor velocidad y estabilidad
	sei();
}

void setMotorSpeed(int16_t leftSpeed, int16_t rightSpeed) {
	if (leftSpeed > 0) {
		PORTD |= (1 << MOTOR_LEFT_IN1);
		PORTD &= ~(1 << MOTOR_LEFT_IN2);
		} else {
		PORTD &= ~(1 << MOTOR_LEFT_IN1);
		PORTD |= (1 << MOTOR_LEFT_IN2);
		leftSpeed = -leftSpeed;
	}
	if (rightSpeed > 0) {
		PORTD |= (1 << MOTOR_RIGHT_IN3);
		PORTD &= ~(1 << MOTOR_RIGHT_IN4);
		} else {
		PORTD &= ~(1 << MOTOR_RIGHT_IN3);
		PORTD |= (1 << MOTOR_RIGHT_IN4);
		rightSpeed = -rightSpeed;
	}

	OCR0A = (leftSpeed > 255) ? 255 : (leftSpeed < 0) ? 0 : leftSpeed;
	OCR0B = (rightSpeed > 255) ? 255 : (rightSpeed < 0) ? 0 : rightSpeed;
}

int main(void) {
	setup();
	while (1) {
		uint16_t* sensor_values = read_all_sensors();

		// Asumiendo que los valores del sensor se mapean a un error
		int error = (sensor_values[0] * -3 + sensor_values[1] * -2 +
		sensor_values[2] * -1 + sensor_values[3] * 1 +
		sensor_values[4] * 2 + sensor_values[5] * 3);

		// Calcular la corrección PID
		int correction = pid_calculate(0, error);

		// Ajustar la velocidad de los motores
		int16_t baseSpeed = 100; // Incremento del valor base para mayor velocidad
		int16_t leftSpeed = baseSpeed - correction;
		int16_t rightSpeed = baseSpeed + correction;

		setMotorSpeed(leftSpeed, rightSpeed);
	}
	return 0;
}
