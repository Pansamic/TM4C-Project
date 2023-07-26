/**
 * @file tv_i2c.h
 * @author pansamic (wanggengjie@ieee.org)
 * @brief Customized I2C driver header file
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023 ALL RIGHTS RESERVED FOR PANSAMIC
 * 
 */

#ifndef _APP_I2C_H_
#define _APP_I2C_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>
#include <i2cm_drv.h>
extern tI2CMInstance I2C0Inst;
extern volatile bool I2C0Done;
extern tI2CMWrite8 I2C0WriteInst;

extern tI2CMInstance I2C2Inst;
extern volatile bool I2C2Done;
extern tI2CMWrite8 I2C2WriteInst;

extern tI2CMInstance I2C4Inst;
extern volatile bool I2C4Done;
extern tI2CMWrite8 I2C4WriteInst;

extern tI2CMInstance I2C5Inst;
extern volatile bool I2C5Done;
extern tI2CMWrite8 I2C5WriteInst;

void TV_I2C_Init(void);

uint8_t I2C0_ReadByte(uint8_t DevAddress, uint8_t DevReg);
void I2C0_WriteByte(uint8_t DevAddress, uint8_t DevReg, uint8_t Data);
void I2C0_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length);
void I2C0_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length);

uint8_t I2C2_ReadByte(uint8_t DevAddress, uint8_t DevReg);
void I2C2_WriteByte(uint8_t DevAddress, uint8_t DevReg, uint8_t Data);
void I2C2_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length);
void I2C2_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length);

uint8_t I2C4_ReadByte(uint8_t DevAddress, uint8_t DevReg);
void I2C4_WriteByte(uint8_t DevAddress, uint8_t DevReg, uint8_t Data);
void I2C4_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length);
void I2C4_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length);

uint8_t I2C5_ReadByte(uint8_t DevAddress, uint8_t DevReg);
void I2C5_WriteByte(uint8_t DevAddress, uint8_t DevReg, uint8_t Data);
void I2C5_Read(uint8_t DevAddress, uint8_t DevReg, uint8_t *pDataDst, uint8_t Length);
void I2C5_Write(uint8_t DevAddress, uint8_t DevReg, uint8_t *pData, uint8_t Length);
#ifdef __cplusplus
}
#endif
#endif /* APP_I2C_H_ */
