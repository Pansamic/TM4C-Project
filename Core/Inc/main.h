/**
 * @file main.h
 * @author pansamic (wanggengjie@ieee.org)
 * @brief Pin define and include files
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023 ALL RIGHTS RESERVED FOR PANSAMIC
 * 
 */
#ifndef _MAIN_H_
#define _MAIN_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <hw_memmap.h>
#include <hw_types.h>
#include <hw_i2c.h>
#include <hw_ints.h>
#include <pin_map.h>
#include <sysctl.h>

#include <motor.h>
#include <mdp_io.h>
#include <4wheel_differential.h>

#define SYSTEM_FREQUENCY 120000000

// #define USE_OPENMV          0
// #define USE_JETSON          0
// #define USE_BLE             0
// #define USE_LCD_DISPLAY     0
// #define USE_BUZZER          0
// #define USE_KEYBOARD        0
// #define USE_IST8310         0
// #define USE_ICM20602        0
// #define USE_TRACKING_MODULE 0
// #define USE_THERMOMETER     0
// #define USE_PCA9685         0
/*****************************************************/
/*                        LED                        */
/*****************************************************/
#define LEDR_Pin GPIO_PIN_0
#define LEDR_GPIO_Port GPIO_PORTL_BASE
#define LEDG_Pin GPIO_PIN_1
#define LEDG_GPIO_Port GPIO_PORTL_BASE
#define LEDB_Pin GPIO_PIN_2
#define LEDB_GPIO_Port GPIO_PORTL_BASE                           


/*****************************************************/
/*                       Motor                       */
/*****************************************************/
#define LFMotor_RotateDirectionCtrl1_Pin GPIO_PIN_4
#define LFMotor_RotateDirectionCtrl1_GPIO_Port GPIO_PORTP_BASE
#define LFMotor_RotateDirectionCtrl2_Pin GPIO_PIN_5
#define LFMotor_RotateDirectionCtrl2_GPIO_Port GPIO_PORTP_BASE

#define LRMotor_RotateDirectionCtrl1_Pin GPIO_PIN_0
#define LRMotor_RotateDirectionCtrl1_GPIO_Port GPIO_PORTN_BASE
#define LRMotor_RotateDirectionCtrl2_Pin GPIO_PIN_1
#define LRMotor_RotateDirectionCtrl2_GPIO_Port GPIO_PORTN_BASE

#define RFMotor_RotateDirectionCtrl1_Pin GPIO_PIN_2
#define RFMotor_RotateDirectionCtrl1_GPIO_Port GPIO_PORTN_BASE
#define RFMotor_RotateDirectionCtrl2_Pin GPIO_PIN_3
#define RFMotor_RotateDirectionCtrl2_GPIO_Port GPIO_PORTN_BASE

#define RRMotor_RotateDirectionCtrl1_Pin GPIO_PIN_4
#define RRMotor_RotateDirectionCtrl1_GPIO_Port GPIO_PORTN_BASE
#define RRMotor_RotateDirectionCtrl2_Pin GPIO_PIN_5
#define RRMotor_RotateDirectionCtrl2_GPIO_Port GPIO_PORTN_BASE


/*****************************************************/
/*                    Encoder                        */
/*****************************************************/
#define EncA_LeftFront_Pin GPIO_PIN_0
#define EncA_LeftFront_GPIO_Port GPIO_PORTM_BASE
#define EncA_LeftFront_IntPin GPIO_INT_PIN_0

#define EncB_LeftFront_Pin GPIO_PIN_1
#define EncB_LeftFront_GPIO_Port GPIO_PORTM_BASE
#define EncB_LeftFront_IntPin GPIO_INT_PIN_1

#define EncA_LeftRear_Pin GPIO_PIN_2
#define EncA_LeftRear_GPIO_Port GPIO_PORTM_BASE
#define EncA_LeftRear_IntPin GPIO_INT_PIN_2

#define EncB_LeftRear_Pin GPIO_PIN_3
#define EncB_LeftRear_GPIO_Port GPIO_PORTM_BASE
#define EncB_LeftRear_IntPin GPIO_INT_PIN_3

#define EncA_RightFront_Pin GPIO_PIN_5
#define EncA_RightFront_GPIO_Port GPIO_PORTM_BASE
#define EncA_RightFront_IntPin GPIO_INT_PIN_5

#define EncB_RightFront_Pin GPIO_PIN_4
#define EncB_RightFront_GPIO_Port GPIO_PORTM_BASE
#define EncB_RightFront_IntPin GPIO_INT_PIN_4

#define EncA_RightRear_Pin GPIO_PIN_6
#define EncA_RightRear_GPIO_Port GPIO_PORTM_BASE
#define EncA_RightRear_IntPin GPIO_INT_PIN_6

#define EncB_RightRear_Pin GPIO_PIN_7
#define EncB_RightRear_GPIO_Port GPIO_PORTM_BASE
#define EncB_RightRear_IntPin GPIO_INT_PIN_7


/*****************************************************/
/*                       Key                         */
/*****************************************************/
#define KEY0_Pin GPIO_PIN_6
#define KEY0_GPIO_Port GPIO_PORTL_BASE
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIO_PORTL_BASE

/*****************************************************/
/*                  SPI CS Pin                       */
/*****************************************************/
#define ICM20602_CS_Pin GPIO_PIN_3
#define ICM20602_CS_GPIO_Port GPIO_PORTA_BASE


/*****************************************************/
/*                      Keyboard                     */
/*****************************************************/
#define KEYBOARD1_GPIO_Port GPIO_PORTC_BASE
#define KEYBOARD1_Pin GPIO_PIN_4
#define KEYBOARD2_GPIO_Port GPIO_PORTC_BASE
#define KEYBOARD2_Pin GPIO_PIN_5
#define KEYBOARD3_GPIO_Port GPIO_PORTH_BASE
#define KEYBOARD3_Pin GPIO_PIN_0
#define KEYBOARD4_GPIO_Port GPIO_PORTH_BASE
#define KEYBOARD4_Pin GPIO_PIN_1
#define KEYBOARD5_GPIO_Port GPIO_PORTQ_BASE
#define KEYBOARD5_Pin GPIO_PIN_0
#define KEYBOARD6_GPIO_Port GPIO_PORTQ_BASE
#define KEYBOARD6_Pin GPIO_PIN_1
#define KEYBOARD7_GPIO_Port GPIO_PORTQ_BASE
#define KEYBOARD7_Pin GPIO_PIN_2
#define KEYBOARD8_GPIO_Port GPIO_PORTQ_BASE
#define KEYBOARD8_Pin GPIO_PIN_3
/*****************************************************/
/*                     Relay                         */
/*****************************************************/
#define RELAY1_GPIO_Port GPIO_PORTH_BASE
#define RELAY1_Pin GPIO_PIN_2

#define RELAY2_GPIO_Port GPIO_PORTH_BASE
#define RELAY2_Pin GPIO_PIN_3

#define RELAY3_GPIO_Port GPIO_PORTF_BASE
#define RELAY3_Pin GPIO_PIN_4

extern DCMotor LeftFrontMotor;
extern DCMotor LeftRearMotor;
extern DCMotor RightFrontMotor;
extern DCMotor RightRearMotor;
extern Car_t Car;

extern MDP_io Jetsonio;
extern MDP_io K210io;

#ifdef __cplusplus
}
#endif
#endif /* _MAIN_H_ */
