#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int input_fd) __attribute__((noreturn));

void
primes(int input_fd)
{
  int prime, n;
  int p[2];
  
  if(read(input_fd, &prime, sizeof(int)) != sizeof(int)){
    close(input_fd);
    exit(0);
  }
  
  printf("prime %d\n", prime);
  
  if(pipe(p) < 0){
    fprintf(2, "primes: pipe failed\n");
    exit(1);
  }
  
  int pid = fork();
  if(pid < 0){
    fprintf(2, "primes: fork failed\n");
    exit(1);
  }
  
  if(pid == 0){
    close(p[1]); 
    close(input_fd); 
    primes(p[0]); 
    close(p[0]);
    exit(0);
  } else {
    close(p[0]);
    
    while(read(input_fd, &n, sizeof(int)) == sizeof(int)){
      if(n % prime != 0){
        write(p[1], &n, sizeof(int));
      }
    }
    
    close(p[1]);
    close(input_fd);
    wait(0); 
    exit(0);
  }
}

int
main(int argc, char *argv[])
{
  int p[2];
  
  if(pipe(p) < 0){
    fprintf(2, "primes: pipe failed\n");
    exit(1);
  }
  
  int pid = fork();
  if(pid < 0){
    fprintf(2, "primes: fork failed\n");
    exit(1);
  }
  
  if(pid == 0){
    close(p[1]);
    primes(p[0]);
    close(p[0]);
    exit(0);
  } else {
    close(p[0]); 
    
    for(int i = 2; i <= 280; i++){
      write(p[1], &i, sizeof(int));
    }
    
    close(p[1]);
    wait(0); 
    exit(0);
  }
}

