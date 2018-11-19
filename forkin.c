#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int get_random() {
    int * temp = malloc(sizeof(int)); // allocate pointer
    int straw = open("/dev/random", O_RDONLY); // open
    read(straw, temp, sizeof(int)); // read num into temp
    int ret = * temp; // store var before freeing
    free(temp);
    close(straw);
    return ret;
}

int main() {
    // parent instructions:
    int parent = getpid(); // parent PID
    int first_child;
    int second_child;
    int status, sleepe;
    // print a statement
    printf("I am parent with PID: %d, about to fork.\n", parent);
    first_child = fork();
    // if statements to run diff commands for diff pids
    if (getpid() == parent) {
        // fork second child if parent
        second_child = fork();
        // parent statement:
        if (getpid() == parent) {
            int child = wait(&status);
            int how_long = WEXITSTATUS(status);
            printf("CHILD: %d slept for %d\nparent exiting now...\n", child, how_long);
            exit(1);
        } else { // child two
            printf("Child: %d\n", getpid());
            sleepe = abs(get_random()) / 123456745;
            sleep(sleepe);
            printf("Done sleeping\n");
            return sleepe;
        }
    } else { // child one
        printf("Child: %d\n", getpid());
        sleepe = abs(get_random()) / 123456755;
        sleep(sleepe);
        printf("Done sleeping\n");
        return sleepe;
    }

    return 0;


    //
    // int parent = getpid();
    // int first_child = fork();
    // if (getpid() != parent) {
    //     printf("hi im child: %d\n", getpid());
    // }
    // int second_child;
    // if (getpid() == parent) {
    //     printf("Yo im parent: %d\n", parent);
    //     // second_child = fork();
    // } else if (getpid() == first_child){
    //     printf("yo im first child: %d\nMy parent is: %d\n", first_child, getppid());
    // }

}
