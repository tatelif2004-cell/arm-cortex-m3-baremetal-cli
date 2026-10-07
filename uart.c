#include "uart.h"

void uart_init(void) {
    
}

void uart_putc(char c) {
    while (UART0_FR & UART_FR_TXFF);
    UART0_DR = c;
}

void uart_puts(const char *str) {
    while (*str) {
        if (*str == '\n') {
            uart_putc('\r');
        }
        uart_putc(*str++);
    }
}

char uart_getc(void) {
    while (UART0_FR & UART_FR_RXFE);
    return (char)(UART0_DR & 0xFF);
}