/**
 * @file main.c
 * @author pansamic (wanggengjie@ieee.org)
 * @brief Car driver system main file
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <main.h>
#include <interrupt.h>
#include <gpio.h>
#include <pwm.h>
#include <fpu.h>
#include <uart.h>
#include <tv_gpio.h>
#include <tv_uart.h>
#include <tv_i2c.h>
#include <tv_spi.h>
#include <tv_pwm.h>
#include <tv_dma.h>	
#include <tv_adc.h>
#include <icm20602.h>
#include <PCA9685.h>
#include <mdp_io.h>
#include <FreeRTOS.h>
#include <task.h>

/* test ssi */
#include <ssi.h>

DCMotor LeftFrontMotor = {0};
DCMotor LeftRearMotor = {0};
DCMotor RightFrontMotor = {0};
DCMotor RightRearMotor = {0};
Car_t Car = {0};
ICM20602_t ICM20602_dev = {0};
/***********************************************/
/*          OPENMV UART io Device              */
/***********************************************/

#if USE_OPENMV_UART
#define OPENMV_OUTPUTBUF1_SIZE 64
#define OPENMV_OUTPUTBUF2_SIZE 64
#define OPENMV_INTPUTBUF_SIZE 256
uint8_t OpenMVio_OutputBuf1[OpenMV_OUTPUTBUF1_SIZE];
uint8_t OpenMVio_OutputBuf2[OpenMV_OUTPUTBUF2_SIZE];
uint8_t OpenMVio_InputBuf[OpenMV_INTPUTBUF_SIZE];
uint8_t OpenMVPackageContainer[16];
MDP_io OpenMVio;
const uint8_t OpenMVPkgHead[2]={0xC8,0xFF};
const MDP_PkgFmt OpenMVPkgFmt=
{
    1,               // enable package head
	OpenMVPkgHead,     // use Jetson head sequence
    2,               // head sequence length equals two
    0,               // disable data check
    NULL,            // don't use check algorithm
    0,               // disable tail
    NULL,            // use null tail sequence
    0,               // tail sequence length equals 0
    0                // tail after check value. useless field, cuz check is disabled.
};
void OpenMV_PackageProcess(MDP_io* ioDevice, uint8_t *PkgDst);
#endif


/***********************************************/
/*       Jetson nano UART io Device            */
/***********************************************/
#if USE_JETSON_UART
#define JETSON_OUTPUTBUF1_SIZE 64
#define JETSON_OUTPUTBUF2_SIZE 64
#define JETSON_INTPUTBUF_SIZE 256
uint8_t Jetsonio_OutputBuf1[JETSON_OUTPUTBUF1_SIZE];
uint8_t Jetsonio_OutputBuf2[JETSON_OUTPUTBUF2_SIZE];
uint8_t Jetsonio_InputBuf[JETSON_INTPUTBUF_SIZE];
uint8_t JetsonPackageContainer[16];
MDP_io Jetsonio;
const uint8_t JetsonPkgHead[2]={0xC8,0xFF};
const MDP_PkgFmt JetsonPkgFmt=
{
    1,               // enable package head
	JetsonPkgHead,   // use Jetson head sequence
    2,               // head sequence length equals two
    0,               // disable data check
    NULL,            // don't use check algorithm
    0,               // disable tail
    NULL,            // use null tail sequence
    0,               // tail sequence length equals 0
    0                // tail after check value. useless field, cuz check is disabled.
};
void Jetson_PackageProcess(MDP_io* ioDevice, uint8_t *PkgDst);
#endif 

#if USE_BLE_UART
#define BLE_OUTPUTBUF1_SIZE 64
#define BLE_OUTPUTBUF2_SIZE 64
#define BLE_INTPUTBUF_SIZE 256
uint8_t BLEio_OutputBuf1[BLE_OUTPUTBUF1_SIZE];
uint8_t BLEio_OutputBuf2[BLE_OUTPUTBUF2_SIZE];
uint8_t BLEio_InputBuf[BLE_INTPUTBUF_SIZE];
uint8_t BLEPackageContainer[16];
MDP_io BLEio;
const uint8_t BLEPkgHead[2]={0xC8,0xFF};
const MDP_PkgFmt BLEPkgFmt=
{
    1,               // enable package head
	BLEPkgHead,      // use BLE head sequence
    2,               // head sequence length equals two
    0,               // disable data check
    NULL,            // don't use check algorithm
    0,               // disable tail
    NULL,            // use null tail sequence
    0,               // tail sequence length equals 0
    0                // tail after check value. useless field, cuz check is disabled.
};
void BLE_PackageProcess(MDP_io* ioDevice, uint8_t *PkgDst);
#endif

void TV_FREERTOS_Init(void);

