#include "mm.h"

/* Used to determine whether or not page is free */
static unsigned short mem_map[NUM_PAGES] = {0,};

unsigned long get_free_page()
{
    unsigned int i;
    for (i = 0; i < NUM_PAGES; i++) {
        if (mem_map[i] == 0) {
            mem_map[i] = 1;
            return LOW_MEMORY + (i * PAGE_SIZE);
        } 
    }
    return 0;
}

void free_page(unsigned long page)
{
    mem_map[(page - LOW_MEMORY) / PAGE_SIZE] = 0;
}