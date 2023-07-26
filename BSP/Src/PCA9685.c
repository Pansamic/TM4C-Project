/**
 * @file PCA9685.c
 * @author pansamic (wanggengjie@ieee.org)
 * @brief driver for PCA9685
 * @version 0.1
 * @date 2023-07-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <PCA9685.h>
#include <tv_i2c.h>

#define PCA9685_WriteReg(addr, reg, data)\
        I2C2_WriteByte(addr, reg, data)
#define PCA9685_ReadReg(addr, reg)\
        I2C2_ReadByte(addr, reg)

/**
 * @brief Initialize PCA9685
 * 
 */
void PCA9685_Init(void)
{
    /* No.1 PCA9685 initialization */
    PCA9685_WriteReg(PCA9685_1_ADDR, PCA9685_MODE1, 0x80);
    SysCtlDelay(120000); // wait for PCA9685 to restart
    PCA9685_WriteReg(PCA9685_1_ADDR, PCA9685_MODE2, 0x40);

    /* No.2 PCA9685 initialization */
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_MODE1, 0x80);
    SysCtlDelay(120000); // wait for PCA9685 to restart
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_MODE2, 0x40);

    /* No.3 PCA9685 initialization */
    PCA9685_WriteReg(PCA9685_3_ADDR, PCA9685_MODE1, 0x80);
    SysCtlDelay(120000); // wait for PCA9685 to restart
    PCA9685_WriteReg(PCA9685_3_ADDR, PCA9685_MODE2, 0x40);
}
/**
 * @brief Set LED_RGB1 PWM duty cycle
 * 
 * @param r integer from 0 to 4095
 * @param g integer from 0 to 4095
 * @param b integer from 0 to 4095
 */
void RGB1_SetPWM(uint16_t r, uint16_t g, uint16_t b)
{
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED0_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED0_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED0_OFF_L, r & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED0_OFF_H, r >> 8);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED1_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED1_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED1_OFF_L, g & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED1_OFF_H, g >> 8);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED2_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED2_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED2_OFF_L, b & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED2_OFF_H, b >> 8);
}

/**
 * @brief Set LED1 PWM duty cycle
 * 
 * @param PulseWidth integer from 0 to 4096
 */
void LED1_SetPWM(uint16_t PulseWidth)
{
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED3_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED3_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED3_OFF_L, PulseWidth & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED3_OFF_H, PulseWidth >> 8);
}

/**
 * @brief Set LED2 PWM duty cycle
 * 
 * @param PulseWidth integer from 0 to 4096
 */
void LED2_SetPWM(uint16_t PulseWidth)
{
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED4_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED4_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED4_OFF_L, PulseWidth & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED4_OFF_H, PulseWidth >> 8);
}

/**
 * @brief Set LED3 PWM duty cycle
 * 
 * @param PulseWidth 
 */
void LED3_SetPWM(uint16_t PulseWidth)
{
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED5_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED5_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED5_OFF_L, PulseWidth & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED5_OFF_H, PulseWidth >> 8);
}

/**
 * @brief Set LED4 PWM duty cycle
 * 
 * @param PulseWidth integer from 0 to 4096
 */
void LED4_SetPWM(uint16_t PulseWidth)
{
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED6_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED6_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED6_OFF_L, PulseWidth & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED6_OFF_H, PulseWidth >> 8);
}

/**
 * @brief integer from 0 to 4096
 * 
 * @param PulseWidth integer from 0 to 4096
 */
void LED5_SetPWM(uint16_t PulseWidth)
{
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED7_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED7_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED7_OFF_L, PulseWidth & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED7_OFF_H, PulseWidth >> 8);
}

/**
 * @brief Set LED6 PWM duty cycle
 * 
 * @param PulseWidth integer from 0 to 4096
 */
void LED6_SetPWM(uint16_t PulseWidth)
{
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED8_ON_L, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED8_ON_H, 0x00);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED8_OFF_L, PulseWidth & 0xFF);
    PCA9685_WriteReg(PCA9685_2_ADDR, PCA9685_LED8_OFF_H, PulseWidth >> 8);
}