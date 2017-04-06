#include <stdio.h>
#include <assert.h>

#include "Tpm.h"
#include "Global.h"

int main(void)
{
  printf("sizeof(PERSISTENT_DATA) = %zd\n", sizeof(PERSISTENT_DATA));
  printf("--------------\n");

  printf("NV_STATE_RESET_DATA = %lu (0x%lx)\n",
         NV_STATE_RESET_DATA,
         NV_STATE_RESET_DATA);
  assert(NV_STATE_RESET_DATA == 0x400);
  printf("sizeof(STATE_RESET_DATA) = %zd\n", sizeof(STATE_RESET_DATA));
  printf("--------------\n");

  printf("NV_STATE_CLEAR_DATA = %lu (0x%lx)\n",
         NV_STATE_CLEAR_DATA,
         NV_STATE_CLEAR_DATA);
  assert(NV_STATE_CLEAR_DATA == 0x800);
  printf("sizeof(STATE_CLEAR_DATA) = %zd\n", sizeof(STATE_CLEAR_DATA));
  printf("--------------\n");

  printf("NV_ORDERLY_DATA = %lu (0x%lx)\n",
         NV_ORDERLY_DATA,
         NV_ORDERLY_DATA);
  assert(NV_ORDERLY_DATA == 0x1000);
  printf("sizeof(ORDERLY_DATA) = %zd\n", sizeof(ORDERLY_DATA));
  printf("--------------\n");

  printf("NV_INDEX_RAM_DATA = %lu (0x%lx)\n",
         NV_INDEX_RAM_DATA,
         NV_INDEX_RAM_DATA);
  assert(NV_INDEX_RAM_DATA == 0x1200);
}
