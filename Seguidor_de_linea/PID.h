/*
 * PID.h
 *
 * Created: 04/06/2024 02:00:02 p. m.
 *  Author: tonoc
 */ 


#ifndef PID_H_
#define PID_H_
void pid_init(int p, int i, int d);
int pid_calculate(int setpoint, int measured_value);

#endif /* PID_H_ */