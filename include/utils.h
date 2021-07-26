#ifndef	_UTILS_H
#define	_UTILS_H

extern void delay(unsigned long);
extern void put32(unsigned long, unsigned int);
extern unsigned int get32 (unsigned long);
extern void memzero(unsigned long src, unsigned long n);
extern int get_el(void);

#endif  /*_UTILS_H */
