#ifndef ANIM_H
#define ANIM_H

#define NUM_PIXELS 25 // A matriz de Led 5x5

bool led_buffer[NUM_PIXELS]; //Armazinar o Número de Pixels
volatile int indice_animacao = 0; //Inicia animação apresentando o 0.



void caso_inicial() //Animação para o número 0.
{
          // Configura todos os LEDs como desligados
          for (int i = 0; i < NUM_PIXELS; i++) {
            led_buffer[i] = false;
        }
    
        // Liga os LEDs extremos na cor verde
        led_buffer[0] = true;  //DIAGONAL DE BAIXO - DIREITA

        led_buffer[1] = true; 
        led_buffer[2] = true;   //PARTE DE BAIXO
        led_buffer[3] = true; 

        led_buffer[4] = true;  //DIAGONAL DE BAIXO - ESQUERDA
        
        led_buffer[5] = true;  
        led_buffer[14] = true; //CANTO ESQUERDO
        led_buffer[15] = true; 

        led_buffer[9] = true; 
        led_buffer[10] = true; //CANTO DIREITO
        led_buffer[19] = true; 
        
        
        led_buffer[20] = true; // DIAGONAL DE CIMA - ESQUERDA

        led_buffer[21] = true; 
        led_buffer[22] = true; // PARTE DE CIMA
        led_buffer[23] = true; 

        led_buffer[24] = true; // DIGONAL DE CIMA - DIREITA
}


void caso_x_medio() //Animação para o número 2.
{
          // Configura todos os LEDs como desligados
          for (int i = 0; i < NUM_PIXELS; i++) {
            led_buffer[i] = false;
        }
    
        // Liga os LEDs extremos na cor verde
        led_buffer[0] = false;  //DIAGONAL DE BAIXO - DIREITA

        led_buffer[1] = false; 
        led_buffer[2] = false;   //PARTE DE BAIXO
        led_buffer[3] = false; 

        led_buffer[4] = false;  //DIAGONAL DE BAIXO - ESQUERDA
        
        led_buffer[5] = true;  
        led_buffer[14] = true; //CANTO ESQUERDO
        led_buffer[15] = true; 

        led_buffer[9] = true; 
        led_buffer[10] = true; //CANTO DIREITO
        led_buffer[19] = true; 
        
        
        led_buffer[20] = false; // DIAGONAL DE CIMA - ESQUERDA

        led_buffer[21] = false; 
        led_buffer[22] = false; // PARTE DE CIMA
        led_buffer[23] = false; 

        led_buffer[24] = false; // DIGONAL DE CIMA - DIREITA
}

void caso_x_extremo() //Animação para o número 2.
{
          // Configura todos os LEDs como desligados
          for (int i = 0; i < NUM_PIXELS; i++) {
            led_buffer[i] = false;
        }
    
        // Liga os LEDs extremos na cor verde
        led_buffer[0] = false;  //DIAGONAL DE BAIXO - DIREITA

        led_buffer[1] = false; 
        led_buffer[2] = false;   //PARTE DE BAIXO
        led_buffer[3] = false; 

        led_buffer[4] = false;  //DIAGONAL DE BAIXO - ESQUERDA
        
        led_buffer[5] = true;  
        led_buffer[14] = true; //CANTO ESQUERDO
        led_buffer[15] = true; 

        led_buffer[9] = true; 
        led_buffer[10] = true; //CANTO DIREITO
        led_buffer[19] = true; 
        
        
        led_buffer[20] = false; // DIAGONAL DE CIMA - ESQUERDA

        led_buffer[21] = false; 
        led_buffer[22] = false; // PARTE DE CIMA
        led_buffer[23] = false; 

        led_buffer[24] = false; // DIGONAL DE CIMA - DIREITA
}

