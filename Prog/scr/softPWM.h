#ifndef _softPWM_h_
#define _softPWM_h_

//pwm�˿���
#define PWM_PORT_COUNT 5
//pwm�ּ���
#define PWM_TotalLevel 64
//����ģʽ�����ٶȣ�PWM_shadeTimeLable�����ֵ��
//todo: Ϊ��ѹ������ռ䣬��ʱ������ĳ���8λ���пռ��˾͸Ļ���
#define PWM_ShadeTimeLableMax 80
extern void PWM_init();
//��Ҫѭ�����ô˺���
extern void PWM_Generator(void);
//�ı�����ȼ�
extern void PWM_setOutputLevel(uint8_t n,uint8_t level);
extern void PWM_setOutputLevel_direct(uint8_t n,uint8_t level);
#endif
