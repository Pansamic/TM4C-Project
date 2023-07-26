/***
	*************************************************************************************************
	*	@version V1.0
	*  @date    2023-3-2
	*	@author  反客科技	
	*	@brief   usart 接口相关函数
   *************************************************************************************************
   *  @description
	*
	*	实验平台：反客STM32F103核心板 
	*	淘宝地址：https://shop212360197.taobao.com
	*	QQ交流群：536665479
	*
>>>>> 文件说明：
	*
	*  初始化USART1的引脚 PA9/PA10，
	*  配置USART1工作在收发模式、数位8位、停止位1位、无校验、不使用硬件控制流控制，
	*  串口的波特率设置为115200，若需要更改波特率直接修改usart.h里的宏定义USART1_BaudRate。
	*  重定义fputc函数,用以支持使用printf函数打印数据
	*
	************************************************************************************************
***/

#include "usart.h"  


/*************************************************************************************************
*	函 数 名:	USART_GPIO_Config
*
*	函数功能:	IO口初始化
*	 
*************************************************************************************************/

void  USART_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd ( USART1_TX_CLK|USART1_RX_CLK, ENABLE); 	//IO口时钟使能

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 				// PA9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 速度等级
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// 复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);						// 初始化PA9

	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				//	PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//	浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//	初始化PA10  
}

/*************************************************************************************************
*	函 数 名:	Usart_Config
*
*	函数功能:	串口参数配置
*	 
*************************************************************************************************/

void Usart_Config(void)
{		
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// IO口初始化
	USART_GPIO_Config();
	
	// 配置串口各项参数
	USART_InitStructure.USART_BaudRate 	 = USART1_BaudRate; //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStructure.USART_StopBits   = USART_StopBits_1; //停止位1位
	USART_InitStructure.USART_Parity     = USART_Parity_No ; //无校验
	USART_InitStructure.USART_Mode 	    = USART_Mode_Rx | USART_Mode_Tx; //发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流控制
	
	USART_Init(USART1,&USART_InitStructure); //初始化串口1
	USART_Cmd(USART1,ENABLE);	//使能串口1
}

/*************************************************************************************************
*	函 数 名:	fputc
*	入口参数:	ch - 要输出的字符 ，  f - 文件指针（这里用不到）
*	返 回 值:	正常时返回字符，出错时返回 EOF（-1）
*	函数功能:	重定向 fputc 函数，目的是使用 printf 函数
*	说    明:	无		
*************************************************************************************************/

int fputc(int c, FILE *fp)
{

	USART_SendData( USART1,(u8)c );	// 发送单字节数据
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//等待发送完毕 

	return (c); //返回字符
}


