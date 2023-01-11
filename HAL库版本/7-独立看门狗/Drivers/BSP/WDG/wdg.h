#ifndef __WDG_H
#define __WDG_H

#include "./SYSTEM/sys/sys.h"


void iwdg_init(uint8_t prer, uint16_t rlr);
void iwdg_feed(void);

#endif
