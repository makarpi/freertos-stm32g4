/*
 * file:	PIDController.c
 * author:	makarpi
 * brief:	
 */

#ifndef _PIDCONTROLLER_H_
#define _PIDCONTROLLER_H_

typedef struct
{
    float input;
    float setPoint;
    float kp;
    float ki;
    float kd;
    float e;
    float integral;
    float limitIntegralMax;
    float limitIntegralMin;
    
    float limitOutputMax;
    float limitOutputMin;
    float output;
}PIDController_t;

#endif /* _PIDCONTROLLER_H_ */