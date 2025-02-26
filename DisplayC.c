#include "hardware/i2c.h" //Biblioteca para controlar o barramento I2C no Raspberry Pi Pico.
#include "inc/ssd1306.h" //Biblioteca para controle do display OLED SSD1306, incluindo renderização de texto.
#include "inc/font.h" //Biblioteca onde está o nosso alfabeto.
#include <stdio.h> //Biblioteca padrão C.
#include "pico/stdlib.h" //Biblioteca das funções básicas do Raspberry Pi Pico, como inicialização e controle de GPIOs.
#include "hardware/pio.h" //Biblioteca das funções para manipulação do PIO (Programmable I/O) para controlar a matriz de LEDs WS2812.
#include "hardware/clocks.h" //Biblioteca das funções para trabalhar com temporizadores.
#include "hardware/timer.h" //Biblioteca das funções para trabalhar com controle de relógios.
#include "hardware/adc.h" //Biblioteca para o conversor analógico digital.      
#include <math.h> //Biblioteca para as funções matemáticas.
#include "ws2812.pio.h" //Biblioteca das funções para controle da matriz de LEDs WS2812.
#include "anim.h"

#define I2C_PORT i2c1 //Definição das portas I2C.
#define I2C_SDA 14 //Definição das portas I2C.
#define I2C_SCL 15 //Definição das portas I2C.
#define endereco 0x3C //Endereço do display no barramento I2C.

#define Led_G 11 //Definindo o pino 11 do led verde.
#define Led_B 12 //Definindo o pino 12 do led azul.
#define Led_R 13 //Defidindo o pino 13 do led vermelho.

#define Buzzer_A 21 //Definindo o Buzzer no pino 21.
#define Buzzer_B 10 //Definindo o Buzzer no pino 10.

#define botao_a 5 //Definindo o botao a no pino 5.
#define botao_b 6 //Definindo o botao b no pino 6.
#define Debounce_b 500//Debounce para o botão 22.
#define Debounce_a 400//Debounce para o botão 22.

#define VRX_PIN 27 //Definindo o Pino do Potênciometro X.
#define VRY_PIN 26 //Definindo o Pino do Potênciometro Y.


#define IS_RGBW false //Apenas o RGB sem LED Branco.
#define WS2812_PIN 7 //A Matriz de LED GPIO 7.
#define NUM_PIXELS 25 // A matriz de Led 5x5

//Variáveis globais
uint8_t led_r = 50; //Potência do nosso led vermelho da matriz de leds.
uint8_t led_g = 0; //Verde desligado.
uint8_t led_b = 0; //Azul desligado


bool sistema = true; //Variável que controla o sistema.
bool press_b = false; //Variável pra eu alterar no botao B.

bool led_buffer[NUM_PIXELS]; //Armazinar o Número de Pixels


void botao_irq_handler(uint gpio, uint32_t events) {
  static uint32_t ultima_interrup_a = 0; //Capturar o tempo da interrupção.
  static uint32_t ultima_interrup_b = 0; //Capturar o tempo da interrupção.
  uint32_t tempo_atual = to_ms_since_boot(get_absolute_time()); // Tempo atual em ms desde o início do sistema
  // Verifica se o botão A foi pressionado
  if (gpio == botao_a && tempo_atual - ultima_interrup_a > Debounce_a) {
      sistema = true;
      ultima_interrup_a = tempo_atual; //Atualiza o tempo da última interrupção.
  }

  if (gpio == botao_b && tempo_atual - ultima_interrup_b > Debounce_b) {
    sistema = false; 
    press_b = true;
    ultima_interrup_a = tempo_atual; //Atualiza o tempo da última interrupção.
}else{

  press_b = false;

}
}

//Função que envia um valor de cor para o pino de controle da matriz de LEDs WS2812.
static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
  }
  
  //Função que converte valores RGB em um valor de 32 bits no formato GRB.
  static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
  }

//Função para configurar as cores dos leds conforme a leitura e o setado nas variáveis globais.
void set_one_led(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = urgb_u32(r, g, b);
    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(led_buffer[i] ? color : 0);
    }
  }



//Função para configurar as cores dos leds conforme a leitura e o setado nas variáveis globais.

