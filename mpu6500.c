#include "mpu6500.h"
#include "pico/stdlib.h"

#define MPU6500_ADDR     0x68
#define MPU6500_PWR_MGMT 0x6B
#define MPU6500_ACCEL_X  0x3B

void mpu6500_init(i2c_inst_t* i2c) {
    // Para "acordar" o MPU-6500, precisamos escrever 0x00 no registrador de gerenciamento de energia
    uint8_t buf[] = {MPU6500_PWR_MGMT, 0x00};
    i2c_write_blocking(i2c, MPU6500_ADDR, buf, 2, false);
}

void mpu6500_read_raw(i2c_inst_t* i2c, mpu6500_data_t* data) {
    uint8_t buffer[14];

    // Começamos a leitura a partir do registrador de dados do acelerômetro (0x3B)
    // O sensor enviará 14 bytes em sequência: Accel(6), Temp(2), Gyro(6)
    uint8_t reg = MPU6500_ACCEL_X;
    i2c_write_blocking(i2c, MPU6500_ADDR, &reg, 1, true); // true para manter o barramento ativo
    i2c_read_blocking(i2c, MPU6500_ADDR, buffer, 14, false);

    // Converte os bytes lidos (que são de 8 bits) em números de 16 bits
    // Os valores são "big-endian", então o byte mais significativo vem primeiro
    data->accel[0] = (buffer[0] << 8) | buffer[1];
    data->accel[1] = (buffer[2] << 8) | buffer[3];
    data->accel[2] = (buffer[4] << 8) | buffer[5];
    data->temp     = (buffer[6] << 8) | buffer[7];
    data->gyro[0]  = (buffer[8] << 8) | buffer[9];
    data->gyro[1]  = (buffer[10] << 8) | buffer[11];
    data->gyro[2]  = (buffer[12] << 8) | buffer[13];
}