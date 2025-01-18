#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define LED_VERDE 13

//mapa de teclas
char KEY_MAP[16] = {
    '1', '2' , '3', 'A',
    '4', '5' , '6', 'B',
    '7', '8' , '9', 'C',
    '*', '0' , '#', 'D'
};

//define os pinos do teclado com as portas GPIO
uint columns[4] = {4, 3, 2, 1}; 
uint rows[4] = {8, 7, 6, 5};


// Função para inicializar o teclado
void init_teclado() {
    // Configura as colunas como saída
    for (int i = 0; i < 4; i++) {
        gpio_init(columns[i]);  //inicializa as colunas
        gpio_set_dir(columns[i], GPIO_OUT); // coloca as colunas como saída 
        gpio_put(columns[i], 1); // Inicializa como HIGH = alto (1)
    }

    // Configura as linhas como entrada com pull-up
    for (int i = 0; i < 4; i++) {
        gpio_init(rows[i]); // inicializa as linhas
        gpio_set_dir(rows[i], GPIO_IN); // coloca as linhas como entrada 
        gpio_pull_up(rows[i]);
    }
}

// Função para verificar teclas pressionadas
char detectar_tecla() {
    for (int col = 0; col < 4; col++) {
        // Ativa a coluna atual
        gpio_put(columns[col], 0);

        // Verifica as linhas
        for (int row = 0; row < 4; row++) {
            if (gpio_get(rows[row]) == 0) { // Tecla pressionada
                // Desativa a coluna antes de retornar
                gpio_put(columns[col], 1);
                return KEY_MAP[row * 4 + col];
            }
        }

        // Desativa a coluna atual
        gpio_put(columns[col], 1);
    }

    // Nenhuma tecla pressionada
    return '\0';
}

int main() {
    stdio_init_all();

    // Inicializa o teclado
    init_teclado();

    printf("Teclado inicializado.\n");

    char tecla;

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    while (true) {
        // Detecta a tecla pressionada
        gpio_put(LED_VERDE, 0); //mantém led verde desligado
        tecla = detectar_tecla();
        if (tecla != '\0') {
          printf("Tecla pressionada: %c\n", tecla);
          if(tecla == 'A'){
            gpio_put(LED_VERDE, 1);
            printf("led verde ligado\n");
          }
        }

        sleep_ms(100);
    }
}