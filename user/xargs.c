#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define stdin 0
#define stdout 1
#define stderr 2

#define MAX_ARG_LEN 1024

int 
main(int argc, char *argv[]){
    int n, buf_index = 0;
    char buf, arg[MAX_ARG_LEN], * args[MAXARG];

    if(argc < 2){
        fprintf(stderr, "usage: xargs <command> ...\n");
        exit(0);
    }

    for (int i = 1; i < argc; ++i){
        args[i - 1] = argv[i];
    }

    while((n=read(stdin, &buf, sizeof(buf)))>0){
        if(buf=='\n'){
            arg[buf_index] = 0;

            if(fork()==0){
                args[argc - 1] = arg;
                args[argc] = 0;
                exec(args[0], args);
            }else{
                wait(0);
                buf_index = 0;
            }
        }else{
            arg[buf_index++] = buf;
        }
    }
    exit(0);
}
