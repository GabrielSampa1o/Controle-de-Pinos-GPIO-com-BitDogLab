#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 21
#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13
#define BUTTON_PIN 5

void configure_pins() {
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Ativa o pull-up interno do botão
}

void turn_off_all_leds() {
    gpio_put(BLUE_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(RED_LED_PIN, 0);
}

void control_leds(int command) {
    turn_off_all_leds();

    if (command == 1) {
        gpio_put(GREEN_LED_PIN, 1);
    } else if (command == 2) {
        gpio_put(BLUE_LED_PIN, 1);
    } else if (command == 3) {
        gpio_put(RED_LED_PIN, 1);
    } else if (command == 4) {
        gpio_put(GREEN_LED_PIN, 1);
        gpio_put(BLUE_LED_PIN, 1);
        gpio_put(RED_LED_PIN, 1);
    } else {
        printf("Comando desconhecido para LEDs\n");
    }
}

void activate_buzzer() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint pwm_slice = pwm_gpio_to_slice_num(BUZZER_PIN);

    pwm_set_clkdiv(pwm_slice, 125.0);
    pwm_set_wrap(pwm_slice, 255);
    pwm_set_gpio_level(BUZZER_PIN, 150);
    pwm_set_enabled(pwm_slice, true);

    sleep_ms(2000);

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
    int button_state = 0;
    int last_button_state = 1; // Botão começa como "não pressionado"
    int led_mode = 0; // Estado atual dos LEDs

    printf("Digite um comando (GREEN, BLUE, RED, WHITE, BUZZER, OFF) ou pressione o botão:\n");

    while (1) {
        // Verifica o botão
        button_state = gpio_get(BUTTON_PIN);

        if (button_state == 0 && last_button_state == 1) {
            // Botão foi pressionado
            led_mode = (led_mode + 1) % 5; // Alterna entre os modos (0 a 4)
            control_leds(led_mode);
            printf("Botão pressionado. Modo LED: %d\n", led_mode);

            if (led_mode == 0) {
                printf("Todos os LEDs foram apagados\n");
            }

            sleep_ms(200); // Debounce
        }

        last_button_state = button_state;

        // Comando via console
        if (scanf("%19s", user_input) == 1) {
            int command = map_command(user_input);

            if (command == 1 || command == 2 || command == 3 || command == 4) {
                control_leds(command);
                printf("LED ativado: %s\n", user_input);
            } else if (command == 5) {
                activate_buzzer();
                printf("Buzzer ativado\n");
            } else if (command == 6) {
                turn_off_all_leds();
                printf("Todos os LEDs foram apagados\n");
            } else {
                printf("Comando desconhecido\n");
            }
        }

        sleep_ms(100); // Aguarda antes de processar o próximo comando
    }
}
