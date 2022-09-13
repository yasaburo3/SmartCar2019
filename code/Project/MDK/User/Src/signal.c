/********************************************************************************
 *
 * @file      signal.c
 * @brief     acquire and process sensor signals
 * @author    SJX
 * @date      2018-04-08
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "signal.h"
#include "adc.h"
#include <stdint.h>
#include "control.h"
#include "common.h"
#include "main.h"
#include "uart.h"
uint16_t sensor[8] = {0};
uint16_t sensor_dist = 0;
uint16_t sensor_val_org[8][6];
uint16_t sensor_dist_org[6] = {0};
uint16_t sensor_val_ave[8] = {0};
uint16_t sensor_dist_ave = 0;
uint16_t sensor_val_sum[8] = {0};
uint16_t sensor_dist_sum = 0;
uint16_t sensor_val_max_temp[8] = {0};
uint16_t sensor_dist_max_temp = 0;
uint16_t sensor_val_min_temp[8] = {0};
uint16_t sensor_dist_min_temp = 0;
uint16_t sensor_val_max = 0;
uint16_t sensor_dist_max = 0;
uint16_t sensor_val_min = 0;
uint16_t sensor_dist_min = 0;
uint16_t sensor_val_phl[8][4];
uint16_t sensor_dist_phl[4];
uint16_t sensor_val_top = 2100;
uint16_t sensor_val_bottom = 0;
uint16_t sensor_val_top_back = 5000;
uint16_t sensor_val_bottom_back = 0;

uint16_t back_sensor[3] = {0};
uint16_t sensor_sum = 0;
int sensor_diff31 = 0;
int sensor_diff13 = 0;
int sensor_sum13 = 0;
int past_sensor_diff13 = 0;
int diff_sensor_diff13 = 0;
int sensor_diff40 = 0;
int sensor_ave_024 = 0;
int sensor_ave_02 = 0;
int sensor_ave_24 = 0;
int sensor_diff34_01 = 0;
int back_sensor_sum = 0;
int sensor_total_sum = 0;

int block_up = 0;

int code[6] = {0};							//拨码开关
int situation = 0;

uint16_t dist = 0;
uint16_t sensor4[20]={0};
int16_t sensor4_count=19;
uint16_t sensor4_sum = 0;
uint16_t sensor13=0;
uint16_t sensor_max[6] = {0,0,0,0,0,550};

volatile int32_t row_save[100]={2500};
volatile double PJ;
volatile double a;
int32_t  row_sum;	                          
uint8_t pos_i_max;
uint16_t sensor_bound=2000;
//float po_er;
//float er;
int32_t row;
#define BUFFER_SIZE 2
#define FACTOR_SCALE 0.2


static	uint32_t ATD0DR0=0;
static	uint32_t ATD0DR1=0;
static	uint32_t ATD0DR2=0;
static	uint32_t ATD0DR3=0;
static	uint32_t ATD0DR4=0;
static	uint32_t ATD0DR5=0;
static	uint32_t ATD0DR6=0;
static	uint32_t ATD0DR7=0;
static	uint32_t ATD0DR8=0;

int32_t  ud_old = 0;
uint32_t row_save_size=99;

uint16_t sensor1[5];
//float sensor_standard[5]={10800,11260,10580,9780,8340}; //电感归一化注意先注掉归一化计算！！！！！！！！！！！！！！！！
float sensor_standard[8]={795*2,771*2,840*2,770*2,795*2,2515*2,2513*2,2845*2};
uint8_t max=0;
uint8_t i_max;
int fankui_count=0;

int sensorRawBuf[5][BUFFER_SIZE]={0};

inline int abs(int x) { return x>0? x:-x;}

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     get sensors' values
 * @param     sensor point to the values of sensors
 * @return    none
 ************************************************************/

void Sensor_Data_Init(){
	int i = 0;
	int j = 0;
		//初始化
	for(i = 0; i < 8; i++){
		for(j = 0; j < 6; j++){
			sensor_val_org[i][j] = 0;
		}
	}
	
	for(i = 0; i < 8; i++){
		for(j = 0; j < 4; j++){
			sensor_val_phl[i][j] = 0;
		}
	}
	
	
	for(i = 0; i < 6;i++){
		sensor_dist_org[i] = 0;
	}
	for(i = 0;i < 4; i++){
		sensor_dist_phl[i] = 0;
	}
	
}

