#include "uart.h"
#include <stdint.h>

#define CMD_BUFFER_SIZE 64


int str_cmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int str_starts_with(const char *str, const char *prefix) {
    while (*prefix) {
        if (*prefix++ != *str++) return 0;
    }
    return 1;
}

void process_command(char *cmd) {
    if (str_cmp(cmd, "help") == 0) {
        uart_puts("Desteklenen komutlar:\n");
        uart_puts("  help    : Bu yardim ekranini listeler\n");
        uart_puts("  status  : Sistem donanim ve cekirdek durumunu gosterir\n");
        uart_puts("  clear   : Terminal ekranini temizler\n");
        uart_puts("  echo <m>: Girdiginiz metni ekrana geri yazar\n");
    } 
    else if (str_cmp(cmd, "status") == 0) {
        uart_puts("[SISTEM DURUMU]\n");
        uart_puts("  Cekirdek : ARM Cortex-M3 (LM3S6965 Emulation)\n");
        uart_puts("  Flash    : 256 KB (0x00000000)\n");
        uart_puts("  SRAM     : 64 KB  (0x20000000)\n");
        uart_puts("  Haberlesme: UART0 (115200 Baud, Polling Mode)\n");
        uart_puts("  Durum    : Calisiyor (Bare-Metal, OS yok)\n");
    } 
    else if (str_cmp(cmd, "clear") == 0) {
        uart_puts("\033[2J\033[H");
    } 
    else if (str_starts_with(cmd, "echo ")) {
        uart_puts(&cmd[5]);
        uart_puts("\n");
    } 
    else if (cmd[0] != '\0') {
        uart_puts("Bilinmeyen komut: '");
        uart_puts(cmd);
        uart_puts("'. Yardim icin 'help' yaziniz.\n");
    }
}

int main(void) {
    uart_init();
    uart_puts("\033[2J\033[H");
    uart_puts("=====================================================\n");
    uart_puts("    Bare-Metal ARM Cortex-M3 Terminal Kabugu (CLI)   \n");
    uart_puts("    QEMU LM3S6965 - No OS, No Standard Libraries     \n");
    uart_puts("=====================================================\n\n");
    uart_puts("Komut girmek icin 'help' yazip Enter'a basiniz.\n\n");

    char buffer[CMD_BUFFER_SIZE];
    uint32_t index = 0;

    uart_puts("baremetal> ");

    while (1) {
        char c = uart_getc();

        if (c == '\r' || c == '\n') {
            uart_puts("\n");
            buffer[index] = '\0'; 
            process_command(buffer);
            index = 0;
            uart_puts("baremetal> ");
        }
        else if (c == '\b' || c == 0x7F) {
            if (index > 0) {
                index--;
                uart_puts("\b \b");
            }
        }
       
        else {
            if (index < CMD_BUFFER_SIZE - 1) {
                buffer[index++] = c;
                uart_putc(c); 
            }
        }
    }

    return 0;
}