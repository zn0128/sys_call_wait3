#include <sys/wait.h>
#include <stdio.h>
#define __LIBRARY__
#include <sys/types.h>
#include <unistd.h>

#define __NR_wait3 74

struct rusage {
    long ru_utime;
    long ru_stime;
    long ru_lifetime;
};

pid_t wait3(pid_t pid, int *wait_stat, struct rusage *rusage);
_syscall3(pid_t, wait3, pid_t, pid, int *, wait_stat, struct rusage *, rusage)

int main() {
    int i, j, k = 0;
    time_t currentTime;

    pid_t childpid = fork();
    long result = 0;

    if (childpid > 0) {
      	int status;
        struct rusage usage;
        wait3(childpid, &status, &usage);
     	printf("i am father\n");
     	printf("Child process finished, status: %d\n", status);
        printf("Resource usage:\n");
        printf("User time: %ld\n", usage.ru_utime);
        printf("System time: %ld\n", usage.ru_stime);
        printf("Life time: %ld\n", usage.ru_lifetime);
    } else if (childpid == 0) {
	    for (i = 0; i < 5000; i++) {
            for (j = 0; j < 1000; j++) {
                k++;
            }
        }

        for(i = 0; i < 10000; i++) {
            time(&currentTime);
       	}

   	    sleep(3);
   	    exit(0);
    }

    return 0;
}
