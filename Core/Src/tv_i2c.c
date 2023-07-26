/**
 * @file tv_i2c.c
 * @author pansamic (wanggengjie@ieee.org)
 * @brief I2C initialization and customized I2C functions
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <main.h>
#include <i2c.h>
#include <gpio.h>
#include <tv_i2c.h>
#include <tm4c129_it.h>

#include <FreeRTOS.h>

/************************************************/
/*                     I2C0                     */
/************************************************/
tI2CMInstance I2C0Inst;
volatile bool I2C0Done = true;
tI2CMWrite8 I2C0WriteInst;

/************************************************/
/*                     I2C2                     */
/************************************************/
tI2CMInstance I2C2Inst;
volatile bool I2C2Done = true;
tI2CMWrite8 I2C2WriteInst;

/************************************************/
/*                     I2C4                     */
/************************************************/
tI2CMInstance I2C4Inst;
volatile bool I2C4Done = true;
tI2CMWrite8 I2C4WriteInst;

/************************************************/
/*                     I2C5                     */
/************************************************/
tI2CMInstance I2C5Inst;
volatile bool I2C5Done = true;
tI2CMWrite8 I2C5WriteInst;

void I2C0_I2CMCallback(void *pvData, uint_fast8_t ui8Status);
void I2C2_I2CMCallback(void *pvData, uint_fast8_t ui8Status);
void I2C4_I2CMCallback(void *pvData, uint_fast8_t ui8Status);
void I2C5_I2CMCallback(void *pvData, uint_fast8_t ui8Status);


void TV_I2C_Init(void)
{
    /************************************************/
    /*                     I2C0                     */
    /************************************************/
	SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0);
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
	I2CMasterInitExpClk(I2C0_BASE, SYSTEM_FREQUENCY, true);
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
    I2CIntRegister(I2C0_BASE,I2C0_IntHandler);
    I2CMasterIntEnable(I2C0_BASE);
    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000; // clear I2C FIFOs
    I2CMInit(&I2C0Inst, I2C0_BASE, INT_I2C0, 0xff, 0xff, 120000000);
    /************************************************/
    /*                     I2C2                     */
    /************************************************/
	SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C2);
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
	I2CMasterInitExpClk(I2C2_BASE, SYSTEM_FREQUENCY, true);
	GPIOPinConfigure(GPIO_PG2_I2C2SCL);
	GPIOPinConfigure(GPIO_PG3_I2C2SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTG_BASE, GPIO_PIN_3);
    I2CIntRegister(I2C2_BASE,I2C2_IntHandler);
    I2CMasterIntEnable(I2C2_BASE);
    HWREG(I2C2_BASE + I2C_O_FIFOCTL) = 80008000; // clear I2C FIFOs
    I2CMInit(&I2C2Inst, I2C2_BASE, INT_I2C2, 0xff, 0xff, 120000000);
    /************************************************/
    /*                     I2C4                     */
    /************************************************/
	SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C4);
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C4);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C4);
	I2CMasterInitExpClk(I2C4_BASE, SYSTEM_FREQUENCY, true);
	GPIOPinConfigure(GPIO_PK6_I2C4SCL);
	GPIOPinConfigure(GPIO_PK7_I2C4SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTK_BASE, GPIO_PIN_6);
	GPIOPinTypeI2C(GPIO_PORTK_BASE, GPIO_PIN_7);
    I2CIntRegister(I2C4_BASE,I2C4_IntHandler);
    I2CMasterIntEnable(I2C4_BASE);
    HWREG(I2C4_BASE + I2C_O_FIFOCTL) = 80008000; // clear I2C FIFOs
    I2CMInit(&I2C4Inst, I2C4_BASE, INT_I2C4, 0xff, 0xff, 120000000);
    /************************************************/
    /*                     I2C5                     */
    /************************************************/
	SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C5);
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C5);
	I2CMasterInitExpClk(I2C5_BASE, SYSTEM_FREQUENCY, true);
	GPIOPinConfigure(GPIO_PB4_I2C5SCL);
	GPIOPinConfigure(GPIO_PB5_I2C5SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_4);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_5);
    I2CIntRegister(I2C5_BASE,I2C5_IntHandler);
    I2CMasterIntEnable(I2C5_BASE);
    HWREG(I2C5_BASE + I2C_O_FIFOCTL) = 80008000; // clear I2C FIFOs
    I2CMInit(&I2C5Inst, I2C5_BASE, INT_I2C5, 0xff, 0xff, 120000000);
}

    /************************************************/
    /*                     I2C0                     */
    /************************************************/

