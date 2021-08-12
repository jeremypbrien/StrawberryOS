#include "shell.h"
#include "drivers/mini_uart.h"
#include "printf.h"

#define PROMPT "[StrawberryOS]$ "
#define MAX_LINE_SIZE 64

char line_buffer[MAX_LINE_SIZE];


unsigned int get_line() {
    unsigned int line_len = 0;
    unsigned int cursor_index = 0;
    while (1) {
        char c = uart_recv();

        if (c >= 32) { /* printable character */
            printf("%c", c);
            line_buffer[line_len++] = c;
            cursor_index++;
        } else if (c == 10 || c == 13) { /* CRLF */
            line_buffer[line_len] = 0;
            return line_len;
        } else if (c == 27) { /* Escape sequence */
            char c2 = uart_recv();
            char c3 = uart_recv();

            if (c2 == 91 && c3 == 65) { /* Up arrow */
                printf("UP");
            } else if (c2 == 91 && c3 == 66) { /* Down arrow */
                printf("DOWN");
            } else if (c2 == 91 && c3 == 67) { /* Right arrow */
                printf("RIGHT");
            } else if (c2 == 91 && c3 == 68) { /* Left arrow */
                printf("LEFT");
            }       
        } else if (c == 8) { /* Backspace */
            if (cursor_index > 0) {
                printf("%c %c", 8, 8);
                line_buffer[--line_len] = 0; /* Erase character */
                cursor_index--;
            }
        }

        /* Prevent buffer overflow */
        if (line_len == MAX_LINE_SIZE - 1) {
            line_buffer[line_len] = 0;
            return line_len;
        }
    } /* end while */
}

void prompt(void) {
    printf(PROMPT);
}

void start_shell(void)
{
    while (1) {
        /* Get command */
        prompt();
        get_line();
        printf("\r\n");

        /* Process command */
        // TODO
    } /* end while */
}