# Teste Modular do Sensor IMU MPU-6500

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Plataforma](https://img.shields.io/badge/Plataforma-Raspberry%20Pi%20Pico-purple.svg)
![Sensor](https://img.shields.io/badge/Sensor-MPU6500-green.svg)

Este repositório contém um código teste  para o sensor de movimento de 6 eixos (IMU - Unidade de Medição Inercial) MPU-6500. O código foi desenvolvido em C para a BITDOGLAB.

O projeto demonstra uma implementação limpa de um driver de sensor, separando a lógica de baixo nível (`mpu6500.c`, `.h`) da aplicação de teste (`main.c`). Além de ler os dados brutos, o programa já os converte para unidades físicas padrão, tornando a saída de dados intuitiva e pronta para uso.

## ✨ Funcionalidades

* **Leitura de 6 Eixos:** Coleta dados de aceleração em 3 eixos (X, Y, Z) e de velocidade angular em 3 eixos (X, Y, Z).
* **Driver Modular:** A lógica de comunicação com o sensor MPU-6500 é completamente encapsulada, fornecendo uma API simples e reutilizável.
* **Conversão de Dados:** Converte os valores brutos do ADC do sensor para unidades físicas padrão: **g** (aceleração da gravidade) e **°/s** (graus por segundo).
* **Configuração Flexível de Porta:** Permite alternar facilmente o uso entre os barramentos I2C 0 e I2C 1 através de uma simples alteração no `main.c`.
* **Leitura Eficiente:** Lê todos os 14 bytes de dados do sensor (aceleração, temperatura e giroscópio) em uma única transação I2C para máxima performance.
* **Saída Serial em Tempo Real:** Exibe os dados formatados no monitor serial com uma frequência de 5Hz.

## 🛠️ Hardware e Software Necessários

### Hardware
* Placa com Raspberry Pi Pico (neste projeto, foi usada a **BitDogLab**)
* Sensor de Movimento I2C **MPU-6500** (ou MPU-9250)

### Software
* [Raspberry Pi Pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk)
* Ambiente de compilação C/C++ (GCC para ARM, CMake)
* Um programa para monitor serial (ex: o integrado no VS Code, PuTTY, etc.)

## Configurar a Porta I2C
* Por padrão, o projeto está configurado para usar o conector I2C 1 (Esquerda) da BitDogLab.
* Para trocar para o conector I2C 0 (Direita), edite o arquivo main.c
* Comente o bloco de configuração do I2C 1.
* Descomente o bloco de configuração do I2C 0.

## Exemplo para usar a porta I2C 0:

```bash
// --- Configuração da Porta I2C 1 da BitDogLab (Comentado) ---
// #define I2C_PORT i2c1
// const uint I2C_SDA_PIN = 2;
// const uint I2C_SCL_PIN = 3;

// --- Configuração da Porta I2C 0 da BitDogLab (Ativo) ---
#define I2C_PORT i2c0
const uint I2C_SDA_PIN = 0;
const uint I2C_SCL_PIN = 1;
```
## Visualizar a Saída
* Conecte o sensor MPU-6500 na porta I2C configurada.
* Abra um monitor serial conectado à porta COM do seu Pico.
* Você verá a seguinte saída, atualizada a cada 200ms:
```bash
--- Iniciando teste do Acelerometro/Giroscopio MPU-6500 ---
Usando a porta I2C com SDA no pino 2 e SCL no pino 3
Sensor inicializado. Coletando dados...
Acel: X=0.01g, Y=-0.02g, Z=1.00g  |  Giro: X=-0.54°/s, Y=0.88°/s, Z=-0.15°/s
Acel: X=0.01g, Y=-0.02g, Z=1.01g  |  Giro: X=-0.55°/s, Y=0.89°/s, Z=-0.14°/s
```
## 📂 Estrutura dos Arquivos
* main.c: A aplicação principal. Orquestra a inicialização e o loop de leitura, e converte os dados para unidades físicas.
* mpu6500.c: A implementação do driver do sensor, contendo a lógica de comunicação I2C e leitura dos registradores.
* mpu6500.h: O arquivo de cabeçalho (a interface ou API) para o driver do MPU-6500.
* CMakeLists.txt: O arquivo de build do projeto.

✍️ Autor

  ASCCJR
