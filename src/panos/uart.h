#ifndef PANOS_UART_H
#define PANOS_UART_H

/**
 * @author      Benno Zeeman
 * @brief       UART functions
 * @copyright   The MIT License (MIT)
 * @date        2014
 * @version     1.0
 */

void panos_uart_init(void);
void panos_uart_char(char c);
void panos_uart_string(const char *str);
void panos_uart_int(int num, int base);

#endif
