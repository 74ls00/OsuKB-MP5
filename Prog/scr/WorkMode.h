//����ģʽ������

#ifndef _WORKMODE_h_
#define _WORKMODE_h_

#define WorkMode_Unused 	0 		//����
#define WorkMode_SpeedTest 	1 		//������ģʽ
#define WorkMode_Setup 		2 		//����ģʽ��������ʱΪ��ɫչʾ��2��ָ�Ϊģʽ0

extern volatile uint8_t workMode;
void WorkMode_set(uint8_t mode);

void WorkMode_CLK();	//��Ҫ1ms����һ��

#endif
 
