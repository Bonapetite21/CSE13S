#ifndef __SUPPORT_H__
#define __SUPPORT_H__
#include <stdbool.h>
#include <stdint.h>
extern uint32_t moves;
extern uint32_t comparisons;
void guide();
bool less_than(int64_t first, int64_t second);
bool greater_than(int64_t third, int64_t fourth);
void swap(uint32_t *one, uint32_t *two);

#endif
