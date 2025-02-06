#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdio.h>
#include "pico/stdlib.h"

// Configurações dos botões
#define BOTAO_A 5      // Pino do Botão A
#define BOTAO_B 6      // Pino do Botão B

// Tempo mínimo entre interrupções para debouncing
#define DEBOUNCE_DELAY 300  // Milissegundos

// Protótipos das funções
void iniciar_botoes(void);
void debounce_botao(uint pino, volatile uint32_t *last_irq_time);
void botao_callback(uint gpio, uint32_t eventos);

#endif  // BUTTONS_H
