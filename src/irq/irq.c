#include "rpi4.h"
#include "arm/ivt.h"
#include "utils.h"
#include "printf.h"
#include "drivers/timer.h"

/* Associated error message with ivt.h errors */
const char *vector_entry_error_messages[] = {
    "SYNC_INVALID_EL1t",
    "IRQ_INVALID_EL1t",        
    "FIQ_INVALID_EL1t",        
    "ERROR_INVALID_EL1T",        

    "SYNC_INVALID_EL1h",        
    "IRQ_INVALID_EL1h",        
    "FIQ_INVALID_EL1h",        
    "ERROR_INVALID_EL1h",        

    "SYNC_INVALID_EL0_64",        
    "IRQ_INVALID_EL0_64",        
    "FIQ_INVALID_EL0_64",        
    "ERROR_INVALID_EL0_64",    

    "SYNC_INVALID_EL0_32",        
    "IRQ_INVALID_EL0_32",        
    "FIQ_INVALID_EL0_32",        
    "ERROR_INVALID_EL0_32"    
};

void enable_interrupt_controller()
{
    put32(IRQ0_SET_EN_0, SYSTEM_TIMER_IRQ_1);
}

void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
    printf("%s, ESR: %x, address: %x\r\n", vector_entry_error_messages[type], esr, address);
}

void handle_irq(void)
{
    unsigned int irq = get32(IRQ0_PENDING_0);
    while (irq) {
        if (irq & SYSTEM_TIMER_IRQ_1) {
            handle_timer_irq();
            irq &= ~SYSTEM_TIMER_IRQ_1;
        } else {
            printf("Unknown IRQ: %x\r\n", irq);
            irq = 0;
        }
    } /* end while */
}
