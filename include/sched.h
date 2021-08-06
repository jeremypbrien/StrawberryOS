#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#define THREAD_CPU_CONTEXT 0 // offset of cpu_context in task_struct 

#ifndef __ASSEMBLER__

#define MAX_TASKS (64)

extern struct task_struct *current;
extern struct task_struct *tasks[MAX_TASKS];
extern unsigned int num_tasks;

struct cpu_context {
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    unsigned long fp;
    unsigned long sp;
    unsigned long pc;
};

enum process_state {
    READY,
    WAITING,
    RUNNING,
    STOPPED,
};

struct task_struct {
    struct cpu_context cpu_context;
    enum process_state state;
    long counter;
    long priority;
    long preempt_count;
};

void scheduler_timer_tick(void);
void switch_to(struct task_struct *next);
void yield_cpu(void);
extern void cpu_switch_to(struct task_struct *prev, struct task_struct *next);
extern void preempt_disable(void);
extern void preempt_enable(void);

#endif /* __ASSEMBLER__ */

#endif /* _SCHEDULE_H */
