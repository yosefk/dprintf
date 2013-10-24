#include <stdio.h>
#include "dprintf.h"

int main()
{
  int i;
  for(i=0; i<10; ++i) {
    dprintf("i=%d i/2=%f %s\n", i, i/2., (i&1)?"odd":"even");
  }
  dflush();
  dprintf("going to crash...\n");
  volatile int* p=0;
  dprintf("i=%d p=0x%x\n", i, (dcell)p);
  p[i]=0;
}
