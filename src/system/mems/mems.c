#include "platform.h"
#include "lsm6dso_reg.h"

#include "i2c_master.h"

// #define LSM6DSO_ADDR  0x6d

// int32_t Mems_I2C_Write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
// int32_t Mems_I2C_Read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static void LSM6DSO_Init(void);

stmdev_ctx_t lsm6dsoHandler = {
    .write_reg = I2C_Master_Write,
    .read_reg = I2C_Master_Read,
    .handle = I2C1,
};

void Mems_Init(void)
{
    I2C_Master_Init();

    LSM6DSO_Init();
}

static void LSM6DSO_Init(void)
{
	static uint8_t whoamI, rst;

	lsm6dso_device_id_get(&lsm6dsoHandler, &whoamI);
	if (whoamI != LSM6DSO_ID)
	while(1);

	/*
	 *  Restore default configuration
	*/
	lsm6dso_reset_set(&lsm6dsoHandler, PROPERTY_ENABLE);
	do {
	lsm6dso_reset_get(&lsm6dsoHandler, &rst);
	} while (rst);

	/*
	 * Disable I3C interface
	*/
	lsm6dso_i3c_disable_set(&lsm6dsoHandler, LSM6DSO_I3C_DISABLE);

	/*
	*  Enable Block Data Update
	*/
	lsm6dso_block_data_update_set(&lsm6dsoHandler, PROPERTY_ENABLE);

	/*
	* Set Output Data Rate
	*/
	lsm6dso_xl_data_rate_set(&lsm6dsoHandler, LSM6DSO_XL_ODR_6667Hz);
	lsm6dso_gy_data_rate_set(&lsm6dsoHandler, LSM6DSO_GY_ODR_6667Hz);

	/*
	* Set full scale
	*/
	lsm6dso_xl_full_scale_set(&lsm6dsoHandler, LSM6DSO_2g);
	lsm6dso_gy_full_scale_set(&lsm6dsoHandler, LSM6DSO_2000dps);

	/*
	* Configure filtering chain(No aux interface)
	*
	* Accelerometer - LPF1 + LPF2 path
	*/
	lsm6dso_xl_hp_path_on_out_set(&lsm6dsoHandler, LSM6DSO_LP_ODR_DIV_100);
	lsm6dso_xl_filter_lp2_set(&lsm6dsoHandler, PROPERTY_ENABLE);
}
