#include <stdio.h>
#include <assert.h>

#define NV_C
#include "Tpm.h"

int main(void)
{
  printf("sizeof(PERSISTENT_DATA) = %zd\n", sizeof(PERSISTENT_DATA));
  printf("available space = %ld\n",
         NV_STATE_RESET_DATA - sizeof(PERSISTENT_DATA));
  printf("--------------\n");

  printf("NV_STATE_RESET_DATA = %lu (0x%lx)\n",
         NV_STATE_RESET_DATA,
         NV_STATE_RESET_DATA);
  assert(NV_STATE_RESET_DATA == 0x400);
  printf("sizeof(STATE_RESET_DATA) = %zd\n", sizeof(STATE_RESET_DATA));
  printf("available space = %ld\n",
         NV_STATE_CLEAR_DATA - sizeof(STATE_RESET_DATA) - NV_STATE_RESET_DATA);
  printf("--------------\n");

  printf("NV_STATE_CLEAR_DATA = %lu (0x%lx)\n",
         NV_STATE_CLEAR_DATA,
         NV_STATE_CLEAR_DATA);
  assert(NV_STATE_CLEAR_DATA == 0x800);
  printf("sizeof(STATE_CLEAR_DATA) = %zd\n", sizeof(STATE_CLEAR_DATA));
  printf("available space = %ld\n",
         NV_ORDERLY_DATA - sizeof(STATE_CLEAR_DATA) - NV_STATE_CLEAR_DATA);
  printf("--------------\n");

  printf("NV_ORDERLY_DATA = %lu (0x%lx)\n",
         NV_ORDERLY_DATA,
         NV_ORDERLY_DATA);
  assert(NV_ORDERLY_DATA == 0x1000);
  printf("sizeof(ORDERLY_DATA) = %zd\n", sizeof(ORDERLY_DATA));
  printf("available space = %ld\n",
         NV_INDEX_RAM_DATA - sizeof(ORDERLY_DATA) - NV_ORDERLY_DATA);
  printf("--------------\n");

  printf("NV_INDEX_RAM_DATA = %lu (0x%lx)\n",
         NV_INDEX_RAM_DATA,
         NV_INDEX_RAM_DATA);
  printf("sizeof(s_indexOrderlyRam) = %zd\n", sizeof(s_indexOrderlyRam));
  printf("available space = %ld\n",
         NV_USER_DYNAMIC - NV_INDEX_RAM_DATA);
  assert(NV_INDEX_RAM_DATA == 0x1200);
  printf("--------------\n");

  printf("NV_USER_DYNAMIC = %lu (0x%lx)\n",
         NV_USER_DYNAMIC,
         NV_USER_DYNAMIC);
  printf("available space = %ld\n",
         NV_USER_DYNAMIC_END - NV_USER_DYNAMIC);
  assert(NV_USER_DYNAMIC == 0x1400);

  return 0;
}
