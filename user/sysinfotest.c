#include "kernel/types.h"
#include "kernel/riscv.h"
#include "user/user.h"

void
sinfo(struct sysinfo *info) {
  if (sysinfo(info) < 0) {
    printf("sysinfo failed\n");
    exit(1);
  }
}

int
main(int argc, char *argv[])
{
  struct sysinfo info;
  printf("sysinfotest: start\n");
  sinfo(&info);

  printf("  free memory: %ld bytes\n", info.freemem);
  printf("  nproc: %ld\n", info.nproc);

  if (info.load_avg >= 10)
    printf("Load Average: %ld.%ld\n", info.load_avg / 100, info.load_avg % 100);
  else 
    printf("Load Average: %ld.0%ld\n", info.load_avg / 100, info.load_avg % 100);

  printf("sysinfotest: OK\n");
  exit(0);
}