void caso_y_medio() //Animação para o número 2.
{
          // Configura todos os LEDs como desligados
          for (int i = 0; i < NUM_PIXELS; i++) {
            led_buffer[i] = false;
        }
    
        // Liga os LEDs extremos na cor verde
        led_buffer[0] = false;  //DIAGONAL DE BAIXO - DIREITA

        led_buffer[1] = true; 
        led_buffer[2] = true;   //PARTE DE BAIXO
        led_buffer[3] = true; 

        led_buffer[4] = false;  //DIAGONAL DE BAIXO - ESQUERDA
        
        led_buffer[5] = false;  
        led_buffer[14] = false; //CANTO ESQUERDO
        led_buffer[15] = false; 

        led_buffer[9] = false; 
        led_buffer[10] = false; //CANTO DIREITO
        led_buffer[19] = false; 
        
        
        led_buffer[20] = false; // DIAGONAL DE CIMA - ESQUERDA

        led_buffer[21] = true; 
        led_buffer[22] = true; // PARTE DE CIMA
        led_buffer[23] = true; 

        led_buffer[24] = false; // DIGONAL DE CIMA - DIREITA
}

void caso_y_extremo() //Animação para o número 2.
{
          // Configura todos os LEDs como desligados
          for (int i = 0; i < NUM_PIXELS; i++) {
            led_buffer[i] = false;
        }
    
        // Liga os LEDs extremos na cor verde
        led_buffer[0] = false;  //DIAGONAL DE BAIXO - DIREITA

        led_buffer[1] = true; 
        led_buffer[2] = true;   //PARTE DE BAIXO
        led_buffer[3] = true; 

        led_buffer[4] = false;  //DIAGONAL DE BAIXO - ESQUERDA
        
        led_buffer[5] = false;  
        led_buffer[14] = false; //CANTO ESQUERDO
        led_buffer[15] = false; 

        led_buffer[9] = false; 
        led_buffer[10] = false; //CANTO DIREITO
        led_buffer[19] = false; 
        
        
        led_buffer[20] = false; // DIAGONAL DE CIMA - ESQUERDA

        led_buffer[21] = true; 
        led_buffer[22] = true; // PARTE DE CIMA
        led_buffer[23] = true; 

        led_buffer[24] = false; // DIGONAL DE CIMA - DIREITA
}

void caso_xy_medio() //Animação para o número 2.
{
          // Configura todos os LEDs como desligados
          for (int i = 0; i < NUM_PIXELS; i++) {
            led_buffer[i] = false;
        }
    
        // Liga os LEDs extremos na cor verde
        led_buffer[0] = true;  //DIAGONAL DE BAIXO - DIREITA

        led_buffer[1] = true; 
        led_buffer[2] = false;   //PARTE DE BAIXO
        led_buffer[3] = true; 

        led_buffer[4] = true;  //DIAGONAL DE BAIXO - ESQUERDA
        
        led_buffer[5] = true;  
        led_buffer[14] = false; //CANTO ESQUERDO
        led_buffer[15] = true; 

        led_buffer[9] = true; 
        led_buffer[10] = false; //CANTO DIREITO
        led_buffer[19] = true; 
        
        
        led_buffer[20] = true; // DIAGONAL DE CIMA - ESQUERDA

        led_buffer[21] = true; 
        led_buffer[22] = false; // PARTE DE CIMA
        led_buffer[23] = true; 

        led_buffer[24] = true; // DIGONAL DE CIMA - DIREITA
}

void caso_xy_extremo() //Animação para o número 2.
{
          // Configura todos os LEDs como desligados
          for (int i = 0; i < NUM_PIXELS; i++) {
            led_buffer[i] = false;
        }
    
        // Liga os LEDs extremos na cor verde
        led_buffer[0] = true;  //DIAGONAL DE BAIXO - DIREITA

        led_buffer[1] = true; 
        led_buffer[2] = false;   //PARTE DE BAIXO
        led_buffer[3] = true; 

        led_buffer[4] = true;  //DIAGONAL DE BAIXO - ESQUERDA
        
        led_buffer[5] = true;  
        led_buffer[14] = false; //CANTO ESQUERDO
        led_buffer[15] = true; 

        led_buffer[9] = true; 
        led_buffer[10] = false; //CANTO DIREITO
        led_buffer[19] = true; 
        
        
        led_buffer[20] = true; // DIAGONAL DE CIMA - ESQUERDA

        led_buffer[21] = true; 
        led_buffer[22] = false; // PARTE DE CIMA
        led_buffer[23] = true; 

        led_buffer[24] = true; // DIGONAL DE CIMA - DIREITA
}



#endif