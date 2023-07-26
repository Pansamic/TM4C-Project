/**
 * @file tv_spi.c
 * @author darkbe
 * @brief 
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <main.h>
#include <hw_ints.h>
#include <ssi.h>
#include <gpio.h>
#include <tv_spi.h>
#include <tv_gpio.h>


#define DC_PIN  GPIO_PIN_0
#define MOSI_PIN  GPIO_PIN_1
#define NUM_SSI_DATA 3

void TV_SPI_Init(void)
{
    /********************************************/
    /*          SPI0 GPIO Configuration         */
    /********************************************/
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0XDAT0);
    GPIOPinConfigure(GPIO_PA5_SSI0XDAT1);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
    SSIConfigSetExpClk(SSI2_BASE, 120000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI2_BASE);
    /********************************************/
    /*          SPI2 GPIO Configuration         */
    /********************************************/
    GPIOPinConfigure(GPIO_PD3_SSI2CLK);
    GPIOPinConfigure(GPIO_PD2_SSI2FSS);
    GPIOPinConfigure(GPIO_PD1_SSI2XDAT0);
    GPIOPinConfigure(GPIO_PD0_SSI2XDAT1);
    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    SSIConfigSetExpClk(SSI2_BASE, 120000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI2_BASE);
}
void TV_SPI_W(uint8_t uc_SendData)
{
    /* 向SSI FIFO写入数据 */
    SSIDataPut(SSI2_BASE, uc_SendData);
}

void TV_SPI_R(uint8_t uc_RecvData)
{
    while(SSIBusy(SSI2_BASE));
    
}

