#include "kernel/types.h"
#include "kernel/riscv.h"
#include "user/user.h"

int
main(void)
{
  struct sysinfo info;

  if (sysinfo(&info) < 0) {
    printf("sysinfo failed\n");
    exit(1);
  }

  printf("sysinfo:\n");
  printf("  free memory: %ld bytes\n", info.freemem);
  printf("  nproc: %ld\n", info.nproc);
}