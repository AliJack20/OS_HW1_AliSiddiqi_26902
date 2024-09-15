#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Usage: countsyscalls <program>\n");
        exit(1);
    }
    int pid = fork();
    if (pid < 0) {
        
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        
        exec(argv[1], argv + 1);

        
        printf("Execution failed\n");
        exit(1);
    } else {
        wait(0);
        int syscalls = getreadcount();

        
        printf("System calls used by %s: %d\n", argv[1], syscalls);
    }

    
    exit(0);
}