/******************************************************/
/******************************************************/
/*                    MAIN FUNCTION                   */
/******************************************************/
/******************************************************/
int main( void )
{ 
    /* SYSTEM CLOCK INIT 120MHZ */
    SysCtlClockFreqSet(SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_CFG_VCO_240,SYSTEM_FREQUENCY);
	IntPriorityGroupingSet(3);
	FPULazyStackingEnable();
    /* PERIPHERAL INIT */
    TV_GPIO_Init();
    TV_UART_Init();
//	TV_DMA_Init();
    TV_I2C_Init();
	TV_SPI_Init();
	TV_PWM_Init();
	TV_ADC0_Init();
    PCA9685_Init();
    RGB1_SetPWM(4095,4095,4095);
    LED_Red_SetPWM(4095);
    LED_Green_SetPWM(4095);
    LED_Blue_SetPWM(4095);
    LED_Pink_SetPWM(4095);
    LED_Yellow_SetPWM(4095);
    LED_White_SetPWM(4095);
    // uint32_t data=0xFF;
    // GPIOPinWrite(ICM20602_CS_GPIO_Port, ICM20602_CS_Pin, ~ICM20602_CS_Pin);
    // SSIDataPut(SSI0_BASE, 0x13&0x7F); // reg:0x13 | write 
    // while(SSIBusy(SSI0_BASE));
    // SSIDataPut(SSI0_BASE, 0x28); // data
    // while(SSIBusy(SSI0_BASE));
    // SSIDataPut(SSI0_BASE, 0x13|0x80); // reg:0x13 | read
    // while(SSIBusy(SSI0_BASE));
    // SSIDataGet(SSI0_BASE, &data);
    // while(SSIBusy(SSI0_BASE));
    // GPIOPinWrite(ICM20602_CS_GPIO_Port, ICM20602_CS_Pin, ICM20602_CS_Pin);
    // printf("data:%x\r\n",data);
    // for(;;);

#if USE_OPENMV_UART
    io_Init(&K210io, K210_UART, K210io_InputBuf, K210_INTPUTBUF_SIZE, K210io_OutputBuf1, K210_OUTPUTBUF1_SIZE, K210io_OutputBuf2, K210_OUTPUTBUF2_SIZE);
    io_PackageMode(&K210io, K210PackageContainer, 1, 9, K210_PackageProcess);
    io_SetPkgParseFmt(&K210io,&K210PkgFmt);
	printf("K210 UART init done.\r\n");
#endif

#if USE_JETSON_UART
    io_Init(&Jetsonio, JETSON_UART, Jetsonio_InputBuf, JETSON_INTPUTBUF_SIZE, Jetsonio_OutputBuf1, JETSON_OUTPUTBUF1_SIZE, Jetsonio_OutputBuf2, JETSON_OUTPUTBUF2_SIZE);
    io_PackageMode(&Jetsonio, JetsonPackageContainer, 1, 9, Jetson_PackageProcess);
    io_SetPkgParseFmt(&Jetsonio,&JetsonPkgFmt);
	printf("Jetson nano UART init done.\r\n");
#endif
    
    DCMotor_Init(&LeftFrontMotor, DCMOTOR_REVERSE_DIRECTION, PWM0_BASE, PWM_OUT_0, LFMotor_RotateDirectionCtrl1_GPIO_Port, LFMotor_RotateDirectionCtrl1_Pin, LFMotor_RotateDirectionCtrl2_GPIO_Port, LFMotor_RotateDirectionCtrl2_Pin);
    DCMotor_Init(&LeftRearMotor, DCMOTOR_DEFAULT_DIRECTION, PWM0_BASE, PWM_OUT_1, LRMotor_RotateDirectionCtrl1_GPIO_Port, LRMotor_RotateDirectionCtrl1_Pin, LRMotor_RotateDirectionCtrl2_GPIO_Port, LRMotor_RotateDirectionCtrl2_Pin);
    DCMotor_Init(&RightFrontMotor, DCMOTOR_DEFAULT_DIRECTION, PWM0_BASE, PWM_OUT_2, RFMotor_RotateDirectionCtrl1_GPIO_Port, RFMotor_RotateDirectionCtrl1_Pin, RFMotor_RotateDirectionCtrl2_GPIO_Port, RFMotor_RotateDirectionCtrl2_Pin);
    DCMotor_Init(&RightRearMotor, DCMOTOR_DEFAULT_DIRECTION, PWM0_BASE, PWM_OUT_3, RRMotor_RotateDirectionCtrl1_GPIO_Port, RRMotor_RotateDirectionCtrl1_Pin, RRMotor_RotateDirectionCtrl2_GPIO_Port, RRMotor_RotateDirectionCtrl2_Pin);
	printf("DCMotor init done.\r\n");
	
	Add_ICM20602();

    Car_SetVelocity(200,200);

    /* FreeRTOS INIT */
	TV_FREERTOS_Init();
	printf("FreeRTOS init done.\r\nNow enter FreeRTOS scheduler.\r\n");
    /* FreeRTOS Scheduler Start */
    vTaskStartScheduler();
    while(1)
    {
    }
}

#if USE_OPENMV_UART
void OpenMV_PackageProcess(MDP_io* ioDevice, uint8_t *PkgDst)
{
    if(PkgDst[0]==0)
    {
        Car_SetVelocity(*(float*)(PkgDst+1), *(float*)(PkgDst+5));
    }
    else if(PkgDst[0]==1)
    {
        Car_SetDistance(*(float*)(PkgDst+1), *(float*)(PkgDst+5));
    }
}
#endif

#if USE_JETSON_UART
void Jetson_PackageProcess(MDP_io* ioDevice, uint8_t *PkgDst)
{
	float Left = 0;
	float Right = 0;
	memcpy(&Left, PkgDst+1, 4);
	memcpy(&Right, PkgDst+5, 4);
    if(PkgDst[0]==0)
    {
        Car_SetVelocity(Left, Right);
    }
    else if(PkgDst[0]==1)
    {
        Car_SetDistance(Left, Right);
    }
}
#endif

#if USE_BLE_UART
void BLE_PackageProcess(MDP_io* ioDevice, uint8_t *PkgDst)
{
	float Left = 0;
	float Right = 0;
	memcpy(&Left, PkgDst+1, 4);
	memcpy(&Right, PkgDst+5, 4);
    if(PkgDst[0]==0)
    {
        Car_SetVelocity(Left, Right);
    }
    else if(PkgDst[0]==1)
    {
        Car_SetDistance(Left, Right);
    }
}
#endif


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    UARTCharPut(USB_UART, ch);
    return ch;
}

void __error__(char *pcFilename, uint32_t ui32Line)
{
    printf("Error: %s, %d\r\n", pcFilename, ui32Line);
}
