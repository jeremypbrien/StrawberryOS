#ifndef _MM_H
#define _MM_H

#define LOW_MEMORY (0x400000)
#define HIGH_MEMORY (0x40000000)
#define PAGING_MEMORY (HIGH_MEMORY - LOW_MEMORY)

#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define NUM_PAGES (PAGING_MEMORY / PAGE_SIZE)


#ifndef __ASSEMBLER__

unsigned long get_free_page();
void free_page(unsigned long page);

#endif /* __ASSEMBLER__ */

#endif  /*_MM_H */
