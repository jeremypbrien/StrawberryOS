#include "sched.h"
#include "printf.h"
#include "irq.h"

static struct task_struct init_task = {{0,0,0,0,0,0,0,0,0,0,0,0,0}, RUNNING, 0, 1, 0};
struct task_struct *current_task = &(init_task);
struct task_struct *tasks[MAX_TASKS] = {&(init_task), };
unsigned int num_tasks = 1;

void _schedule(void)
{
    preempt_disable();
    int next;
    int c;
    struct task_struct *p;
    while (1) {
        c = -1;
        next = 0;
        for (int i = 0; i < MAX_TASKS; i++){
            p = tasks[i];
            if (p && p->state == RUNNING && p->counter > c) {
                c = p->counter;
                next = i;
            }
        }
        if (c) {
            break;
        }
        for (int i = 0; i < MAX_TASKS; i++) {
            p = tasks[i];
            if (p) {
                p->counter = (p->counter >> 1) + p->priority;
            }
        }
    }
    switch_to(tasks[next]);
    preempt_enable();
}

void switch_to(struct task_struct *next)
{
    struct task_struct *prev;

    if (current_task == next) {
        return;
    }

    prev = current_task;
    current_task = next;
    cpu_switch_to(prev, next);
}

void yield_cpu(void)
{
    current_task->counter = 0;
    _schedule();
}

void scheduler_timer_tick(void) {
    current_task->counter--;

    /* Don't context switch if task still has cpu time reversed or preempt is disabled for process */
    if (current_task->counter > 0 || current_task->preempt_count > 0) {
        return;
    }

    /* Must enable interrupts during scheduler as interrupt won't
     * return until context switch results in returning to process that was
     * running when initial interrupt occured
     */
    enable_irq();
    _schedule();
    disable_irq();
}

void preempt_disable(void)
{
    current_task->preempt_count++;
}

void preempt_enable(void)
{
    current_task->preempt_count--;
}
