/**
 * @file tv_gpio.c
 * @author pansamic (wanggengjie@ieee.org)
 * @brief GPIO initialization and customize functions
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <main.h>
#include <hw_gpio.h>
#include <hw_types.h>
#include <hw_ints.h>
#include <interrupt.h>
#include <tm4c129_it.h>
#include <tv_gpio.h>

void TV_GPIO_Init(void)
{
    /* GPIO port enable */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);

    /*******************************************************/
    /*                      LED                            */
    /*******************************************************/
    GPIOPinTypeGPIOOutput(LEDR_GPIO_Port, LEDR_Pin);
	GPIOPadConfigSet(LEDR_GPIO_Port, LEDR_Pin, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    GPIOPinTypeGPIOOutput(LEDG_GPIO_Port, LEDG_Pin);
	GPIOPadConfigSet(LEDG_GPIO_Port, LEDG_Pin, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
    GPIOPinTypeGPIOOutput(LEDB_GPIO_Port, LEDB_Pin);
	GPIOPadConfigSet(LEDB_GPIO_Port, LEDB_Pin, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);

    /*******************************************************/
    /*                      Motor                          */
    /*******************************************************/
    GPIOPinTypeGPIOOutput(LFMotor_RotateDirectionCtrl1_GPIO_Port, LFMotor_RotateDirectionCtrl1_Pin);
    GPIOPinTypeGPIOOutput(LFMotor_RotateDirectionCtrl2_GPIO_Port, LFMotor_RotateDirectionCtrl2_Pin);
    GPIOPinTypeGPIOOutput(LRMotor_RotateDirectionCtrl1_GPIO_Port, LRMotor_RotateDirectionCtrl1_Pin);
    GPIOPinTypeGPIOOutput(LRMotor_RotateDirectionCtrl2_GPIO_Port, LRMotor_RotateDirectionCtrl2_Pin);
    GPIOPinTypeGPIOOutput(RFMotor_RotateDirectionCtrl1_GPIO_Port, RFMotor_RotateDirectionCtrl1_Pin);
    GPIOPinTypeGPIOOutput(RFMotor_RotateDirectionCtrl2_GPIO_Port, RFMotor_RotateDirectionCtrl2_Pin);
    GPIOPinTypeGPIOOutput(RRMotor_RotateDirectionCtrl1_GPIO_Port, RRMotor_RotateDirectionCtrl1_Pin);
    GPIOPinTypeGPIOOutput(RRMotor_RotateDirectionCtrl2_GPIO_Port, RRMotor_RotateDirectionCtrl2_Pin);

    /*******************************************************/
    /*                      Encoder                        */
    /*******************************************************/
    GPIOPinTypeGPIOInput(EncA_LeftFront_GPIO_Port, EncA_LeftFront_Pin);
    GPIOPinTypeGPIOInput(EncB_LeftFront_GPIO_Port, EncB_LeftFront_Pin);
    GPIOPinTypeGPIOInput(EncA_LeftRear_GPIO_Port, EncA_LeftRear_Pin);
    GPIOPinTypeGPIOInput(EncB_LeftRear_GPIO_Port, EncB_LeftRear_Pin);
    GPIOPinTypeGPIOInput(EncA_RightFront_GPIO_Port, EncA_RightFront_Pin);
    GPIOPinTypeGPIOInput(EncB_RightFront_GPIO_Port, EncB_RightFront_Pin);
    GPIOPinTypeGPIOInput(EncA_RightRear_GPIO_Port, EncA_RightRear_Pin);
    GPIOPinTypeGPIOInput(EncB_RightRear_GPIO_Port, EncB_RightRear_Pin);

    /*******************************************************/
    /*                      Key                            */
    /*******************************************************/
    GPIOPinTypeGPIOInput(KEY0_GPIO_Port, KEY0_Pin);
    GPIOPinTypeGPIOInput(KEY1_GPIO_Port, KEY1_Pin);

    /*******************************************************/
    /*                      Relay                          */
    /*******************************************************/
	GPIOPinTypeGPIOOutput(RELAY1_GPIO_Port,RELAY1_Pin);
	GPIOPadConfigSet(RELAY1_GPIO_Port, RELAY1_Pin, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
	GPIOPinTypeGPIOOutput(RELAY2_GPIO_Port,RELAY2_Pin);
	GPIOPadConfigSet(RELAY2_GPIO_Port, RELAY2_Pin, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
	GPIOPinTypeGPIOOutput(RELAY3_GPIO_Port,RELAY3_Pin);
	GPIOPadConfigSet(RELAY3_GPIO_Port, RELAY3_Pin, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);

    /*******************************************************/
    /*                      Keyboard                       */
    /*******************************************************/
    GPIOPinTypeGPIOInput(KEYBOARD1_GPIO_Port, KEYBOARD1_Pin);
    GPIOPinTypeGPIOInput(KEYBOARD2_GPIO_Port, KEYBOARD2_Pin);
    GPIOPinTypeGPIOInput(KEYBOARD3_GPIO_Port, KEYBOARD3_Pin);
    GPIOPinTypeGPIOInput(KEYBOARD4_GPIO_Port, KEYBOARD4_Pin);
    GPIOPinTypeGPIOOutput(KEYBOARD5_GPIO_Port, KEYBOARD5_Pin);
    GPIOPinTypeGPIOOutput(KEYBOARD6_GPIO_Port, KEYBOARD6_Pin);
    GPIOPinTypeGPIOOutput(KEYBOARD7_GPIO_Port, KEYBOARD7_Pin);
    GPIOPinTypeGPIOOutput(KEYBOARD8_GPIO_Port, KEYBOARD8_Pin);

    /*******************************************************/
    /*                  Encoder Interrupt                  */
    /*******************************************************/
    GPIOIntRegister(GPIO_PORTM_BASE, EXTI_GPIOM_IRQHandler);
    IntPrioritySet(INT_GPIOM, 3<<5);

    GPIOIntEnable(EncA_LeftFront_GPIO_Port, EncA_LeftFront_IntPin);
    GPIOIntTypeSet(EncA_LeftFront_GPIO_Port, EncA_LeftFront_Pin, GPIO_BOTH_EDGES);

    GPIOIntEnable(EncB_LeftFront_GPIO_Port, EncB_LeftFront_IntPin);
    GPIOIntTypeSet(EncB_LeftFront_GPIO_Port, EncB_LeftFront_Pin, GPIO_BOTH_EDGES);

    GPIOIntEnable(EncA_LeftRear_GPIO_Port, EncA_LeftRear_IntPin);
    GPIOIntTypeSet(EncA_LeftRear_GPIO_Port, EncA_LeftRear_Pin, GPIO_BOTH_EDGES);

    GPIOIntEnable(EncB_LeftRear_GPIO_Port, EncB_LeftRear_IntPin);
    GPIOIntTypeSet(EncB_LeftRear_GPIO_Port, EncB_LeftRear_Pin, GPIO_BOTH_EDGES);

    GPIOIntEnable(EncA_RightFront_GPIO_Port, EncA_RightFront_IntPin);
    GPIOIntTypeSet(EncA_RightFront_GPIO_Port, EncA_RightFront_Pin, GPIO_BOTH_EDGES);

    GPIOIntEnable(EncB_RightFront_GPIO_Port, EncB_RightFront_IntPin);
    GPIOIntTypeSet(EncB_RightFront_GPIO_Port, EncB_RightFront_Pin, GPIO_BOTH_EDGES);

    GPIOIntEnable(EncA_RightRear_GPIO_Port, EncA_RightRear_IntPin);
    GPIOIntTypeSet(EncA_RightRear_GPIO_Port, EncA_RightRear_Pin, GPIO_BOTH_EDGES);
 
    GPIOIntEnable(EncB_RightRear_GPIO_Port, EncB_RightRear_IntPin);
    GPIOIntTypeSet(EncB_RightRear_GPIO_Port, EncB_RightRear_Pin, GPIO_BOTH_EDGES);
}

