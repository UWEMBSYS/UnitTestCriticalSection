#include <stdlib.h>
#include <stdint.h>
/* Need to add the cmsis header for stm32f401 to get ITM_SendChar */
//#include <stm32f401.h>
//#include <core_cm4.h>


extern void ut_cs(void);

__ATTRIBUTES size_t __write(int h, const unsigned char *c, size_t count)
{
  size_t i=0;
  (void)h;
  
  /* redirect stdout to SWO */
  while (i<count) {
    ITM_SendChar(c[i]);
  }
  return count;
}

int main()
{
  
  ut_cs();
  return 0;
}