int main() {
  stdio_init_all(); //Inicializando serial.

  PIO pio = pio0; //Definindo o PIO 0 para controlar a matriz de leds.
  int sm = 0; //Maquina de estado = 0.
  uint offset = pio_add_program(pio, &ws2812_program); //Programa para controlar os leds da matriz.
  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW); //Inicializa o PIO com o programa WS2812.


  adc_init(); //Iniciando o ADC.
  adc_gpio_init(VRX_PIN); //Iniciando o PINO VRX.
  adc_gpio_init(VRY_PIN); //Iniciando o PINO VRY.

  //I2C Inicialização.
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);                                //Inicialização do I²C com o Display OLED.
  gpio_pull_up(I2C_SCL);
  ssd1306_t ssd; 
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
  ssd1306_config(&ssd);
  ssd1306_send_data(&ssd);

gpio_init(Led_G);
gpio_set_dir(Led_G, GPIO_OUT); //Inicializando o LED verde.
gpio_put(Led_G, false);

gpio_init(Led_R);
gpio_set_dir(Led_R, GPIO_OUT); //Inicializando o LED vermelho.
gpio_put(Led_R, false);

gpio_init(Led_B);
gpio_set_dir(Led_B, GPIO_OUT); //Inicializando o LED azul.
gpio_put(Led_B, false);

gpio_init(botao_a);
gpio_set_dir(botao_a, GPIO_IN); //Inicializando o Botão A.
gpio_pull_up(botao_a);
gpio_set_irq_enabled_with_callback(botao_a, GPIO_IRQ_EDGE_FALL, true, &botao_irq_handler); //Chamar a função de interrupção na borda de descida.

gpio_init(botao_b);
gpio_set_dir(botao_b, GPIO_IN); //Inicializando o Botão B.
gpio_pull_up(botao_b);
gpio_set_irq_enabled_with_callback(botao_b, GPIO_IRQ_EDGE_FALL, true, &botao_irq_handler); //Chamar a função de interrupção na borda de descida.

gpio_init(Buzzer_A);
gpio_set_dir(Buzzer_A, GPIO_OUT); //Inicializando o Buzzer A.
gpio_put(Buzzer_A, false);

gpio_init(Buzzer_B);
gpio_set_dir(Buzzer_B, GPIO_OUT); //Inicializando o Buzzer B.
gpio_put(Buzzer_B, false);



bool cor = true; //Cor nesse caso verdadeiro é branco

