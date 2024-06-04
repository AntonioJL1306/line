/*
 * PID.c
 *
 * Created: 04/06/2024 02:00:39 p. m.
 *  Author: tonoc
 */ 
#include "PID.h"

static int kp, ki, kd;
static int previous_error = 0;
static int integral = 0;

void pid_init(int p, int i, int d) {
	kp = p;
	ki = i;
	kd = d;
}

int pid_calculate(int setpoint, int measured_value) {
	int error = setpoint - measured_value;
	integral += error;
	int derivative = error - previous_error;
	previous_error = error;

	return kp * error + ki * integral + kd * derivative;
}