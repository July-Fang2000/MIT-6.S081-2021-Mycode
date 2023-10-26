#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
sieve(int pipes[2])
{
    int p;
    read(pipes[0], &p, sizeof(p));
    if(p==-1){
        exit(0);
    }
    printf("prime %d\n", p);

    int input_pipe[2];
    pipe(input_pipe);

    if (fork() != 0) {
      close(input_pipe[0]);
      int buf;
      while(read(pipes[0], &buf, sizeof(buf)) && buf !=-1){
          if (buf % p != 0)
          {
              write(input_pipe[1], &buf, sizeof(buf));
          }
      }
      buf = -1;
      write(input_pipe[1], &buf, sizeof(buf));
      wait(0);
      exit(0);
    }
    else
    {
      close(input_pipe[1]);
      close(pipes[0]);
      sieve(input_pipe);
    }
}

int
main(int argc, char *argv[])
{
    int input_pipe[2];
    pipe(input_pipe);

    if(fork()!=0){
        close(input_pipe[0]);
        for (int i = 2; i <= 35; ++i){
            write(input_pipe[1], &i, sizeof(i));
        }
        int i = -1;
        write(input_pipe[1], &i, sizeof(i));
    }else{
        close(input_pipe[1]);
        sieve(input_pipe);
        exit(0);
    }
    wait(0);
    exit(0);
}