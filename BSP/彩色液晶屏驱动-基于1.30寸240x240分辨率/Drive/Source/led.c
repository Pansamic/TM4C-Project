/***
	*************************************************************************************************
	*	@version V1.0
	*  @date    2023-3-2
	*	@author  ���ͿƼ�	
	*	@brief   LED�ӿ����
   *************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨������STM32F103RCT6���İ� ���ͺţ�FK103M2��
	*	�Ա���ַ��https://shop212360197.taobao.com
	*	QQ����Ⱥ��536665479
	*
>>>>> �ļ�˵����
	*
	*	��ʼ��LED��IO�ڣ�����Ϊ����������ٶȵȼ�2M��
	*
	************************************************************************************************
***/

#include "led.h"  


/*************************************************************************************************
*	�� �� ��:	LED_Init
*
*	��������:	IO�ڳ�ʼ��
*	 
*************************************************************************************************/

void LED_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��
	RCC_APB2PeriphClockCmd ( LED1_CLK | LED2_CLK, ENABLE); 	//��ʼ��GPIOʱ��	
				
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	
	//��ʼ�� LED1 ����
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	 
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);	

	//��ʼ�� LED2 ����
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	 
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);	
	
	GPIO_ResetBits(LED1_PORT,LED1_PIN);  //IO������͵�ƽ
	GPIO_ResetBits(LED2_PORT,LED2_PIN);  //IO������͵�ƽ	
}

/*************************************************************************************************
*	�� �� ��:	LED_Toggle
*
*	��ڲ���:	 GPIOx - ��Ӧ��GPIO�˿� ��  GPIO_Pin - ���������
*
*	��������:	LED ״̬��ת
*	 
*************************************************************************************************/

void LED_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{	
  uint32_t odr;		// �Ĵ���ODR��ֵ

  odr = GPIOx->ODR;	// ��ȡ ODR ��ֵ

  GPIOx->BSRR = ((odr & GPIO_Pin) << 16) | (~odr & GPIO_Pin);		// �������е�IO״̬ȡ��
		
}