uint8_t I2C0_ReadByte(uint8_t DevAddress, uint8_t DevReg)
{
    uint8_t Data;
    I2C0Done = false;
    I2CMRead(&I2C0Inst, DevAddress, &DevReg, 1, &Data, 1, I2C0_I2CMCallback, 0);
    while(!I2C0Done)
    {}
    return Data;
}
void I2C0_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length)
{
    I2C0Done = false;
    I2CMRead(&I2C0Inst, DevAddress, &DevReg, 1, pDataDst, Length, I2C0_I2CMCallback, 0);
    while(!I2C0Done)
    {}
}

void I2C0_WriteByte(uint8_t DevAddress, uint8_t DevReg, const uint8_t Data)
{
    I2C0Done = false;
    I2CMWrite8(&I2C0WriteInst,&I2C0Inst,(uint_fast8_t)DevAddress,DevReg,&Data,1,I2C0_I2CMCallback,0);
    while(!I2C0Done)
    {}
}

void I2C0_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length)
{
    uint8_t *DataBuf = pvPortMalloc(Length+1);
    if(DataBuf==NULL)
    {
        printf("I2C0_Write: malloc failed\r\n");
        return;
    }
    DataBuf[0]=DevReg;
    memcpy(DataBuf+1, pData, Length);
    I2C0Done = false;
    I2CMWrite(&I2C0Inst, DevAddress, DataBuf, Length+1, I2C0_I2CMCallback, 0);
    while(!I2C0Done)
    {}
    vPortFree(DataBuf);
}

void I2C0_I2CMCallback(void *pvData, uint_fast8_t ui8Status)
{
    //
    // See if an error occurred.
    //
    if(ui8Status != I2CM_STATUS_SUCCESS)
    {
    //
    // An error occurred, so handle it here if required.
    //
    printf("I2C0_I2CMCallback: error\r\n");
    }
    //
    // Indicate that the I2C transaction has completed.
    //
    I2C0Done = true;
}

    /************************************************/
    /*                     I2C2                     */
    /************************************************/

uint8_t I2C2_ReadByte(uint8_t DevAddress, uint8_t DevReg)
{
    uint8_t Data;
    I2C2Done = false;
    I2CMRead(&I2C2Inst, DevAddress, &DevReg, 1, &Data, 1, I2C2_I2CMCallback, 0);
    while(!I2C2Done)
    {}
    return Data;
}
void I2C2_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length)
{
    I2C2Done = false;
    I2CMRead(&I2C2Inst, DevAddress, &DevReg, 1, pDataDst, Length, I2C2_I2CMCallback, 0);
    while(!I2C2Done)
    {}
}

void I2C2_WriteByte(uint8_t DevAddress, uint8_t DevReg, const uint8_t Data)
{
    I2C2Done = false;
    I2CMWrite8(&I2C2WriteInst,&I2C2Inst,(uint_fast8_t)DevAddress,DevReg,&Data,1,I2C2_I2CMCallback,0);
    while(!I2C2Done)
    {}
}

void I2C2_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length)
{
    uint8_t *DataBuf = pvPortMalloc(Length+1);
    if(DataBuf==NULL)
    {
        printf("I2C2_Write: malloc failed\r\n");
        return;
    }
    DataBuf[0]=DevReg;
    memcpy(DataBuf+1, pData, Length);
    I2C2Done = false;
    I2CMWrite(&I2C2Inst, DevAddress, DataBuf, Length+1, I2C2_I2CMCallback, 0);
    while(!I2C2Done)
    {}
    vPortFree(DataBuf);
}

void I2C2_I2CMCallback(void *pvData, uint_fast8_t ui8Status)
{
    //
    // See if an error occurred.
    //
    if(ui8Status != I2CM_STATUS_SUCCESS)
    {
    //
    // An error occurred, so handle it here if required.
    //
    printf("I2C2_I2CMCallback: error\r\n");
    }
    //
    // Indicate that the I2C transaction has completed.
    //
    I2C2Done = true;
}

    /************************************************/
    /*                     I2C4                     */
    /************************************************/

