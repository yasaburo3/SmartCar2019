#include "main.h"
#include "control.h"
#include "ftm.h"
#include "ics.h"
#include "init.h"
#include "pit.h"
#include "signal.h"
#include  "lcd.h"
#include  "common.h"
#include "KEA128_irq.h"
#include "UART.h"
#include "mpu6050.h"
#include "i2c.h"
#include "math.h"
#include  "stdio.h"
#include "gpio.h"
#include "delay.h" 

#define GYRO_Z_BIAS 140
#define ZuoXiaoHuan 0
#define YouXiaoHuan 1
#define YouDaHuan 2
#define ZuoDaHuan 3

#define normal_mode 0
#define loop_mode 1
#define block_mode 2
#define big_loop_mode 3

/*�޸���ֵ��pid������*/
 

#define use_stop_ghg

#ifdef use_stop_ghg

int stop_flag = 0;
#define stop_5ms_Delay  1*200
int stop_5ms = stop_5ms_Delay;

#endif


//��Ҫ�����Ĳ���
#define start_time 200 * 0						//�����ʱ//����ʱ��عص���ʱ��������������������������
int loop_rank[3] = {1, 1, 4};					//�ı价��˳��,1Ϊ�һ�,2Ϊ��,3Ϊ�Ҵ󻷣�4Ϊ���
int block_rank[3] = {3, 1, 2};					//�ı����ϵķ�ʽ��1Ϊ�ұ���,2Ϊ�����,3Ϊ������
//end

int spdL = 7000;								//ֱ�����ߵ�����ռ�ձ�
int spdR = 7000;
int spdL_loop = 7000;
int spdR_loop = 7000;


int road_mode = 0;


//����ʹ�õı���
int loop = 0;									//����״̬����
int counter_str = 0;		//ֱ�е��뻷��
int counter_turn = 0;
int counter_out = 0;

int loop_num = 0;
int loop_type = -1;

int loop_er = 0;
int loop_po_er = 0;
int loop_devi = 0;

int flag_loop_protect = 0;
int counter_loop_protect = 0; 

int p_temp = 2500;

int loop_out_p = 3000;
int loop_out_d = 0;

int counter_turn_to_str = 0;

int count_loop_in = 0;
int count_loop_out = 0;
int count_loop_zm = 0;
int count_loop_zxy = 0;

//������ʹ�õı���
int flag_echo_come = 0;
int echo_filter = 0;
int echo_dist_mid = 0;
int time_a = 0;
int time_b = 0;

//���ʹ�õı���
int block = -1;
int counter_block_out = 0;
int counter_block_str_out = 0;
int block_flag_counter = 0;
int block_flag = 0;
int flag_block_stop = 0;
int counter_block_back = 0;
int counter_block_stop = 0;
int counter_block_out_turn = 0;
int p_block_back = 2000;
int counter_dsy = 0;
int counter_hlj = 0;
int counter_zm = 0;
int flag_loop_echo = 0;
int counter_loop_echo = 0;
int count_lh = 0;
int block_type = 0;
int block_num = -1;
int count_direction = 0;
int devi_block = 0;
int count_back = 0;
int count_wait = 0;
int block_protect = 0;
int count_block_protect = 0;


//�Զ�����ʹ�õı���
int counter_start = 0;//������ʱ
int flag_start = 0;
int flag_start_str = 0;
int counter_start_str = 0;

//������ʹ�õı���
int exp_dir = 0;
float ang_spd = 0;          //����֮��ĵĽ��ٶȣ���/�жϣ�
float ang_sum = 0;          //���ֺ�ĽǶ� 
float ang_exp = 0;
float dir_err = 0;
float po_dir_err = 0;
float dir_devi = 0;

//���ڵ��ת��ʹ�õı���         
int left_speed = 0;
int right_speed = 0;


int count_straight = 0;//���ֱ��
int straight_flag = 0;
int counter_hjb = 0;

