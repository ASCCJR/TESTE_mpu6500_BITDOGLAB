#ifndef MPU6500_H
#define MPU6500_H

#include <stdint.h>
#include "hardware/i2c.h"

// Estrutura para armazenar os dados brutos do sensor
typedef struct {
    int16_t accel[3]; // Aceleração X, Y, Z
    int16_t gyro[3];  // Giroscópio X, Y, Z
    int16_t temp;     // Temperatura
} mpu6500_data_t;

// Funções públicas
void mpu6500_init(i2c_inst_t* i2c_port);
void mpu6500_read_raw(i2c_inst_t* i2c_port, mpu6500_data_t* data);

#endif