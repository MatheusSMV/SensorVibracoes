# Sistema de Monitoramento de Vibração com Raspberry Pi Pico

Este projeto implementa um sistema de monitoramento de vibração utilizando um Raspberry Pi Pico. O sistema lê dados de um joystick analógico (potenciômetros) para simular vibrações, exibe os resultados em um display OLED e controla LEDs e um buzzer para fornecer feedback visual e sonoro.

## Componentes Utilizados
- **Microcontrolador**: Raspberry Pi Pico
- **Display**: OLED SSD1306 (comunicação I2C)
- **Entrada Analógica**: Joystick com potenciômetros (eixos X e Y)
- **Feedback Visual**: LEDs RGB (verde, amarelo, vermelho)
- **Feedback Sonoro**: Buzzer
- **Matriz de LEDs**: WS2812 (5x5)
- **Botões**: Dois botões para controle do sistema (A e B)

## Funcionalidades
1. **Leitura do Joystick**:
   - Os potenciômetros do joystick são lidos via ADC para simular vibrações nos eixos X e Y.
   - Os valores são convertidos em níveis de vibração.

2. **Cálculo da Vibração**:
   - A vibração total é calculada usando a magnitude do vetor:
     \[
     \text{Vibracao\_Total} = \sqrt{(\text{Vibracao\_X}^2 + \text{Vibracao\_Y}^2)}
     \]

3. **Exibição no Display OLED**:
   - O valor da vibração total é exibido no display OLED.
   - Mensagens de status são mostradas em caso de parada automática ou manual.

4. **Controle de LEDs**:
   - LEDs RGB indicam o nível de vibração:
     - **Verde**: Vibração baixa (0 a 2,3 mm/s).
     - **Amarelo**: Vibração média (2,3 a 4,5 mm/s).
     - **Vermelho**: Vibração alta (4,5 a 7,1 mm/s).

5. **Controle do Buzzer**:
   - O buzzer emite alertas sonoros em caso de vibração excessiva (acima de 7,1 mm/s).

6. **Reinício do Sistema**:
   - O sistema pode ser reiniciado manualmente pressionando o botão A.
   - Mensagens de parada automática e manual são exibidas sem sobreposição.

## Estrutura do Código
O código está organizado da seguinte forma:
- **Inicialização**: Configuração dos periféricos (I2C, ADC, GPIO, PIO).
- **Leitura e Cálculo**: Leitura dos potenciômetros e cálculo da vibração.
- **Exibição**: Atualização do display OLED com os valores de vibração.
- **Controle de LEDs e Buzzer**: Acionamento dos LEDs e buzzer com base no nível de vibração.
- **Interrupções**: Tratamento de interrupções dos botões para controle do sistema.

## Como Executar o Código

### Pré-requisitos
1. **Hardware**:
   - Raspberry Pi Pico.
   - Display OLED SSD1306.
   - Joystick analógico com potenciômetros.
   - LEDs RGB, buzzer e botões.
   - Matriz de LEDs WS2812 (opcional).

2. **Software**:
   - Ambiente de desenvolvimento configurado para Raspberry Pi Pico (por exemplo, Visual Studio Code com a extensão Pico SDK).
   - Bibliotecas necessárias:
     - `hardware/i2c.h`
     - `ssd1306.h`
     - `font.h`
     - `pico/stdlib.h`
     - `hardware/pio.h`
     - `hardware/adc.h`
     - `ws2812.pio.h`

### Passos para Execução
1. Conecte os componentes ao Raspberry Pi Pico conforme as definições de pinos no código.
2. Compile o código usando o Pico SDK.
3. Carregue o código no Raspberry Pi Pico.
4. O sistema iniciará automaticamente e começará a monitorar a vibração simulada pelo joystick.

### Pinagem
| Componente       | Pino no Raspberry Pi Pico |
|------------------|---------------------------|
| Display OLED SDA | GPIO 14                   |
| Display OLED SCL | GPIO 15                   |
| Joystick VRX     | GPIO 27 (ADC1)            |
| Joystick VRY     | GPIO 26 (ADC0)            |
| LED Verde        | GPIO 11                   |
| LED Vermelho     | GPIO 13                   |
| LED Azul         | GPIO 12                   |
| Buzzer A         | GPIO 21                   |
| Buzzer B         | GPIO 10                   |
| Botão A          | GPIO 5                    |
| Botão B          | GPIO 6                    |
| Matriz de LEDs   | GPIO 7                    |

## Testes Realizados
- **Leitura do Joystick**: Verificação da precisão dos valores lidos pelo ADC.
- **Cálculo da Vibração**: Validação do cálculo da magnitude do vetor.
- **Exibição no OLED**: Teste de exibição de mensagens e valores no display.
- **Controle de LEDs e Buzzer**: Verificação do acionamento correto dos LEDs e buzzer.
- **Reinício do Sistema**: Teste de reinício manual e exibição de mensagens de parada.

## Melhorias Futuras
1. **Calibração do Sensor**: Implementar uma rotina de calibração para maior precisão.
2. **Log de Dados**: Armazenar dados de vibração em um cartão SD para análise posterior.
3. **Interface Gráfica**: Melhorar a interface do display com gráficos ou indicadores visuais.
4. **Comunicação Remota**: Adicionar suporte para Wi-Fi ou Bluetooth para monitoramento remoto.

## Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.

## Licença
Este projeto está licenciado sob a [Licença MIT](LICENSE).