//����������ж�ʹ�õı���
static int echo_dist = 0;

int IsStraight(float error);

//		������
//		BEEP_ON();
//		BEEP_OFF();
		 
//		left_speed = 0;
//		right_speed = 0;

void PIT_CallBack(void){
	
    static uint32_t counter = 0;
	stop_5ms ++;
	if (stop_5ms > stop_5ms_Delay)
		stop_5ms = stop_5ms_Delay;
	
    Get_Sensor_Value(sensor);
	GetDistance();
	
	if(flag_start == 0){
        counter_start++;
    }
	if(counter_start > start_time){
        flag_start_str = 1;
        counter_start = 0;
    }
	if(flag_start_str == 1){
        counter_start_str++;
    }
	if(flag_start_str == 1&&counter_start_str > 0 && counter_start_str < 100){				//������ֱ��
        left_speed = 5000;
        right_speed = 5000;
    }
	if(counter_start_str > 100){
        flag_start_str = 0;
        counter_start_str = 0;
        flag_start = 1;
    }
	if(flag_start == 1){
	
	
		//����������500*5ms�ڲ�����ڶ����л�
	if(flag_loop_protect == 1){
		
		if(counter_loop_protect < 500){
			counter_loop_protect++;
		}
		else{
			counter_loop_protect = 0;
			flag_loop_protect = 0;
			
		}
	}
	
	//��ϱ������ں�Ͻ�����500*5ms�ڲ�������κ��
	if(block_protect == 1){
		if(count_block_protect < 420){
			count_block_protect++;
		}
		else{
			count_block_protect = 0;
			block_protect = 0;
			BEEP_ON();
		}
	}
/*-------------------------------------------------------------------------
	                          ״̬�ж�
---------------------------------------------------------------------------*/
	
	if(road_mode == normal_mode){
		DirectionControl();
		straight_flag = IsStraight(error);
		
//		if(straight_flag == 1){										//ע��,ֱ���жϺ��п���������
//			BEEP_ON();
//		}
//		else BEEP_OFF();
		
		if(back_sensor_sum > 1600 && flag_loop_protect == 0){
			road_mode = loop_mode;
			flag_loop_protect = 1;
			loop = 1;
			loop_type = loop_rank[loop_num];							//�ı价������
			BEEP_ON();
			
		}
		else if(sensor_dist > 1100 && (straight_flag == 1)&& (block_protect == 0))
		{
			block_num++;
			road_mode = block_mode;
			block = 1;
			block_type = block_rank[block_num];					//�ı��ϰ��ķ�ʽ
		}
		
//		else if(sensor_dist > 1100 && (straight_flag == 1) && ( (block_num == 0)) && (block_protect == 0)){//  && (block_up == 1) && (block_num == 0) || (block_num == 1) 
//			road_mode = block_mode;
//			block = 1;
//			block_type = block_rank[block_num];					//�ı��ϰ��ķ�ʽ
////			BEEP_ON();
//		}
		Motor_ChangeSpeed(left_speed, LEFT_MOTOR);
		Motor_ChangeSpeed(right_speed, RIGHT_MOTOR);
		return;
	}
	if(road_mode == loop_mode){
		/*************************************************
							��
		**************************************************/
		if(loop_type == 2){							
			if(loop == 1){
				count_loop_zm++;
			}
			if(loop == 1 && count_loop_zm < 10){
				DirectionControl();
			}
			if(loop == 1 && count_loop_zm >= 10){
				loop = 2;
				count_loop_zm = 0;
			}
			if(loop == 2){
//				BEEP_ON();
				po_devi_loop = 8000* ((sensor[2]*0.1 -sensor[0]*6)/(sensor[2]*0.1 +sensor[0]*6));
				if(po_devi_loop > 5000){
					po_devi_loop = 5000;
				}
				else if(po_devi_loop < -5000){
					po_devi_loop = -5000;
				}
				left_speed = spdL_loop + po_devi_loop;
				right_speed = spdR_loop - po_devi_loop;
				count_loop_in++;
			}
			if(loop == 2  && count_loop_in > 100 && sensor_sum < 1400){
				loop = 3;
				BEEP_OFF();
				count_loop_in = 0;
			}
			if(loop == 3){
				Direction_loop();
//				BEEP_ON();
			}
			if(loop == 3 && back_sensor_sum> 1500){
				loop = 4;
//				BEEP_OFF();
				BEEP_ON();
			}
//			if(loop == 4){
//				left_speed = spdL + 6000*((sensor[4] - sensor[2]*0.25)/(sensor[4]+sensor[2]*0.25));
//				right_speed = spdR - 6000*((sensor[4] - sensor[2]*0.25)/(sensor[4]+sensor[2]*0.25));
//			}
			if(loop == 4 ){//&& sensor_sum < 2000
				loop = 0;
				//BEEP_ON();
				BEEP_OFF();
				loop_num++;
				road_mode = normal_mode;
				//flag_protect = 0;
				flag_loop_protect = 1;
				}
			
			Motor_ChangeSpeed(left_speed, LEFT_MOTOR);
			Motor_ChangeSpeed(right_speed, RIGHT_MOTOR);
			return;
				
			}
		/*************************************************
							�һ�
		**************************************************/
		if(loop_type == 1){							
			if(loop == 1){
				count_loop_zm++;
			}
			if(loop == 1 && count_loop_zm < 30){
				DirectionControl();
			}
			if(loop == 1 && count_loop_zm >= 30){
				loop = 2;
				count_loop_zm = 0;
			}
			if(loop == 2){
//				BEEP_ON();
				BEEP_OFF();
				po_devi_loop = 8000* ((sensor[2]*0.13 -sensor[4])/(sensor[2]*0.13 +sensor[4]));
				if(po_devi_loop > 5000){
					po_devi_loop = 5000;
				}
				else if(po_devi_loop < -5000){
					po_devi_loop = -5000;
				}
				left_speed = spdL_loop - po_devi_loop;
				right_speed = spdR_loop + po_devi_loop;
				count_loop_in++;
			}
			if(loop == 2  && count_loop_in > 100 && sensor_sum < 1400){
				loop = 3;
//				BEEP_OFF();
				count_loop_in = 0;
			}
			if(loop == 3){
				Direction_loop();
//				BEEP_ON();
			}
			if(loop == 3 && back_sensor_sum> 1650){
				loop = 4;
//				BEEP_OFF();
				BEEP_ON();
			}
//			if(loop == 4){
//				left_speed = spdL + 6000*((sensor[4] - sensor[2]*0.25)/(sensor[4]+sensor[2]*0.25));
//				right_speed = spdR - 6000*((sensor[4] - sensor[2]*0.25)/(sensor[4]+sensor[2]*0.25));
//			}
			if(loop == 4 ){//&& sensor_sum < 2000
				loop = 0;
				//BEEP_ON();
				BEEP_OFF();
				loop_num++;
				road_mode = normal_mode;
				//flag_protect = 0;
				flag_loop_protect = 1;
				}
			
			Motor_ChangeSpeed(left_speed, LEFT_MOTOR);
			Motor_ChangeSpeed(right_speed, RIGHT_MOTOR);
			return;
				
			}
		


		
	}
	
	
			
		/*************************************************
							���
		**************************************************/
	if(road_mode == block_mode){
		if(block_type == 1){			//�ұ���
			
		if(block == 1 && counter_block_stop < 40){					//����תһ������
				//BEEP_ON();
				counter_block_stop++;
				left_speed = 1700;
				right_speed = -1700;
			}
			if(block == 1 && counter_block_stop >= 40){		
				counter_block_stop = 0;
				block = 2;
			}
			if(block == 2 && counter_block_str_out < 90){			//����ֱ��
				counter_block_str_out++;
				left_speed = 5000;
				right_speed = 6000;
			}
			if(block == 2 && counter_block_str_out >= 90){
				counter_block_str_out = 0;
				block = 3;
			}
			if(block == 3 && counter_dsy < 80){						//����ת��
				counter_dsy++;							
				
				left_speed = -1000;
				right_speed = 5000;
			}	
			if(block == 3 && counter_dsy >= 80){
				block = 4;
				counter_dsy = 0;
			}
			if(block == 4){											//����ת��Ѳ��
				if((sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4])/5 > 150){
					block = 0;
					road_mode = normal_mode;
					
					block_protect = 1;
				}
				else{
					left_speed = 3000;
					right_speed = 5500;
				}
			}
		}
			
		if(block_type == 2){			//�����
			
			if(block == 1 && counter_block_stop < 40){					//����תһ������
				//BEEP_ON();
				counter_block_stop++;
				left_speed = -2100;
				right_speed = +2100;
			}
			if(block == 1 && counter_block_stop >= 40){		
				counter_block_stop = 0;
				block = 2;
			}
			if(block == 2 && counter_block_str_out < 90){			//����ֱ��
				counter_block_str_out++;
				left_speed = 5000;
				right_speed = 6000;
			}
			if(block == 2 && counter_block_str_out >= 90){
				counter_block_str_out = 0;
				block = 3;
			}
			if(block == 3 && counter_dsy < 80){						//����ת��
				counter_dsy++;							
				
				left_speed = 3500;
				right_speed = -1000;
			}	
			if(block == 3 && counter_dsy >= 80){
				block = 4;
				counter_dsy = 0;
			}
			if(block == 4){											//����ת��Ѳ��
				if((sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4])/5 > 150){
					block = 0;
					road_mode = normal_mode;
					
					block_protect = 1;
				}
				else{
					left_speed = 5500;
					right_speed = 3000;
				}
			}
			
		}

		if(block_type == 3){			//�µ�������
			block_protect =1;
			block = 0;
			road_mode = normal_mode;
			
		}

		
		Motor_ChangeSpeed(left_speed, LEFT_MOTOR);
		Motor_ChangeSpeed(right_speed, RIGHT_MOTOR);
		return;
	

	}
	
}

}


