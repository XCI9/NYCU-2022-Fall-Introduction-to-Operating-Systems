#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t Fork(const int forkID) {
    pid_t pid{ fork() };

    if (pid == 0) //child print info
        printf("Fork %d. I'm the child %d, my parent is %d\n", forkID, getpid(), getppid());
    else //parent always need to wait for child
        wait(NULL);

    return pid;
}

int main() {
    printf("Main Process ID : %d\n", getpid());

    pid_t pid{ Fork(1) };
    if (pid == 0) { //child
        pid = Fork(2);
        if (pid == 0) //child
            pid = Fork(3);
    }
    else { //parent
        pid = Fork(4);
        if (pid > 0) //parent
            pid = Fork(6);
        pid = Fork(5);
    }
    return 0;
}
