    #include "PIDController.h"

    void PIDController_init(PIDController_t *pid, float kp, float ki, float kd)
    {
        pid->integral = 0.0f;
        pid->output = 0.0f;

        pid->kp = kp;
        pid->ki = ki;
        pid->kd = kd;
    }

    float PIDController(PIDController_t *pid, float input, float setPoint)
    {
        pid->e = setPoint - input;

        pid->integral = pid->e * pid->kp + pid->integral;

        
    }