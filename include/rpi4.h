#ifndef _RPI4_H
#define _RPI4_H

#define PBASE 0xFE000000

/* GPIO */
#define GPIO_BASE (PBASE + 0x00200000)
#define GPFSEL1   (GPIO_BASE + 0x4)
#define GPSET0    (GPIO_BASE + 0x1C)
#define GPCLR0    (GPIO_BASE + 0x28)
#define GPPUD     (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

/* MINI UART */
#define MINI_UART_BASE (PBASE + 0x00215000)
#define AUX_ENABLES     (MINI_UART_BASE + 0x4)
#define AUX_MU_IO_REG   (MINI_UART_BASE + 0x40)
#define AUX_MU_IER_REG  (MINI_UART_BASE + 0x44)
#define AUX_MU_IIR_REG  (MINI_UART_BASE + 0x48)
#define AUX_MU_LCR_REG  (MINI_UART_BASE + 0x4C)
#define AUX_MU_MCR_REG  (MINI_UART_BASE + 0x50)
#define AUX_MU_LSR_REG  (MINI_UART_BASE + 0x54)
#define AUX_MU_MSR_REG  (MINI_UART_BASE + 0x58)
#define AUX_MU_SCRATCH  (MINI_UART_BASE + 0x5C)
#define AUX_MU_CNTL_REG (MINI_UART_BASE + 0x60)
#define AUX_MU_STAT_REG (MINI_UART_BASE + 0x64)
#define AUX_MU_BAUD_REG (MINI_UART_BASE + 0x68)

/* IRQ */
#define IRQ0_PENDING_0  (PBASE+0x0000B200)
#define IRQ0_PENDING_1  (PBASE+0x0000B204)
#define IRQ0_PENDING_2  (PBASE+0x0000B208)
#define IRQ0_SET_EN_0   (PBASE+0x0000B210)
#define IRQ0_SET_EN_1   (PBASE+0x0000B214)
#define IRQ0_SET_EN_2   (PBASE+0x0000B218)

/* TIMER */
#define SYSTEM_TIMER_IRQ_0    (1 << 0)
#define SYSTEM_TIMER_IRQ_1    (1 << 1)
#define SYSTEM_TIMER_IRQ_2    (1 << 2)
#define SYSTEM_TIMER_IRQ_3    (1 << 3)
#define TIMER_CS              (PBASE+0x00003000)
#define TIMER_CLO             (PBASE+0x00003004)
#define TIMER_CHI             (PBASE+0x00003008)
#define TIMER_C0              (PBASE+0x0000300C)
#define TIMER_C1              (PBASE+0x00003010)
#define TIMER_C2              (PBASE+0x00003014)
#define TIMER_C3              (PBASE+0x00003018)
#define TIMER_CS_M0           (1 << 0)
#define TIMER_CS_M1           (1 << 1)
#define TIMER_CS_M2           (1 << 2)
#define TIMER_CS_M3           (1 << 3)

#endif  /*_RPI4_H */
