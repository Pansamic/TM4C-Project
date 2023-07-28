#ifndef _TV_SPI_H_
#define _TV_SPI_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>

void TV_SPI_Init(void);
void SSI0_WriteByte(uint8_t data);
void SSI0_Write(uint8_t *data, uint32_t len);
uint8_t SSI0_ReadByte(void);
void SSI0_Read(uint8_t *data, uint32_t len);


#ifdef __cplusplus
}
#endif
#endif