uint16_t mscount = 0;
uint16_t second_count=0;
void ms_CallBack()
{
	mscount ++;
}

uint16_t speed_encoder =0;
uint16_t ED_direction = 0;


void IRQ_IRQHandler(void) 
{
	if(stop_5ms >= stop_5ms_Delay)
	{
		stop_flag ++ ;
		stop_5ms = 0;
	}
	CLEAR_IRQ_FLAG;
}

int main(void) 
{ 
    ICS_QuickInit();
	
	Delay_Init();
	
	DelayMs(1000);
	
	LED_Init();//LED��ʼ��
	
	Sensor_Init();//ADC��ʼ��
	Sensor_Data_Init();

	Motor_Init();//�����ʼ��

	Echo_Init();
	
	LED_Init();
	Beep_Init();
	
#ifdef use_stop_ghg					//���øɻɹ�ʱע��
	ghg_Init();
#endif
	
	loop = 0;
    PIT_QuickInit(PIT_CHANNEL1 ,5000, PIT_CallBack);
	PIT_SetCallback(PIT_CHANNEL1,PIT_CallBack);
  while(1) 
	{
//		
	}
}

void BEEP_ON(void){
	OUTPUT_CLEAR(PTI, PTI5);
}

void BEEP_OFF(void){
	OUTPUT_SET(PTI, PTI5);
}
		
int IsStraight(float error){
	if((error < 0.3) && (error > -0.3)){
		count_straight++;
	}
	else count_straight = 0;
	
	if(count_straight > 30){
		return 1;
	}
	else return 0;
}