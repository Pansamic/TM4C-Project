/**
 * @file tv_uart.c
 * @author pansamic (wanggengjie@ieee.org)
 * @brief UART initialization and customized functions
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <main.h>
#include <hw_ints.h>
#include <pin_map.h>
#include <gpio.h>
#include <uart.h>
#include <interrupt.h>
#include <tv_uart.h>
#include <tm4c129_it.h>



void TV_UART_Init(void)
{
#if USE_USB_UART
	/* UART0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    UARTConfigSetExpClk(UART0_BASE, SYSTEM_FREQUENCY, 115200, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    UARTIntRegister(UART0_BASE, UART0_IRQHandler);
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
	UARTIntEnable(UART0_BASE,UART_INT_RX);
    IntPrioritySet(INT_UART0,2<<5);
    IntEnable(INT_UART0);
#endif

#if USE_BLE_UART
	/* UART1 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinConfigure(GPIO_PB0_U1RX);
    UARTConfigSetExpClk(UART1_BASE, SYSTEM_FREQUENCY, 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTIntEnable(UART1_BASE,UART_INT_RX);
    UARTIntRegister(UART1_BASE,UART1_IRQHandler);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
    IntPrioritySet(INT_UART1,2<<5);
    IntEnable(INT_UART1);
#endif

#if USE_JETSON_UART
	/* UART2 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PA7_U2TX);
    GPIOPinConfigure(GPIO_PA6_U2RX);
    UARTConfigSetExpClk(UART2_BASE, SYSTEM_FREQUENCY, 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTIntEnable(UART2_BASE,UART_INT_RX);
	// UARTFIFOLevelSet(UART2_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
    UARTFIFODisable(UART2_BASE);
    UARTIntRegister(UART2_BASE,UART2_IRQHandler);
    IntPrioritySet(INT_UART2,2<<5); 
    IntEnable(INT_UART2);
#endif

#if USE_OPENMV_UART
	/* UART3 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PA5_U3TX);
    GPIOPinConfigure(GPIO_PA4_U3RX);
    UARTConfigSetExpClk(UART3_BASE, SYSTEM_FREQUENCY, 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTIntEnable(UART3_BASE,UART_INT_RX);
	UARTFIFOLevelSet(UART3_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
    UARTIntRegister(UART3_BASE,UART3_IRQHandler);
    IntPrioritySet(INT_UART3,2<<5);
    IntEnable(INT_UART3);
#endif

#if USE_K210_UART
	/* UART4 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
	GPIOPinTypeUART(GPIO_PORTK_BASE, GPIO_PIN_1 | GPIO_PIN_0);
    GPIOPinConfigure(GPIO_PK1_U4TX);
    GPIOPinConfigure(GPIO_PK0_U4RX);
    UARTConfigSetExpClk(UART4_BASE, 120000000, 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTIntEnable(UART4_BASE,UART_INT_RX);
	UARTFIFOLevelSet(UART4_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
    UARTIntRegister(UART4_BASE,UART4_IRQHandler);
    IntPrioritySet(INT_UART4,2<<5);
	IntEnable(INT_UART4);
#endif

#if USE_WIFI_UART
	/* UART5 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PC6_U5RX);
    GPIOPinConfigure(GPIO_PC7_U5TX); 
    UARTConfigSetExpClk(UART5_BASE, SYSTEM_FREQUENCY, 115200, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    UARTIntRegister(UART5_BASE, UART5_IRQHandler);
    UARTFIFOLevelSet(UART5_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
	UARTIntEnable(UART5_BASE,UART_INT_RX);
    IntPrioritySet(INT_UART5,2<<5);
    IntEnable(INT_UART5);
#endif

#if USE_WIRELESS_UART
	/* UART6 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
    GPIOPinTypeUART(GPIO_PORTP_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PP0_U6RX);
    GPIOPinConfigure(GPIO_PP1_U6TX);
    UARTConfigSetExpClk(UART6_BASE, SYSTEM_FREQUENCY, 115200, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    UARTIntRegister(UART6_BASE, UART6_IRQHandler);
    UARTFIFOLevelSet(UART6_BASE, UART_FIFO_RX1_8, UART_FIFO_TX1_8);
	UARTIntEnable(UART6_BASE,UART_INT_RX);
    IntPrioritySet(INT_UART6,2<<5);
    IntEnable(INT_UART6);
#endif

}


void UART_Transmit(uint32_t UART_Handle, void *pData, uint32_t Length)
{
    while(Length--)
    {
        UARTCharPut(UART_Handle, *(uint8_t *)pData);
        pData = (uint8_t *)pData + 1;
    }
}

