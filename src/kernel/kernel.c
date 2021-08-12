#include "printf.h"
#include "utils.h"
#include "irq.h"
#include "drivers/timer.h"
#include "drivers/mini_uart.h"
#include "sched.h"
#include "shell.h"


void kernel_main(void)
{   
    /* Initialize drivers */
    uart_init();
    timer_init();

    /* Enable interrupts */
    irq_vector_init();
    enable_interrupt_controller();
    enable_irq();

    /* Init process will be the shell process which doesn't return */
    start_shell();

    /* Should never get here */
    while (1);
} /* kernel_main() */
