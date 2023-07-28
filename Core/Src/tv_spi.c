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


void TV_SPI_Init(void)
{
    /********************************************/
    /*          SPI0 GPIO Configuration         */
    /********************************************/
    /* PA3 is functioned as CS signal, configured as GPIO output rather than SSI0FSS */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA4_SSI0XDAT0); // MOSI
    GPIOPinConfigure(GPIO_PA5_SSI0XDAT1); // MISO
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5);
    SSIConfigSetExpClk(SSI0_BASE, 120000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI0_BASE);
    /********************************************/
    /*          SPI2 GPIO Configuration         */
    /********************************************/
    /* PD2 is functioned as CS signal, configured as GPIO output rather than SSI2FSS */
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    GPIOPinConfigure(GPIO_PD3_SSI2CLK);
    // GPIOPinConfigure(GPIO_PD2_SSI2FSS);
    GPIOPinConfigure(GPIO_PD1_SSI2XDAT0); // MOSI
    GPIOPinConfigure(GPIO_PD0_SSI2XDAT1); // MISO
    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3);
    SSIConfigSetExpClk(SSI2_BASE, 120000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI2_BASE);
}

void SSI0_WriteByte(uint8_t data)
{
    SSIDataPut(SSI0_BASE, data);
    while(SSIBusy(SSI0_BASE));
}

void SSI0_Write(uint8_t *data, uint32_t len)
{
    uint32_t i;
    for(i=0;i<len;i++)
    {
        SSIDataPut(SSI0_BASE, data[i]);
        while(SSIBusy(SSI0_BASE));
    }
}

uint8_t SSI0_ReadByte(void)
{
    uint8_t data;
    SSIDataGet(SSI0_BASE,&data);
    return data;
}

void SSI0_Read(uint8_t *data, uint32_t len)
{
    uint32_t i;
    for(i=0;i<len;i++)
    {
        SSIDataGet(SSI0_BASE, data+i);
        while(SSIBusy(SSI0_BASE));
    }
}
