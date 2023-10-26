#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int n = argc;
    if(n < 2){
        printf("No parameter pass, error!\n");
        exit(1);
    }
    int times = atoi(argv[1]);
    sleep(times);
    exit(0);
}