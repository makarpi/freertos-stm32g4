/*
 * file:	i2c_master.h
 * author:	makarpi
 * brief:	
 */

#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

void I2C_Master_Init(void);
int32_t I2C_Master_Write(void *handle, uint16_t slaveAddress, uint8_t reg, uint8_t *pBuffer, uint16_t length);
int32_t I2C_Master_Read(void *handle, uint16_t slaveAddress, uint8_t reg, uint8_t *pBuffer, uint16_t length);

#endif /* _I2C_MASTER_H_ */