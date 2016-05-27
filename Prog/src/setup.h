//�������,��Ҫ����init()
#ifndef _SETUP_H_
#define _SETUP_H_

//eeprom������
//����ʱ����ɫ
#define Setup_bgColor_max 12
#define Setup_Address_bgColor (uint8_t*)0x01
//#define Setup_Default_bgColor 0x00
extern uint8_t Setup_bgColor;


//����12�Ķ���
#define Setup_key12Mode_max 6
#define Setup_Address_key12Mode (uint8_t*)0x02
extern uint8_t Setup_key12Mode;

//����3�Ķ���
#define Setup_key3Mode_max 6
#define Setup_Address_key3Mode (uint8_t*)0x03
extern uint8_t Setup_key3Mode;

//JP������
#define Setup_key12LED_OftenOff	0
#define Setup_key12LED_Always 	1
#define Setup_key12LED_OftenOn	2
#define Setup_key12LED_Never 	3
extern uint8_t Setup_key12LED;

void Setup_init();
//add��ee�ĵ�ַ var�Ǳ�����ַ max��ѭ������
void Setup_setLoop(uint8_t* add,uint8_t* var,uint8_t max);

#endif
