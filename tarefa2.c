#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 21
#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13

void configure_pins() {
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void turn_off_all_leds() {
    // Garante que todos os LEDs estão apagados
    gpio_put(BLUE_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(RED_LED_PIN, 0);
}

void control_leds(char command) {
    // Apaga todos os LEDs antes de acender o solicitado
    turn_off_all_leds();

    if (command == 1) {
        // Liga o LED verde
        gpio_put(GREEN_LED_PIN, 1);
    } else if (command == 2) {
        // Liga o LED azul
        gpio_put(BLUE_LED_PIN, 1);
    } else if (command == 3) {
        // Liga o LED vermelho
        gpio_put(RED_LED_PIN, 1);
    } else if (command == 4) {
        // Liga todos os LEDs
        gpio_put(RED_LED_PIN, 1);
        gpio_put(GREEN_LED_PIN, 1);
        gpio_put(BLUE_LED_PIN, 1);
    } else {
        printf("Comando desconhecido para LEDs\n");
    }
}

void activate_buzzer() {
    // Configura o pino do buzzer para gerar sinal PWM
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint pwm_slice = pwm_gpio_to_slice_num(BUZZER_PIN);

    // Define os parâmetros do PWM para ajustar a frequência e intensidade
    pwm_set_clkdiv(pwm_slice, 125.0);
    pwm_set_wrap(pwm_slice, 255);
    pwm_set_gpio_level(BUZZER_PIN, 150);
    pwm_set_enabled(pwm_slice, true);

    // Mantém o buzzer ativo por 2 segundos
    sleep_ms(2000);

    // Desativa o PWM do buzzer
    pwm_set_enabled(pwm_slice, false);
}

int map_command(const char *input) {
    if (strcmp(input, "GREEN") == 0)
        return 1;
    if (strcmp(input, "BLUE") == 0)
        return 2;
    if (strcmp(input, "RED") == 0)
        return 3;
    if (strcmp(input, "WHITE") == 0)
        return 4;
    if (strcmp(input, "BUZZER") == 0)
        return 5;
    if (strcmp(input, "OFF") == 0)
        return 6;
    return 0;
}

int main() {
    stdio_init_all();
    configure_pins();

    char user_input[20];

    printf("Digite um comando (GREEN, BLUE, RED, WHITE, BUZZER, OFF): \n");

    while (1) {
        scanf("%19s", user_input);

        int command = map_command(user_input);

        if (command == 1 || command == 2 || command == 3 || command == 4) {
            // Controla os LEDs com base no comando recebido
            control_leds(command);
            printf("LED ativado: %s\n", user_input);
        } else if (command == 5) {
            // Ativa o buzzer por 2 segundos
            activate_buzzer();
            printf("Buzzer ativado\n");
        } else if (command == 6) {
            // Desliga todos os LEDs
            turn_off_all_leds();
            printf("Todos os LEDs foram apagados\n");
        } else {
            // Informa que o comando digitado é inválido
            printf("Comando desconhecido\n");
        }

        sleep_ms(100); // Aguarda um curto período antes de processar o próximo comando
    }
}
