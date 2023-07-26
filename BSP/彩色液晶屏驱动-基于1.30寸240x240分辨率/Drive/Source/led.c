/***
	*************************************************************************************************
	*	@version V1.0
	*  @date    2023-3-2
	*	@author  反客科技	
	*	@brief   LED接口相关
   *************************************************************************************************
   *  @description
	*
	*	实验平台：反客STM32F103RCT6核心板 （型号：FK103M2）
	*	淘宝地址：https://shop212360197.taobao.com
	*	QQ交流群：536665479
	*
>>>>> 文件说明：
	*
	*	初始化LED的IO口，配置为推挽输出、速度等级2M。
	*
	************************************************************************************************
***/

#include "led.h"  


/*************************************************************************************************
*	函 数 名:	LED_Init
*
*	函数功能:	IO口初始化
*	 
*************************************************************************************************/

void LED_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_APB2PeriphClockCmd ( LED1_CLK | LED2_CLK, ENABLE); 	//初始化GPIO时钟	
				
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	
	//初始化 LED1 引脚
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	 
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);	

	//初始化 LED2 引脚
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	 
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);	
	
	GPIO_ResetBits(LED1_PORT,LED1_PIN);  //IO口输出低电平
	GPIO_ResetBits(LED2_PORT,LED2_PIN);  //IO口输出低电平	
}

/*************************************************************************************************
*	函 数 名:	LED_Toggle
*
*	入口参数:	 GPIOx - 对应的GPIO端口 ，  GPIO_Pin - 具体的引脚
*
*	函数功能:	LED 状态翻转
*	 
*************************************************************************************************/

void LED_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{	
  uint32_t odr;		// 寄存器ODR的值

  odr = GPIOx->ODR;	// 读取 ODR 的值

  GPIOx->BSRR = ((odr & GPIO_Pin) << 16) | (~odr & GPIO_Pin);		// 根据现有的IO状态取反
		
}

