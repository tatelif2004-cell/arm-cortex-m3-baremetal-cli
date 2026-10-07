#ifndef UART_H
#define UART_H

#include <stdint.h>
#define UART0_BASE   0x4000C000
#define UART0_DR     (*(volatile uint32_t *)(UART0_BASE + 0x000))
#define UART0_FR     (*(volatile uint32_t *)(UART0_BASE + 0x018))


#define UART_FR_TXFF (1 << 5) 
#define UART_FR_RXFE (1 << 4) 


void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *str);
char uart_getc(void);

#endif