#include <avr/io.h>
#include <avr/pgmspace.h>
#include "RGBLED.h"
#include "softPWM.h"

#define RGBLED_ColorQuantity 13

//RGB����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

uint8_t const RGBLED_ColorTable[RGBLED_ColorQuantity][3] ={	//ɫ�� �� ��ֵΪ����, 255Ϊ����
//��ʱ��ɫ��
{0,0,0},			//0
{255,255,255},		//

//�ٶ�ɫ��
{50,75,190},		//���� 3
{50,75,190},		//����
{10,10,190},		//����
{80,80,30},			//����
{127,50,0},			//����
{255,128,255},		//�ۺ�
{255,0,0},			//���
{255,40,100},		//�Ϻ�
{141,20,187},		//����
{255,230,255},		//��ƫ��
{255,201,0}			//��
};

//�˺�����ʾ��RGB�ƣ�����ֻ��level�й�
//RGB��PWM�ȼ�����(allPWM) = 3*PWM_Total*(RGBLv/RGB_Total)
//PWM�ȼ���һ��ɫ����R = RGB��PWM�ȼ�����*(R/R+G+B)

void RGB_setColor(uint8_t n,uint8_t level){
	uint16_t r,g,b,allRGB,allPWM;

	if (n>=RGBLED_ColorQuantity) return;

	r=RGBLED_ColorTable[n][0];
	g=RGBLED_ColorTable[n][1];
	b=RGBLED_ColorTable[n][2]; 
	
	allPWM = 3 * PWM_TotalLevel * level / RGB_TotalLevel;
	allRGB = r+g+b;
	
	r=(allPWM * r / allRGB);
	g=(allPWM * g / allRGB);
	b=(allPWM * b / allRGB);
	
	if(r>255){
		g=g*255/r;
		b=b*255/r;
		r=255;
	}else if(g>255){
		r=r*255/g;
		b=b*255/g;
		g=255;		
	}else if(b>255){
		r=r*255/b;
		g=g*255/b;
		b=255;		
	}
	
	PWM_setOutputLevel(RGB_rP,(uint8_t)r);
	PWM_setOutputLevel(RGB_gP,(uint8_t)g);
	PWM_setOutputLevel(RGB_bP,(uint8_t)b);
}
