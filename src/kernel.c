#include "printf.h"
#include "utils.h"
#include "irq.h"
#include "drivers/timer.h"
#include "drivers/mini_uart.h"


void kernel_main(void)
{   
    /* Initialize drivers */
    uart_init();
    timer_init();

    /* Enable interrupts */
    irq_vector_init();
    enable_interrupt_controller();
    enable_irq();

    printf("StrawberryOS booted!\r\n");
    printf("Current exception level: %d\r\n", get_el());
    
    /* For now hang indefinitely */
    while (1) {
    }
} /* kernel_main() */
