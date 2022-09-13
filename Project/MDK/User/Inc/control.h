/********************************************************************************
 *
 * @file      control.h
 * @brief     header file for control.c
 * @author    SJX
 * @date      2018-04-09
 *
 ********************************************************************************/

#ifndef CONTROL_H_
#define CONTROL_H_

/********************************************************************************
 * Includes
 ********************************************************************************/
#include <stdint.h>

/********************************************************************************
 * Macros
 ********************************************************************************/
/************************************************************
 * Motors
 ************************************************************/
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define SERVO_MIDDLE	850
#define SERVO_LEFT		SERVO_MIDDLE - 72
#define SERVO_RIGHT		SERVO_MIDDLE + 72

#define ZuoXiaoHuan 0
#define YouXiaoHuan 1
#define YouDaHuan 2
#define ZuoDaHuan 3

extern uint16_t servoDuty;
/********************************************************************************
 * Global functions
 ********************************************************************************/
void Motor_ChangeSpeed(int16_t duty, uint8_t motor);
void Steer_Change(int16_t duty);
void Servo_Control1(void);
void Servo_Control2(void);
void Servo_Control3(void);
void Servo_Control4(void);

int getSpeed(void);
int16_t speed_IIR_filter(int16_t speed);
void getcarspeedset(void);
void speed_control(void);
void speed_control_output(void);
void Motor_Output(double duty_speed_adjust);
float PID_Control(float piancha, float po_piancha);
float Dir_Control(float dir_err, float po_dir_err);
void DirectionControl(void);
void Direction_loop(void);
extern int32_t speed;
extern double duty_speed_adjust;
extern int16_t speed_set;
extern int16_t duty_real;
extern int loop;
extern int loop_type;
extern int spdL;
extern int spdR;
extern float po_devi_loop;
extern int flag_protect;

extern float error;
extern int block_up;

#endif /* CONTROL_H_ */
