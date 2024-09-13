#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    int p1[2], p2[2];  // Two pipes: p1 for parent to child, p2 for child to parent
    char buffer[1];
    int pid;
    
    // Create both pipes
    pipe(p1);  // p1[0] for reading, p1[1] for writing (parent to child)
    pipe(p2);  // p2[0] for reading, p2[1] for writing (child to parent)
    
    pid = fork();  // Create a new process

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        for (int i = 0; i < 10; i++) {
            // Read byte from parent through p1
            read(p1[0], buffer, 1);
            printf("Child received: %c\n", buffer[0]);

            // Modify the byte and send it back to the parent via p2
            buffer[0] += 1;
            write(p2[1], buffer, 1);
        }
        exit(0);
    } else {
        // Parent process
        buffer[0] = 'A';  // Start with the letter 'A'

        for (int i = 0; i < 10; i++) {
            // Send byte to child through p1
            write(p1[1], buffer, 1);

            // Read byte back from child through p2
            read(p2[0], buffer, 1);
            printf("Parent received: %c\n", buffer[0]);
        }
        wait(0);  // Wait for child to finish
        exit(0);
    }
}
