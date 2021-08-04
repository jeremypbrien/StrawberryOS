#include "rpi4.h"
#include "mini_uart.h"
#include "utils.h"


void uart_send(char c)
{
    while(1) {
        if(get32(AUX_MU_LSR_REG) & 0x20) 
            break;
    }
    put32(AUX_MU_IO_REG, c);
} /* uart_send() */


char uart_recv(void)
{
    while(1) {
        if(get32(AUX_MU_LSR_REG) & 0x01) 
            break;
    }
    return(get32(AUX_MU_IO_REG) & 0xFF);
} /* uart_recv() */


void uart_send_string(char* str)
{
    for (int i = 0; str[i] != '\0'; i ++) {
        uart_send((char)str[i]);
    }
} /* uart_send_string() */


void uart_init(void)
{
    unsigned int selector;
  
  /* Set GPIO pins for serial: alt5 for gpio 14 and 15 */
    selector = get32(GPFSEL1);
    selector &= ~(7 << 12); // clear gpio14
    selector |= 2 << 12;
    selector &= ~(7 << 15); // clear gpio15
    selector |= 2 << 15;
    put32(GPFSEL1, selector);
  
  /* Configure UART clock */
    put32(GPPUD,0);
    delay(150);
    put32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    put32(GPPUDCLK0, 0);
  
  /* UART settings */
    put32(AUX_ENABLES, 1);                   // Enable mini uart (this also enables access to it registers)
    put32(AUX_MU_CNTL_REG, 0);               // Disable auto flow control and disable receiver and transmitter (for now)
    put32(AUX_MU_IER_REG, 0);                // Disable receive interrupts (TODO: Change in future)
    put32(AUX_MU_LCR_REG, 3);                // Enable 8 bit mode
    put32(AUX_MU_MCR_REG, 0);                // Set RTS line to be always high
    put32(AUX_MU_BAUD_REG, 541);             // Set baud rate to 115200
    put32(AUX_MU_CNTL_REG, 3);               // Finally, enable transmitter and receiver
} /* uart_init() */
