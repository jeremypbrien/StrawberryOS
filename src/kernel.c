#include "mini_uart.h"
#include "printf.h"
#include "utils.h"


void kernel_main(void)
{
  uart_init();
  printf("UART Initialized\r\n");
  printf("Current Exception Level: %d\r\n", get_el());
  
  printf("Entering loopback\r\n");
  while (1) {
    uart_send(uart_recv());
  }
} /* kernel_main() */
