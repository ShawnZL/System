#include <iostream>
#include <unistd.h>
#include "comm.h"
int main() {
    int semid = createSemSet(1);
    initSems(semid, 0, 1);
    pid_t id = fork();
    if (id == 0) { // child
//        int semid = getSemSet();
        while (1) {
            P(semid, 0);
            printf("A\n");
            fflush(stdout);
            usleep(300000);
            printf("A\n");
            fflush(stdout);
            usleep(300000);
            V(semid, 0);
        }
    }
    else { // father
        while (1) {
            P(semid,0);
            printf("B\n");
            fflush(stdout);
            usleep(400000);
            printf("B\n");
            fflush(stdout);
            usleep(400000);
            V(semid,0);
        }
        wait(NULL);
    }
    destroySems(semid);
    return 0;
}
