#include "buttons.h"
#include "rgb.h"  // Para acionar os LEDs via state()
#define BOTAO_A 5      // Pino do Botão A
#define BOTAO_B 6      // Pino do Botão B
volatile uint32_t last_irq_time_A = 0;
volatile uint32_t last_irq_time_B = 0;

void debounce_botao(uint pino, volatile uint32_t *last_irq_time) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());
    if (tempo_atual - *last_irq_time > DEBOUNCE_DELAY) {
        *last_irq_time = tempo_atual;

        if (pino == BOTAO_A) {
            state(1, 0, 0);  // LED vermelho aceso
        }
        if (pino == BOTAO_B) {
            state(0, 1, 0);  // LED verde aceso
        }
    }
}

void iniciar_botoes(void) {
    gpio_init(BOTAO_A);
    gpio_init(BOTAO_B);

    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_set_dir(BOTAO_B, GPIO_IN);

    gpio_pull_up(BOTAO_A);
    gpio_pull_up(BOTAO_B);

    // Configura as interrupções com callback para os botões
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &botao_callback);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &botao_callback);
}

void botao_callback(uint gpio, uint32_t eventos) {
    if (gpio == BOTAO_A) {
        debounce_botao(BOTAO_A, &last_irq_time_A);
    } else if (gpio == BOTAO_B) {
        debounce_botao(BOTAO_B, &last_irq_time_B);
    }
}
