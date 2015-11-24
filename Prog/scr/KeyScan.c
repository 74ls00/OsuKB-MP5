#include <avr/io.h>
#include <avr/pgmspace.h>

#include "KeyScan.h"
#include "speed.h"
#include "setup.h"
#include "softPWM.h"

//ȫ��
uint8_t volatile KeyScan_state[KEYamount] = {0 ,0 ,0};

uint8_t volatile lastPushKey = 0;	//���һ�����µİ���
uint16_t volatile keyPushTime[KEYamount]={0,0,0};
uint8_t KeyScan_keyValue[KEYamount];
#define KeyScan_keyMask(n) (1<<n)
//���ĳkey�Ƿ񱻰���
#define keyPressed(keyPort,key) ( ( (~keyPort) &KeyScan_keyMask(key) ) == KeyScan_keyMask(key) )

volatile uint8_t KeyScan_keyChanged = 0;

void KeyScan_init(){
	switch(Setup_key12Mode){
		case 1:
		KeyScan_keyValue[0] = KEY_Z;
		KeyScan_keyValue[1] = KEY_C;
		
		break;	
	
		case 2:
		KeyScan_keyValue[0] = KEY_A;
		KeyScan_keyValue[1] = KEY_S;
		break;

		case 3:
		KeyScan_keyValue[0] = KEY_A;
		KeyScan_keyValue[1] = KEY_D;
		break;
	
		case 4:
		KeyScan_keyValue[0] = KEY_PAGEUP;
		KeyScan_keyValue[1] = KEY_PAGEDOWN;	
		break;

		case 5:
		KeyScan_keyValue[0] = KEY_UP;
		KeyScan_keyValue[1] = KEY_DOWN;
		break;

		case 6:
		KeyScan_keyValue[0] = KEY_LEFT;
		KeyScan_keyValue[1] = KEY_RIGHT;	
		break;

		default:
		KeyScan_keyValue[0] = KEY_Z;
		KeyScan_keyValue[1] = KEY_X;
		break;
		
	}

//ESC/F1/F2/F8/F12/space/enter
	switch(Setup_key3Mode){
		case 1:
			KeyScan_keyValue[2] = KEY_F1;
			break;
		case 2:
			KeyScan_keyValue[2] = KEY_F2;
			break;
		case 3:
			KeyScan_keyValue[2] = KEY_F8;
			break;
		case 4:
			KeyScan_keyValue[2] = KEY_F12;
			break;
		case 5:
			KeyScan_keyValue[2] = KEY_SPACE;
			break;
		case 6:
			KeyScan_keyValue[2] = KEY_ENTER;
			break;
		default:
			KeyScan_keyValue[2] = KEY_ESC;	
	}
}

	/*
	 *	���γ������˼·�ǽ����ڷ�ֹ���е�������а����ſ��ϵģ����ԶԷſ��ļ��Ƚ��ϸ�
	 *  ÿ��1ms���һ�ΰ���
	 *	ʹ��ȫ�ֱ���keyChanged��main��ͨ
	 */
  	
void KeyScan(void) {

  	uint8_t   keyPort,i;
	keyPort = PINC;
	
	for(i=0;i<KEYamount;i++){
		
		if(KeyScan_state[i]==0){
		//δ����
			if(keyPressed(keyPort,i)){
				//��⵽����
				KeyScan_state[i]++;
				KeyScan_keyChanged = 1;
				speed_count();
				lastPushKey = i;
				if(i<=1)	//bt12��ledģʽ������� ����
				{
					if(Setup_key12LED == Setup_key12LED_OftenOn){
						PWM_setOutputLevel_direct(i,0);							
					}else if(Setup_key12LED == Setup_key12LED_OftenOff) {
						PWM_setOutputLevel_direct(i,PWM_TotalLevel);							
					}						
				}
			}
		}
		else if(KeyScan_state[i]>0 && KeyScan_state[i]<JITTER_TIMER){
			//���µȴ��ſ�,�ſ�״̬Ҫ����10ms����ɹ��ſ�(ȥ��)
			if(!keyPressed(keyPort,i)){
				KeyScan_state[i]++;	

				if(KeyScan_state[i] >= JITTER_TIMER){
					if(i<=1)	//bt12��ledģʽ������� �ſ�
					{
						if(Setup_key12LED == Setup_key12LED_OftenOn){
							PWM_setOutputLevel(i,PWM_TotalLevel);							
						}else if(Setup_key12LED == Setup_key12LED_OftenOff) {
							PWM_setOutputLevel(i,0);
						}
					}
					//�չ�
					KeyScan_state[i] = 0;
					KeyScan_keyChanged = 1;
					keyPushTime[i] = 0;
					continue;
				}

			}
			else{
				//�ſ�ʧ��
				KeyScan_state[i] = 1;				
			}

			if(keyPushTime[i]<600){	//1.5���㳤���� �ټ�Ҳû��������
				keyPushTime[i]++;
			}

			if(keyPushTime[i]>500){
				keyPushTime[i]=0;
				if(i==2 && KeyScan_state[0] && KeyScan_state[1] && lastPushKey == 2){
					//��������,����µ��ǰ���2
					//bt3���
					Setup_setLoop(Setup_Address_key3Mode,&Setup_key3Mode,Setup_key3Mode_max);					
				}else if(i==0 && KeyScan_state[1] && KeyScan_state[2] && lastPushKey == 0){
					//��������,����µ��ǰ���0
					Setup_setLoop(Setup_Address_key12Mode,&Setup_key12Mode,Setup_key12Mode_max);
				}else if(i==1 && KeyScan_state[0] && KeyScan_state[2] && lastPushKey == 1){
					//��������,����µ��ǰ���1
					Setup_setLoop(Setup_Address_bgColor,&Setup_bgColor,Setup_bgColor_max);
				}
			}				
		}

	}//for's end
}
