#include "rpi4.h"
#include "utils.h"
#include "sched.h"
#include "irq.h"

const unsigned int interval = 200000;
unsigned int cur_val = 0;

void timer_init()
{
    cur_val = get32(TIMER_CLO);
    cur_val += interval;
    put32(TIMER_C1, cur_val);
}

void handle_timer_irq( void ) 
{
    cur_val += interval;
    put32(TIMER_C1, cur_val);
    put32(TIMER_CS, TIMER_CS_M1);

    scheduler_timer_tick();
}
