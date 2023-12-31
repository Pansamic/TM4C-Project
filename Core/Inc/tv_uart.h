/**
 * @file tv_uart.h
 * @author pansamic (wanggengjie@ieee.org)
 * @brief Customized UART driver header file
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023 ALL RIGHTS RESERVED FOR PANSAMIC
 * 
 */
#ifndef _TV_UART_H_
#define _TV_UART_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>
#define USE_USB_UART 1
#if USE_USB_UART     
#define USB_UART UART0_BASE
#define USE_USB_UART_TRANSMIT 1
#define USE_USB_UART_RECEIVE 0
#endif



#define USE_JETSON_UART 0
#if USE_JETSON_UART
#define JETSON_UART UART1_BASE
#define USE_JETSON_UART_TRANSMIT 1
#define USE_JETSON_UART_RECEIVE 1
#endif

#define USE_OPENMV_UART 0
#if USE_OPENMV_UART
#define OPENMV_UART UART3_BASE
#define USE_OPENMV_UART_TRANSMIT 0
#define USE_OPENMV_UART_RECEIVE 1
#endif

#define USE_BLE_UART 0
#if USE_BLE_UART
#define BLE_UART UART4_BASE
#define USE_BLE_UART_TRANSMIT 0
#define USE_BLE_UART_RECEIVE 1
#endif

#define USE_WIFI_UART 0
#if USE_WIFI_UART
#define WIFI_UART UART5_BASE
#define USE_WIFI_UART_TRANSMIT 1
#define USE_WIFI_UART_RECEIVE 0
#endif

#define USE_WIRELESS_UART 0
#if USE_WIRELESS_UART
#define WIRELESS_UART UART6_BASE
#define USE_WIRELESS_UART_TRANSMIT 1
#define USE_WIRELESS_UART_RECEIVE 0
#endif

void TV_UART_Init(void);
void UART_Transmit(uint32_t UART_Handle, void *pData, uint32_t Length);

#ifdef __cplusplus
}
#endif
#endif /* _TV_UART_H_ */
