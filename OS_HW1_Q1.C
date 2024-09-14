#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int p1[2], p2[2];    
    char buf[2];         
    int pid;

    
    pipe(p1);  
    pipe(p2);  

    pid = fork();  

    if (pid < 0) {
        
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        
        for (int i = 0; i < 10; i++) {
            
            read(p1[0], buf, 1);
            buf[1] = '\0';  
            printf("%d: received ping %s\n", getpid(), buf);

            
            buf[0] += 1;
            write(p2[1], buf, 1);
        }
        exit(0);
    } else {
        
        buf[0] = 'A';  
        buf[1] = '\0'; 

        for (int i = 0; i < 5; i++) {
            
            write(p1[1], buf, 1);

            
            read(p2[0], buf, 1);
            buf[1] = '\0';  
            printf("%d: received pong %s\n", getpid(), buf);
        }
        
        wait(0);
        exit(0);
    }
}