char valor_vibracao[16]; // Armazenar a string do valor da vibração.



  while (true) {


    if (sistema)
    {
      adc_select_input(1); //Canal do VRX
      uint16_t VRX_Valor = adc_read(); //Lendo o valor do VRX.
      adc_select_input(0); //Canal do VRY  
      uint16_t VRY_Valor = adc_read(); //Lendo o valor do VRY.

    
     
  
  
      int16_t Valor_VRX = (VRX_Valor > 2048) ? (VRX_Valor - 2048) * 2 : (2048- VRX_Valor) * 2; //Condição para o centro.
      int16_t Valor_VRY = (VRY_Valor > 2048) ? (VRY_Valor - 2048) * 2 : (2048 - VRY_Valor) * 2; //Condição para o centro.

  
  
  
      float Vibracao_X = (Valor_VRX * (7.2)) / 4096; //Capturar a vibração pelo potênciometro do eixo X.
      float Vibracao_Y = (Valor_VRY * (7.2)) / 4096; //Capturar a vibração pelo potênciometro do eixo Y.

      if (Vibracao_X < 2.3 && Vibracao_Y < 2.3) {
        caso_inicial();
        set_one_led(0, 50, 0); // Chama a função para setar a cor verde
        sleep_ms(200); // Pequena pausa para visualização

    }
    
    if (Vibracao_X >= 2.3 && Vibracao_X < 4.5 && Vibracao_Y < 2.3) {
        caso_x_medio();
        set_one_led(50, 50, 0); // Chama a função para setar a cor verde
        sleep_ms(200); // Pequena pausa para visualização

    }

    if (Vibracao_X >= 4.5 && Vibracao_Y < 2.3) {
        caso_x_extremo();
        set_one_led(50, 0, 0); // Chama a função para setar a cor verde
        sleep_ms(200); // Pequena pausa para visualização

    }

    if (Vibracao_Y >= 2.3 && Vibracao_Y < 4.5 && Vibracao_X < 2.3) {
        caso_y_medio();
        set_one_led(50, 50, 0); // Chama a função para setar a cor verde
        sleep_ms(200); // Pequena pausa para visualização

    }

    if (Vibracao_Y >= 4.5 && Vibracao_X < 2.3) {
        caso_y_extremo();
        set_one_led(50, 0, 0); // Chama a função para setar a cor verde
        sleep_ms(200); // Pequena pausa para visualização

    }

    if (Vibracao_X >= 2.3 && Vibracao_X < 3 && Vibracao_Y >= 2.3 && Vibracao_Y < 3) {
        caso_xy_medio();
        set_one_led(50, 50, 0); // Chama a função para setar a cor verde
        sleep_ms(200); // Pequena pausa para visualização

    }

    if (Vibracao_X >= 3 && Vibracao_Y >= 3 ) {
        caso_xy_medio();
        set_one_led(50, 0, 0); // Chama a função para setar a cor verde
        sleep_ms(200); // Pequena pausa para visualização

    }


      
  
      float Vibracao_Total = sqrt((Vibracao_X * Vibracao_X) + (Vibracao_Y * Vibracao_Y)); //Pego o vetor do potenciômetro.

      ssd1306_fill(&ssd, !cor); // Limpa o display
      ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
      ssd1306_draw_string(&ssd, "VIBRACAO TOTAL: ", 8, 10); // Desenha uma string

      snprintf(valor_vibracao, sizeof(valor_vibracao), "%.2f mm/s", Vibracao_Total); //Transformando o valor da vibração em texto.

      ssd1306_draw_string(&ssd, valor_vibracao, 30, 30); //Desenhado no display.
  
  
      if (Vibracao_Total >= 0 && Vibracao_Total < 2.3) { //Zona A: 0 a 2,3 mm/s.
          gpio_put(Led_G, true);
          gpio_put(Led_R, false);
          gpio_put(Led_B, false);
      } else if (Vibracao_Total >= 2.3 && Vibracao_Total < 4.5) { //Zona B: 2,3 a 4,5 mm/s.
          gpio_put(Led_G, true);
          gpio_put(Led_R, true);
          gpio_put(Led_B, false);
      } else if (Vibracao_Total >= 4.5 && Vibracao_Total <= 7.1) { //Zona C: 4,5 a 7,1 mm/s.
          gpio_put(Led_G, false);
          gpio_put(Led_R, true);
          gpio_put(Led_B, false);
      } else if (Vibracao_Total> 7.1) { //Zona D: acima de 7,1 mm/s.
          gpio_put(Led_G,false); //Desligando o Led Verde.
          gpio_put(Led_R,false); //Ligando o Led Vermelho.
          gpio_put(Led_B,false); //Desligando o Led Azul.
  
      // Loop para fazer o LED Vermelho piscar
      for (int i = 0; i < 5; i++) { // Piscar 5 vezes, por exemplo
          for (int i = 0; i < 20; i++) { // 20 ciclos de bip rápido
              gpio_put(Buzzer_A, true);
              gpio_put(Buzzer_B, true);
              sleep_us(500); // 500 µs = frequência de 1000 Hz (mais audível)
              gpio_put(Buzzer_A, false);
              gpio_put(Buzzer_B, false);
              sleep_us(500);
          }
          gpio_put(Led_R, true); // Ligando o Led Vermelho.
          sleep_ms(333);
          gpio_put(Led_R, false); // Desligando o Led Vermelho.
          sleep_ms(333);
      }

      sistema = false; //Desligo o sistema para evitar danos a máquina.
      ssd1306_fill(&ssd, !cor); // Limpa o display
      ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
      ssd1306_draw_string(&ssd, "SYSTEM:", 10, 10); // Desenha uma string
      ssd1306_draw_string(&ssd, "FALSE", 76, 10); // Desenha uma string
      ssd1306_draw_string(&ssd, "VIBRACAO MAX: ", 10, 25); // Desenha uma string
      ssd1306_draw_string(&ssd, valor_vibracao, 30, 45); //Desenhado no display.

      }
      ssd1306_send_data(&ssd);
      sleep_ms(200);
    }

    if(sistema == false && press_b == true){ //quando eu apertar B

      gpio_put(Led_G,false); //Desligando o Led Verde.
      gpio_put(Led_R,false); //Ligando o Led Vermelho.
      gpio_put(Led_B,false); //Desligando o Led Azul.

      ssd1306_fill(&ssd, !cor); // Limpa o display
      ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
      ssd1306_draw_string(&ssd, "DESLIGAMENTO", 20, 10); // Desenha uma string
      ssd1306_draw_string(&ssd, "MANUAL", 40, 20); // Desenha uma string
      ssd1306_draw_string(&ssd, "VIBRACAO MAX: ", 20, 35); // Desenha uma string
      ssd1306_draw_string(&ssd, valor_vibracao, 30, 50); //Desenhado no display.
      ssd1306_send_data(&ssd);
      sleep_ms(200);

    }

    if (!sistema) { 
      sleep_ms(100); // Pequena pausa para evitar loop infinito
      continue;      // Aguarda até que sistema seja reativado pelo botão A
  }
    

    
  }

  sleep_ms(200);
}