#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6500.h" // Incluindo a nossa nova biblioteca

// Pinos do conector I2C 1 da BitDogLab
#define I2C_PORT i2c1
const uint I2C_SDA_PIN = 2;
const uint I2C_SCL_PIN = 3;

int main() {
    stdio_init_all();
    sleep_ms(4000); // Pausa para o monitor serial iniciar

    printf("--- Iniciando teste do Acelerometro/Giroscopio MPU-6500 ---\n");

    // Inicializa o I2C com 400kHz, uma velocidade comum para este sensor
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o sensor MPU-6500 (acorda ele do modo de baixo consumo)
    mpu6500_init(I2C_PORT);
    
    printf("Sensor inicializado. Coletando dados...\n");

    while (1) {
        // Cria uma estrutura para guardar os dados
        mpu6500_data_t sensor_data;
        // Lê os dados brutos do sensor
        mpu6500_read_raw(I2C_PORT, &sensor_data);

        // Imprime os valores lidos
        // 'd' é o formatador para inteiros com sinal (signed int)
        printf("Acel: X=%d, Y=%d, Z=%d  |  ", sensor_data.accel[0], sensor_data.accel[1], sensor_data.accel[2]);
        printf("Giro: X=%d, Y=%d, Z=%d\n", sensor_data.gyro[0], sensor_data.gyro[1], sensor_data.gyro[2]);
        
        sleep_ms(200); // Pausa para não sobrecarregar o monitor
    }
    return 0;
}