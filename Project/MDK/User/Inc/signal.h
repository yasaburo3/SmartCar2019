/********************************************************************************
 *
 * @file      signal.h
 * @brief     header file for signal.c
 * @author    SJX
 * @date      2018-04-08
 *
 ********************************************************************************/

#ifndef SIGNAL_H_
#define SIGNAL_H_

/********************************************************************************
 * Includes
 ********************************************************************************/
#include <stdint.h>

extern uint16_t sensor[8];
extern uint16_t back_sensor[3];
extern int back_sensor_sum;
extern uint16_t sensor_sum;
extern int sensor_diff31;
extern int sensor_diff13;
extern int sensor_diff40;
extern int sensor_sum13;
extern int past_sensor_diff13;
extern int diff_sensor_diff13;
extern uint16_t dist;
extern uint16_t sensor4[20];
extern int16_t sensor4_count;
extern uint16_t sensor4_sum;
extern uint16_t sensor_max[6];
extern float er;
extern float po_er;
extern int32_t row;
extern volatile double PJ;
extern volatile double a;
extern uint16_t sensor13;
extern float sensor_standard[8];
extern int sensor_ave_024;
extern int sensor_ave_02;
extern int sensor_ave_24;
extern int sensor_total_sum;

extern uint16_t sensor_dist;

extern int situation;
extern int code[6];
/********************************************************************************
 * Global functions
 ********************************************************************************/
void Get_Sensor_Value(uint16_t* sensor);
void Sensor_Data_Init(void);
void signal_filter(void);
void row_filter(void);
void get_row(void); 
void huandao(void);
void GetDistance(void);
#endif /* SIGNAL_H_ */
