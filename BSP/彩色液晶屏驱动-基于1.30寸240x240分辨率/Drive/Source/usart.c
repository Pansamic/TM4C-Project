/***
	*************************************************************************************************
	*	@version V1.0
	*  @date    2023-3-2
	*	@author  ���ͿƼ�	
	*	@brief   usart �ӿ���غ���
   *************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨������STM32F103���İ� 
	*	�Ա���ַ��https://shop212360197.taobao.com
	*	QQ����Ⱥ��536665479
	*
>>>>> �ļ�˵����
	*
	*  ��ʼ��USART1������ PA9/PA10��
	*  ����USART1�������շ�ģʽ����λ8λ��ֹͣλ1λ����У�顢��ʹ��Ӳ�����������ƣ�
	*  ���ڵĲ���������Ϊ115200������Ҫ���Ĳ�����ֱ���޸�usart.h��ĺ궨��USART1_BaudRate��
	*  �ض���fputc����,����֧��ʹ��printf������ӡ����
	*
	************************************************************************************************
***/

#include "usart.h"  


/*************************************************************************************************
*	�� �� ��:	USART_GPIO_Config
*
*	��������:	IO�ڳ�ʼ��
*	 
*************************************************************************************************/

void  USART_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd ( USART1_TX_CLK|USART1_RX_CLK, ENABLE); 	//IO��ʱ��ʹ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 				// PA9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// �ٶȵȼ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// �����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);						// ��ʼ��PA9

	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				//	PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//	��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//	��ʼ��PA10  
}

/*************************************************************************************************
*	�� �� ��:	Usart_Config
*
*	��������:	���ڲ�������
*	 
*************************************************************************************************/

void Usart_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// IO�ڳ�ʼ��
	USART_GPIO_Config();
	
	// ���ô��ڸ������
	USART_InitStructure.USART_BaudRate 	 = USART1_BaudRate; //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStructure.USART_StopBits   = USART_StopBits_1; //ֹͣλ1λ
	USART_InitStructure.USART_Parity     = USART_Parity_No ; //��У��
	USART_InitStructure.USART_Mode 	    = USART_Mode_Rx | USART_Mode_Tx; //���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ��Ӳ��������
	
	USART_Init(USART1,&USART_InitStructure); //��ʼ������1
	USART_Cmd(USART1,ENABLE);	//ʹ�ܴ���1
}

/*************************************************************************************************
*	�� �� ��:	fputc
*	��ڲ���:	ch - Ҫ������ַ� ��  f - �ļ�ָ�루�����ò�����
*	�� �� ֵ:	����ʱ�����ַ�������ʱ���� EOF��-1��
*	��������:	�ض��� fputc ������Ŀ����ʹ�� printf ����
*	˵    ��:	��		
*************************************************************************************************/

int fputc(int c, FILE *fp)
{

	USART_SendData( USART1,(u8)c );	// ���͵��ֽ�����
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//�ȴ�������� 

	return (c); //�����ַ�
}