void Get_Sensor_Value(uint16_t *sensor) 
{
	static int16_t i;
	static int16_t j;
	
	
	ATD0DR0=0;
	ATD0DR1=0;
	ATD0DR2=0;
	ATD0DR3=0;
	ATD0DR4=0;
    
	ATD0DR5=0;
	ATD0DR6=0;
	ATD0DR7=0;
	
	//获取六组adc数据
	for(i = 0; i < 6; i++){
		sensor_val_org[0][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD4);
		sensor_val_org[1][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD5);
		sensor_val_org[2][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD3);
		sensor_val_org[3][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD2);
		sensor_val_org[4][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD6);
		
		sensor_val_org[5][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD13);
		sensor_val_org[6][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD12);
		sensor_val_org[7][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD7);
		
//		sensor_val_org[8][i] = ADC_PollRead(ADC, ADC_CHANNEL_AD14);
		
	}
	
	//中值滤波，舍弃最大值和最小值
	for(i = 0; i < 8; i++){
		sensor_val_sum[i] = sensor_val_org[i][0];
		sensor_val_max_temp[i] = sensor_val_org[i][0];
		sensor_val_min_temp[i] = sensor_val_org[i][0];
		
		for(int j = 1; j < 6; j++){
			sensor_val_sum[i] += sensor_val_org[i][j];
			sensor_val_max_temp[i] = (sensor_val_max_temp[i] < sensor_val_org[i][j])?sensor_val_org[i][j]:sensor_val_max_temp[i];
			sensor_val_min_temp[i] = (sensor_val_min_temp[i] >sensor_val_org[i][j])?sensor_val_org[i][j]:sensor_val_min_temp[i];
		}
		
		sensor_val_sum[i] = sensor_val_sum[i] - sensor_val_max_temp[i] - sensor_val_min_temp[i];
		sensor_val_ave[i] = sensor_val_sum[i] / 4;
		sensor_val_sum[i] = 0;
	}
	
	//滑动平均滤波
	for(i = 0; i < 3; i++){
		sensor_val_phl[0][i] = sensor_val_phl[0][i + 1];
		sensor_val_phl[1][i] = sensor_val_phl[1][i + 1];
		sensor_val_phl[2][i] = sensor_val_phl[2][i + 1];
		sensor_val_phl[3][i] = sensor_val_phl[3][i + 1];
		sensor_val_phl[4][i] = sensor_val_phl[4][i + 1];
		
		sensor_val_phl[5][i] = sensor_val_phl[5][i + 1];
		sensor_val_phl[6][i] = sensor_val_phl[6][i + 1];
		sensor_val_phl[7][i] = sensor_val_phl[7][i + 1];
//		sensor_val_phl[8][i] = sensor_val_phl[8][i + 1];

	}
	
	for(i = 0;i < 8; i++){
		sensor_val_phl[i][3] = sensor_val_ave[i];
	}
	
	for(i = 0;i < 4; i++){
		sensor_val_sum[0] += sensor_val_phl[0][i];
		sensor_val_sum[1] += sensor_val_phl[1][i];
		sensor_val_sum[2] += sensor_val_phl[2][i];
		sensor_val_sum[3] += sensor_val_phl[3][i];
		sensor_val_sum[4] += sensor_val_phl[4][i];
		
		sensor_val_sum[5] += sensor_val_phl[5][i];
		sensor_val_sum[6] += sensor_val_phl[6][i];
		sensor_val_sum[7] += sensor_val_phl[7][i];
		
//		sensor_val_sum[8] += sensor_val_phl[8][i];

	}
	
	for(i = 0; i < 5; i++){
		sensor_val_ave[i] = sensor_val_sum[i] / 4;
		
		//限幅
		sensor_val_ave[i] = (sensor_val_ave[i] > sensor_standard[i])?sensor_standard[i]:sensor_val_ave[i];
		sensor_val_ave[i] = (sensor_val_ave[i] < sensor_val_bottom)?sensor_val_bottom:sensor_val_ave[i];
		
		//归一化
		sensor[i] = 1000 * (sensor_val_ave[i] - sensor_val_bottom)/(sensor_standard[i] - sensor_val_bottom);
	}
	
	for(i = 5; i < 8; i++){
		sensor_val_ave[i] = sensor_val_sum[i] / 4;
		
	//限幅
	sensor_val_ave[i] = (sensor_val_ave[i] > sensor_standard[i])?sensor_standard[i]:sensor_val_ave[i];
	sensor_val_ave[i] = (sensor_val_ave[i] < sensor_val_bottom_back)?sensor_val_bottom_back:sensor_val_ave[i];
	
	//归一化
	sensor[i] = 1000 * (sensor_val_ave[i] - sensor_val_bottom_back)/(sensor_standard[i] - sensor_val_bottom_back);
	}
	
//	sensor_dist = sensor_val_ave[8];
	
	back_sensor_sum = sensor[5] + sensor[6] + sensor[7];
	sensor_sum = sensor[0] + sensor[2] + sensor[4];
	sensor_total_sum = back_sensor_sum + sensor_sum;
//	for(i=0;i<5;i++)
//    {
//        sensor1[i]=(double)sensor[i];
//			sensor[i] = (double)(sensor[i])/(sensor_standard[i])*50000;  //归一化	！！！！！！！！！！！！！！！！
//	}
//	sensor_sum = sensor[0] + sensor[2] + sensor[4];
	sensor_diff31 = sensor[3] - sensor[1];
//	sensor_diff13 = sensor[1] - sensor[3];
//	sensor_sum13 = sensor[1] + sensor[3];
//	diff_sensor_diff13 = sensor_diff13 - past_sensor_diff13;
//	past_sensor_diff13 = sensor_diff13;
	sensor_diff40 = sensor[4] - sensor[0];
//	sensor_ave_024 = (sensor[0]+sensor[2]+sensor[4])/3;
//	sensor_ave_02 = (sensor[0]+sensor[2])/2;
//	sensor_ave_24 = (sensor[2]+sensor[4])/2;
//	sensor_diff34_01 = (sensor[3]+sensor[4]) - (sensor[0]+sensor[1]);
//	back_sensor_sum = back_sensor[0] + back_sensor[1] + back_sensor[2];
	//sensor13=(sensor[1]-sensor[3])>0? (sensor[1]-sensor[3]):(sensor[3]-sensor[1]);
}
 

