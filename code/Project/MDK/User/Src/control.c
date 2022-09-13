/********************************************************************************
 *
 * @file      control.c
 * @brief     control motor(s) and servo
 * @author    SJX
 * @date      2018-04-09
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "control.h"
#include "ftm.h"
#include "signal.h"
#include "main.h"

//环外巡线变量
float devi ;           
float error;
float po_error;	
float p = 6500;
float i = 0;
float d = 250000;

//环内巡线变量
float devi_loop  = 0; 
float po_devi_loop = 0;
float error_loop = 0;
float po_error_loop = 0;	
float p_loop = 6000;
float i_loop = 0;
float d_loop = 400000 ;
int flag_protect = 0;



//extern float er_loop = 0;
//extern float po_er_loop = 0;
//extern float devi_loop = 0;
/********************************************************************************
*电机控制函数
 ********************************************************************************/
void Motor_ChangeSpeed(int16_t duty, uint8_t motor) 
{
uint8_t dir = duty > 0 ? 1 : 0;
  if (motor == LEFT_MOTOR) 
		{
			if (dir == 1) 
				{
					FTM_PWM_Duty(CFTM2, FTM_CH3, 0); 
					FTM_PWM_Duty(CFTM2, FTM_CH2, duty); 

				} 
			else 
				{
					FTM_PWM_Duty(CFTM2, FTM_CH3, -duty); 
					FTM_PWM_Duty(CFTM2, FTM_CH2, 0);
				}
		} 
	else  
	  {
			if (dir == 1) 	
				{
					FTM_PWM_Duty(CFTM2, FTM_CH1, duty); 
					FTM_PWM_Duty(CFTM2, FTM_CH0, 0); 
				} 
			else 
				{
					FTM_PWM_Duty(CFTM2, FTM_CH1, 0); 
					FTM_PWM_Duty(CFTM2, FTM_CH0, -duty);
				}
		}
}


/********************************************************************************
*环外巡线控制
 *********************************************************************************/

//PID控制函数
float PID_Control(float piancha, float po_piancha){
    devi = p * piancha + d * (piancha - po_piancha);
    if(devi > 9000){
        devi = 9000;
    }
    else if(devi < -9000){
        devi = -9000;
    }
    return devi;
}

void DirectionControl(){

	error = (float)(sensor[0] - sensor[4]) / (sensor[0] + sensor[4]);// + 0.05 + 0.035 - 0.1;
    devi = PID_Control(error, po_error);
    
    left_speed = spdL - devi;
    right_speed = spdR + devi;
	po_error = error;

}

/********************************************************************************
*环内巡线控制
 *********************************************************************************/

float PID_loop(float piancha_loop, float po_piancha_loop){
   
	
	//继承一帧电机控制量
	if(flag_protect == 0){
		devi_loop = po_devi_loop;
		flag_protect = 1;
	}
	else if(flag_protect == 1){
		 devi_loop = p_loop * piancha_loop + d_loop * (piancha_loop - po_piancha_loop);
	}
	
	
	//电机控制量增量限幅
//	if(devi_loop - po_devi_loop > 3000){
//        devi_loop = 3000 + po_devi_loop;
//    }
//    else if(devi_loop - po_devi_loop < -3000){
//        devi_loop = -3000 + po_devi_loop;
//    }
//	po_devi_loop = devi_loop;
	
	
    if(devi_loop > 11000){
        devi_loop = 11000;
    }
    else if(devi_loop < -11000){
        devi_loop = -11000  ;
    }
	
    po_devi_loop = devi_loop;

    return devi_loop;
	
}

void Direction_loop(){

//	error_loop = (float)(sensor[0]*4 - sensor[4]*0.1) / (sensor[0]*4 + sensor[4]*0.1);
	error_loop = (float)(sensor[0]*2 - sensor[4]) / (sensor[0]*2 + sensor[4]);
	devi_loop = PID_loop(error_loop, po_error_loop);
	
	left_speed = spdL_loop - devi_loop;
	right_speed = spdR_loop + devi_loop;
	po_error_loop = error_loop;
}

/*陀螺仪控制函数*/
//float Dir_Control(float dir_err, float po_dir_err){
//    float kp = 20;
//    float ki = 0;
//    float kd = 0;
//    float dir_devi = kp * dir_err + kd * (dir_err - po_dir_err);
//    if(dir_devi > 900){
//        dir_devi = 900;
//    }
//    else if(dir_devi < -900){
//        dir_devi = -900;
//    }
//    
//    return dir_devi;
//}