uint8_t I2C4_ReadByte(uint8_t DevAddress, uint8_t DevReg)
{
    uint8_t Data;
    I2C4Done = false;
    I2CMRead(&I2C4Inst, DevAddress, &DevReg, 1, &Data, 1, I2C4_I2CMCallback, 0);
    while(!I2C4Done)
    {}
    return Data;
}
void I2C4_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length)
{
    I2C4Done = false;
    I2CMRead(&I2C4Inst, DevAddress, &DevReg, 1, pDataDst, Length, I2C4_I2CMCallback, 0);
    while(!I2C4Done)
    {}
}

void I2C4_WriteByte(uint8_t DevAddress, uint8_t DevReg, const uint8_t Data)
{
    I2C4Done = false;
    I2CMWrite8(&I2C4WriteInst,&I2C4Inst,(uint_fast8_t)DevAddress,DevReg,&Data,1,I2C4_I2CMCallback,0);
    while(!I2C4Done)
    {}
}

void I2C4_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length)
{
    uint8_t *DataBuf = pvPortMalloc(Length+1);
    if(DataBuf==NULL)
    {
        printf("I2C4_Write: malloc failed\r\n");
        return;
    }
    DataBuf[0]=DevReg;
    memcpy(DataBuf+1, pData, Length);
    I2C4Done = false;
    I2CMWrite(&I2C4Inst, DevAddress, DataBuf, Length+1, I2C4_I2CMCallback, 0);
    while(!I2C4Done)
    {}
    vPortFree(DataBuf);
}

void I2C4_I2CMCallback(void *pvData, uint_fast8_t ui8Status)
{
    //
    // See if an error occurred.
    //
    if(ui8Status != I2CM_STATUS_SUCCESS)
    {
    //
    // An error occurred, so handle it here if required.
    //
    printf("I2C4_I2CMCallback: error\r\n");
    }
    //
    // Indicate that the I2C transaction has completed.
    //
    I2C4Done = true;
}


    /************************************************/
    /*                     I2C5                     */
    /************************************************/

uint8_t I2C5_ReadByte(uint8_t DevAddress, uint8_t DevReg)
{
    uint8_t Data;
    I2C5Done = false;
    I2CMRead(&I2C5Inst, DevAddress, &DevReg, 1, &Data, 1, I2C5_I2CMCallback, 0);
    while(!I2C5Done)
    {}
    return Data;
}
void I2C5_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length)
{
    I2C5Done = false;
    I2CMRead(&I2C5Inst, DevAddress, &DevReg, 1, pDataDst, Length, I2C5_I2CMCallback, 0);
    while(!I2C5Done)
    {}
}

void I2C5_WriteByte(uint8_t DevAddress, uint8_t DevReg, const uint8_t Data)
{
    I2C5Done = false;
    I2CMWrite8(&I2C5WriteInst,&I2C5Inst,(uint_fast8_t)DevAddress,DevReg,&Data,1,I2C5_I2CMCallback,0);
    while(!I2C5Done)
    {}
}

void I2C5_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length)
{
    uint8_t *DataBuf = pvPortMalloc(Length+1);
    if(DataBuf==NULL)
    {
        printf("I2C5_Write: malloc failed\r\n");
        return;
    }
    DataBuf[0]=DevReg;
    memcpy(DataBuf+1, pData, Length);
    I2C5Done = false;
    I2CMWrite(&I2C5Inst, DevAddress, DataBuf, Length+1, I2C5_I2CMCallback, 0);
    while(!I2C5Done)
    {}
    vPortFree(DataBuf);
}

void I2C5_I2CMCallback(void *pvData, uint_fast8_t ui8Status)
{
    //
    // See if an error occurred.
    //
    if(ui8Status != I2CM_STATUS_SUCCESS)
    {
    //
    // An error occurred, so handle it here if required.
    //
    printf("I2C5_I2CMCallback: error\r\n");
    }
    //
    // Indicate that the I2C transaction has completed.
    //
    I2C5Done = true;
}