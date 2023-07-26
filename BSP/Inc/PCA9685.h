/**
 * @file PCA9685.h
 * @author pansamic (wanggengjie@ieee.org)
 * @brief driver for PCA9685
 * @version 0.1
 * @date 2023-07-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __PCA9685_H
#define __PCA9685_H
#include <stdint.h>

/* the address of the three chip on board,
 * which can be modified by changing the 0-ohm
 * registers. */
#define PCA9685_1_ADDR         0x40
#define PCA9685_2_ADDR         0x41
#define PCA9685_3_ADDR         0x43

/**
 * @brief the register address of PCA9685
 * 
 */
/**
 * @note control bits of MODE1 register:
 * 7: restart
 * 6: extclk
 * 5: AI
 * 4: SLEEP
 * 3: SUB1
 * 2: SUB2
 * 1: SUB3
 * 0: ALLCALL
 * we should initialize the MODE1 register with 8'b1000 0000 = 0x80
 */
#define PCA9685_MODE1          0x00

/**
 * @note control bits of MODE2 register:
 * 7-5: reserved
 * 4: INVRT
 * 3: OCH
 * 2: OUTDRV
 * 1-0: OUTNE[1:0]
 * we should initialize the MODE2 register with 8'b0000 0000 = 0x00
 */
#define PCA9685_MODE2          0x01
#define PCA9685_SUBADR1        0x02
#define PCA9685_SUBADR2        0x03
#define PCA9685_SUBADR3        0x04
#define PCA9685_ALLCALLADR     0x05
#define PCA9685_LED0_ON_L      0x06
#define PCA9685_LED0_ON_H      0x07
#define PCA9685_LED0_OFF_L     0x08
#define PCA9685_LED0_OFF_H     0x09
#define PCA9685_LED1_ON_L      0x0A
#define PCA9685_LED1_ON_H      0x0B
#define PCA9685_LED1_OFF_L     0x0C
#define PCA9685_LED1_OFF_H     0x0D
#define PCA9685_LED2_ON_L      0x0E
#define PCA9685_LED2_ON_H      0x0F
#define PCA9685_LED2_OFF_L     0x10
#define PCA9685_LED2_OFF_H     0x11
#define PCA9685_LED3_ON_L      0x12
#define PCA9685_LED3_ON_H      0x13
#define PCA9685_LED3_OFF_L     0x14
#define PCA9685_LED3_OFF_H     0x15
#define PCA9685_LED4_ON_L      0x16
#define PCA9685_LED4_ON_H      0x17
#define PCA9685_LED4_OFF_L     0x18
#define PCA9685_LED4_OFF_H     0x19
#define PCA9685_LED5_ON_L      0x1A
#define PCA9685_LED5_ON_H      0x1B
#define PCA9685_LED5_OFF_L     0x1C
#define PCA9685_LED5_OFF_H     0x1D
#define PCA9685_LED6_ON_L      0x1E
#define PCA9685_LED6_ON_H      0x1F
#define PCA9685_LED6_OFF_L     0x20
#define PCA9685_LED6_OFF_H     0x21
#define PCA9685_LED7_ON_L      0x22
#define PCA9685_LED7_ON_H      0x23
#define PCA9685_LED7_OFF_L     0x24
#define PCA9685_LED7_OFF_H     0x25
#define PCA9685_LED8_ON_L      0x26
#define PCA9685_LED8_ON_H      0x27
#define PCA9685_LED8_OFF_L     0x28
#define PCA9685_LED8_OFF_H     0x29
#define PCA9685_LED9_ON_L      0x2A
#define PCA9685_LED9_ON_H      0x2B
#define PCA9685_LED9_OFF_L     0x2C
#define PCA9685_LED9_OFF_H     0x2D
#define PCA9685_LED10_ON_L     0x2E
#define PCA9685_LED10_ON_H     0x2F
#define PCA9685_LED10_OFF_L    0x30
#define PCA9685_LED10_OFF_H    0x31
#define PCA9685_LED11_ON_L     0x32
#define PCA9685_LED11_ON_H     0x33
#define PCA9685_LED11_OFF_L    0x34
#define PCA9685_LED11_OFF_H    0x35
#define PCA9685_LED12_ON_L     0x36
#define PCA9685_LED12_ON_H     0x37
#define PCA9685_LED12_OFF_L    0x38
#define PCA9685_LED12_OFF_H    0x39
#define PCA9685_LED13_ON_L     0x3A
#define PCA9685_LED13_ON_H     0x3B
#define PCA9685_LED13_OFF_L    0x3C
#define PCA9685_LED13_OFF_H    0x3D
#define PCA9685_LED14_ON_L     0x3E
#define PCA9685_LED14_ON_H     0x3F
#define PCA9685_LED14_OFF_L    0x40
#define PCA9685_LED14_OFF_H    0x41
#define PCA9685_LED15_ON_L     0x42
#define PCA9685_LED15_ON_H     0x43
#define PCA9685_LED15_OFF_L    0x44
#define PCA9685_LED15_OFF_H    0x45
#define PCA9685_ALL_LED_ON_L   0xFA
#define PCA9685_ALL_LED_ON_H   0xFB
#define PCA9685_ALL_LED_OFF_L  0xFC
#define PCA9685_ALL_LED_OFF_H  0xFD
#define PCA9685_PRE_SCALE      0xFE
#define PCA9685_TESTMODE       0xFF


void PCA9685_Init(void);
void RGB1_SetPWM(uint16_t r, uint16_t g, uint16_t b);
void LED_Green_SetPWM(uint16_t PulseWidth);
void LED_White_SetPWM(uint16_t PulseWidth);
void LED_Pink_SetPWM(uint16_t PulseWidth);
void LED_Red_SetPWM(uint16_t PulseWidth);
void LED_Yellow_SetPWM(uint16_t PulseWidth);
void LED_Blue_SetPWM(uint16_t PulseWidth);
#endif
