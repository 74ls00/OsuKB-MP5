#include <avr/io.h>
#include <avr/pgmspace.h>
#include "RGBLED.h"
#include "speed.h"
#include "WorkMode.h"
#include "setup.h"

volatile uint8_t workMode = WorkMode_Unused;

volatile uint8_t WorkMode_timeLable =0;	//1ms �Լ�1
//volatile uint8_t breathBLNtimeLable = 0;

void WorkMode_set(uint8_t mode){
	workMode = mode;
	WorkMode_timeLable=0;	//todo �������
	if (mode==WorkMode_Unused || mode ==WorkMode_Setup){
	RGB_setColor(Setup_bgColor,32);
	}
}


void WorkMode_CLK(){
	WorkMode_timeLable++;
	switch(workMode){
		/*//todo �����������Ч����
		case WorkMode_Unused:{
			
			if(WorkMode_timeLable >= 100){ //�������ٶ�
				WorkMode_timeLable = 0;
				//������Ч��
				//RGB_setColor(Setup_bgColor,32);
				
				breathBLNtimeLable++;
				if (breathBLNtimeLable == 1){
					RGB_setColor(Setup_bgColor,32);
				}
				else if(breathBLNtimeLable == 50){
					RGB_setColor(Setup_bgColor,3);
				}
				else if(breathBLNtimeLable >= 70){
					breathBLNtimeLable = 0;
				}
			}
			break;
			
		}*/
		case WorkMode_SpeedTest:{
			if(WorkMode_timeLable >= 18){
				WorkMode_timeLable = 0;
				speed_CountList_addData();
			}
			break;
		}
		case WorkMode_Setup:{
			if(WorkMode_timeLable >= 91){
				WorkMode_timeLable = 0;
				workMode = WorkMode_Unused;
			}
			break;
		}
	}


}
