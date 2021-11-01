#ifndef _INFO_H_
#define _INFO_H_

#include <stdlib.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void print_introduction(void);
void print_menu(void);
void efficiency_analysis(unsigned long size);

#endif // _INFO_H_
