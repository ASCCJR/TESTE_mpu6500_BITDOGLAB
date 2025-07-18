/**
 * @file main.c
 * @brief Aplicação de teste para o driver do sensor MPU-6500.
 *
 * Este programa inicializa o sensor, lê continuamente os dados de
 * aceleração e giroscópio, converte-os para unidades físicas (g e °/s)
 * e os exibe no monitor serial.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6500.h" // Incluindo nosso driver modular

// --- Configuração da Porta I2C da BitDogLab ---
// Alterne os comentários para escolher a porta desejada para o teste.

// Configuração para I2C 1 (Esquerda) - Padrão
#define I2C_PORT i2c1
const uint I2C_SDA_PIN = 2;
const uint I2C_SCL_PIN = 3;

// Configuração para I2C 0 (Direita) - Comentado
// #define I2C_PORT i2c0
// const uint I2C_SDA_PIN = 0;
// const uint I2C_SCL_PIN = 1;

int main() {
    stdio_init_all();
    
    // Espera ativa pela conexão do monitor serial.
    while(!stdio_usb_connected()) {
        sleep_ms(100);
    }

    printf("--- Iniciando teste do Acelerometro/Giroscopio MPU-6500 ---\n");
    printf("Usando a porta I2C com SDA no pino %d e SCL no pino %d\n", I2C_SDA_PIN, I2C_SCL_PIN);

    // Inicializa o barramento I2C com velocidade de 400kHz.
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o sensor MPU-6500 usando a função do nosso driver.
    mpu6500_init(I2C_PORT);
    
    printf("Sensor inicializado. Coletando dados...\n");

    while (1) {
        mpu6500_data_t sensor_data;
        
        // Lê os dados brutos do sensor.
        mpu6500_read_raw(I2C_PORT, &sensor_data);

        // Imprime os valores convertidos para unidades físicas.
        // Fatores de conversão baseados na sensibilidade padrão do MPU-6500:
        // Acelerômetro: ±2g  ->  16384.0 LSB/g
        // Giroscópio:   ±250°/s ->  131.0 LSB/(°/s)
        printf("Acel: X=%.2fg, Y=%.2fg, Z=%.2fg  |  Giro: X=%.2f°/s, Y=%.2f°/s, Z=%.2f°/s\n",
                sensor_data.accel[0] / 16384.0f,
                sensor_data.accel[1] / 16384.0f,
                sensor_data.accel[2] / 16384.0f,
                sensor_data.gyro[0] / 131.0f,
                sensor_data.gyro[1] / 131.0f,
                sensor_data.gyro[2] / 131.0f);
        
        // Pausa de 200ms entre as leituras (frequência de 5Hz).
        sleep_ms(200);
    }
    return 0;
}