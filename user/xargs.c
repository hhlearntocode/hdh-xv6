#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(2, "Usage: xargs command [args...]\n");
    exit(1);
  }

  char *cmd[MAXARG];
  for(int i = 1; i < argc; i++)
    cmd[i-1] = argv[i];

  char line[512];
  int i = 0;
  char ch;
  while(read(0, &ch, 1) == 1){
    if(ch == '\n'){
      line[i] = 0;
      cmd[argc - 1] = line;
      cmd[argc] = 0;

      if(fork() == 0){
        char path[32];
        path[0] = '/';
        strcpy(path + 1, cmd[0]);
        exec(path, cmd);
        fprintf(2, "exec %s failed\n", cmd[0]);
        exit(1);
      }
      wait(0);
      i = 0;
    } else {
      line[i++] = ch;
    }
  }

  exit(0);
}
