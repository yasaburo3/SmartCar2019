/********************************************************************************
 *
 * @file      init.h
 * @brief     header file for init.c
 * @author    SJX
 * @date      2018-04-08
 *
 ********************************************************************************/

#ifndef INIT_H_
#define INIT_H_

/********************************************************************************
 * Includes
 ********************************************************************************/
#include <stdint.h>
/********************************************************************************
 * Global functions
 ********************************************************************************/
void LED_Init(void);
void Sensor_Init(void);
void Motor_Init(void);
void Steer_Init(uint16_t frequence,uint16_t duty);
void encoderFtmInit(void);
void Echo_Init(void);
void Beep_Init(void);
void Coding_Init(void);
void Encoder_Init(void);
void ghg_Init(void);
uint16_t read_speed(void);
#endif /* INIT_H_ */