void GetDistance(){
	ATD0DR8=0;
	static int16_t i;
	static int16_t j;
	for(i = 0; i < 6; i++){
		sensor_dist_org[i] = ADC_PollRead(ADC, ADC_CHANNEL_AD14);
	}
	
	sensor_dist_sum = sensor_dist_org[0];
	sensor_dist_max_temp = 0;
	sensor_dist_min_temp = 5000;
		
	for(int j = 0; j < 6; j++){
		sensor_dist_sum += sensor_dist_org[j];
		sensor_dist_max_temp = (sensor_dist_max_temp < sensor_dist_org[j])?sensor_dist_org[j]:sensor_dist_max_temp;
		sensor_dist_min_temp = (sensor_dist_min_temp >sensor_dist_org[j])?sensor_dist_org[j]:sensor_dist_min_temp;
	}
		
	sensor_dist_sum = sensor_dist_sum - sensor_dist_max_temp - sensor_dist_min_temp;
	sensor_dist_ave = sensor_dist_sum / 4;
	sensor_dist_sum = 0;
		
	for(i = 0; i < 3; i++){
		sensor_dist_phl[i] = sensor_dist_phl[i + 1];
	}
	sensor_dist_phl[3] = sensor_dist_ave;
	
	//判断增量
	if((sensor_dist_phl[3] > sensor_dist_phl[2]) && (sensor_dist_phl[2] > sensor_dist_phl[1])){
		block_up = 1;
	}
	else block_up = 0;
	
	for(i = 0;i < 4; i++){
		sensor_dist_sum += sensor_dist_phl[i];
	}
	sensor_dist_ave = sensor_dist_sum / 4;
	
	sensor_dist = sensor_dist_ave;
}

void GetCoding(int *code){
	code[5] = READ_INPUT(PTD, PTD5);
	code[4] = READ_INPUT(PTD, PTD6);
	code[3] = READ_INPUT(PTD, PTD7);
	code[2] = READ_INPUT(PTC, PTC3);
	code[1] = READ_INPUT(PTB, PTB4);
	

	if( READ_INPUT(PTC, PTC3) == 0 && READ_INPUT(PTD, PTD7) == 0 && READ_INPUT(PTD, PTD6) == 0 && READ_INPUT(PTD, PTD5) == 0){
		situation = 1;
	}
}



		 