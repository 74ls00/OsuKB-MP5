/*���÷���:
	���ߣ�ӳ��

	������һ��:����bt3�Զ��尴����ֵ
*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h> 
#include <avr/interrupt.h>
#include "KeyScan.h"
#include "setup.h"
#include "softPWM.h"
#include "workmode.h"
//JP�Գ����������
/*
#define JP1 (!(PIND && (1<<5)))
#define JP2 (!(PIND && (1<<6)))
#define JP3 (!(PIND && (1<<7)))
#define JP4 (!(PINB && (1<<0)))
#define JP5 (!(PINB && (1<<1)))
#define JP6 (!(PINB && (1<<2)))
*/
//ȫ�ֱ���
uint8_t Setup_bgColor;
uint8_t Setup_key12Mode;
uint8_t Setup_key3Mode;
uint8_t Setup_scanMode;
uint8_t Setup_key12LED;
//�ֲ�����
uint8_t needEE=0;
uint8_t *addEE;
uint8_t dataEE;


void Setup_init(){
/*
 * PD5-7	JP1-JP3
 * PB0-2	JP4-JP6	

		JP2	JP1	������
		0	0	����
		0	1	���������±���
		1	0	���������±䰵
		1	1	����
		
		JP6
		0		����ģʽ
		1		������ģʽ
*/

/*//todo ʡ�ռ�,ֻ��JP1 JP2
 	uint8_t jpData;
	jpData = ~(((PIND & 0xe0)>>5)|((PINB & 0x07)<<3));
	Setup_key12LED = jpData & 0x03;
*/
	Setup_key12LED = (~PIND & 0x60)>>5;

//read EEPROM
	eeprom_busy_wait();
	Setup_bgColor = eeprom_read_byte(Setup_Address_bgColor);
	Setup_key12Mode = eeprom_read_byte(Setup_Address_key12Mode);
	Setup_key3Mode = eeprom_read_byte(Setup_Address_key3Mode);
	
}


ISR(EE_READY_vect){
	if(needEE){
		eeprom_write_byte(addEE,dataEE);		
		needEE=0;
		EECR &= ~(1<<EERIE);
	}
}
/*
void Setup_save(){
//	eeprom_busy_wait();
//	eeprom_write_byte(Setup_Address_bgColor,Setup_bgColor);

//	eeprom_busy_wait();
//	eeprom_write_byte(Setup_Address_key3Mode,Setup_key3Mode);
}


void Setup_settingMode(){
//rgb��������ʱ����ɫ��RGB����Ч/RGB��ʱ����/�׻�/ů��/����/����/ů��/Ϲ�۰�
//������ģʽ����ʱ������/����/���²���������/���¾��� ������
	
}
*/



//add��ee�ĵ�ַ num��ѭ������
void Setup_setLoop(uint8_t* add,uint8_t* var,uint8_t max){
	addEE = add;
	(*var)++;
	if(*var>max){
		*var=0;
	}
	dataEE=*var;
	KeyScan_init();
	
	WorkMode_set(WorkMode_Setup);
	EECR |=(1<<EERIE);
	needEE=1;
}

