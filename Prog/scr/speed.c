#include <avr/io.h>
#include <avr/pgmspace.h>
#include "RGBLED.h"
#include "WorkMode.h"
//����
#define speed_CountList_Length 3	//400ms*3=3.2Sec

volatile uint8_t speed_CountList[speed_CountList_Length]={0,0,0};  //ѭ�����У�ÿ400msһ������
volatile uint8_t speed_CountListNow=0;                  //ѭ�����е�ǰλ��
volatile uint8_t speed_CountListTotal=0;                 //�����������ܺ�
volatile uint8_t speed_Data=0;                          //��ǰʱ��ΰ�������ͳ�� 400ms�ڵ�����

void speed_init(){
/*
	uint8_t i=speed_CountList_Length;
	while(i--)
		speed_CountList[i] = 0;
	
	speed_CountListNow = 0;
	speed_CountListTotal = 0;
	speed_Data = 0;
*/
}

void speed_count(){
	speed_Data++;
	workMode = WorkMode_SpeedTest;
}

//��speed_Data�������,���м��㣬������������ʾ����
volatile uint8_t unusedCount = 0;	//15s���� ������38ʱ����

void speed_CountList_addData(){
	speed_CountListTotal -= speed_CountList[speed_CountListNow];
	speed_CountListTotal += speed_Data;

	speed_CountList[speed_CountListNow] = speed_Data;
	speed_Data = 0;
 
 	speed_CountListNow++;
    if(speed_CountListNow >= speed_CountList_Length)
        speed_CountListNow = 0;

//display
/* ��ɫ�� �������ܶ�һ�㣩 ֻ�з�����״̬����ʾ��ɫ������:15s�ް���������,����ʱ�����ƻ��޵ƣ�
 * ��� BPM      	��ɫ     ����1.2Sec�������	
 * 0    0-25     	����     2						
 * 1    25-60       ����     5					
 * 2    60-110      ����     8						
 * 3    110-125     ����     10
 * 4    125-150     ����     12				
 * 5    170-175     �ۺ�     14
 * 6    175-200     ���     16
 * 7    200-225     �Ϻ�     18					
 * 8    225-250     ����     20					
 * 9    250-275     ��ƫ��   22					
 * 10   275����     ��       22����
 */


    uint8_t bpmLevel = 0,lightLevel = 10;
    if(speed_CountListTotal <= 2){
        bpmLevel = 0;
    }else if(speed_CountListTotal <=5){
        bpmLevel = 1;
    }else if(speed_CountListTotal <=8){
        bpmLevel = 2;
    }else if(speed_CountListTotal <=10){
        bpmLevel = 3;
    }else if(speed_CountListTotal <=12){
        bpmLevel = 4;
    }else if(speed_CountListTotal <=14){
        bpmLevel = 5;
		lightLevel = 15;
    }else if(speed_CountListTotal <=16){
        bpmLevel = 6;
		lightLevel = 20;
    }else if(speed_CountListTotal <=18){
        bpmLevel = 7;
		lightLevel = 26;
    }else if(speed_CountListTotal <=20){
        bpmLevel = 8;
		lightLevel = 32;
    }else if(speed_CountListTotal <=22){
        bpmLevel = 9;
		lightLevel =32;
    }else{
        bpmLevel = 10;
		lightLevel =32;
    }

    RGB_setColor(2 + bpmLevel,lightLevel);	//�ٶȱ�ʾɫ ��ɫ��ƫ����Ϊ16

	if(bpmLevel==0){
		unusedCount++;
		if(unusedCount>=38){
			unusedCount=0;
			WorkMode_set(WorkMode_Unused);
		}
	}else{
		unusedCount=0;
	}

}
