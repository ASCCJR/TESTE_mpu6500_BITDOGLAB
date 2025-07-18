/**
 * @file mpu6500.c
 * @brief Implementação do driver para o sensor IMU MPU-6500.
 *
 * Contém a lógica de baixo nível para comunicação I2C e para
 * ler os dados brutos dos registradores do acelerômetro e giroscópio.
 */

/**
 * https://github.com/ASCCJR
 */

#include "mpu6500.h"
#include "pico/stdlib.h"

// --- Registradores e Endereço I2C ---
#define MPU6500_ADDR     0x68 // Endereço I2C padrão quando o pino AD0 está em GND.
#define MPU6500_PWR_MGMT 0x6B // Registrador de Gerenciamento de Energia.
#define MPU6500_ACCEL_X  0x3B // Registrador inicial dos dados do acelerômetro.

void mpu6500_init(i2c_inst_t* i2c) {
    // Para "acordar" o MPU-6500, precisamos escrever 0x00 no registrador
    // de gerenciamento de energia (PWR_MGMT_1), desativando o modo "sleep".
    uint8_t buf[] = {MPU6500_PWR_MGMT, 0x00};
    i2c_write_blocking(i2c, MPU6500_ADDR, buf, 2, false);
}

void mpu6500_read_raw(i2c_inst_t* i2c, mpu6500_data_t* data) {
    uint8_t buffer[14];

    // Apontamos para o primeiro registrador de dados (ACCEL_XOUT_H em 0x3B).
    // O sensor enviará os 14 bytes de dados em sequência a partir deste ponto.
    uint8_t reg = MPU6500_ACCEL_X;
    i2c_write_blocking(i2c, MPU6500_ADDR, &reg, 1, true); // 'true' para manter o barramento ativo.
    i2c_read_blocking(i2c, MPU6500_ADDR, buffer, 14, false);

    // Converte os pares de bytes lidos (8 bits cada) em números de 16 bits.
    // O MPU-6500 envia os dados em formato "big-endian" (byte mais significativo primeiro).
    data->accel[0] = (buffer[0] << 8) | buffer[1];
    data->accel[1] = (buffer[2] << 8) | buffer[3];
    data->accel[2] = (buffer[4] << 8) | buffer[5];
    data->temp     = (buffer[6] << 8) | buffer[7];
    data->gyro[0]  = (buffer[8] << 8) | buffer[9];
    data->gyro[1]  = (buffer[10] << 8) | buffer[11];
    data->gyro[2]  = (buffer[12] << 8) | buffer[13];
}
