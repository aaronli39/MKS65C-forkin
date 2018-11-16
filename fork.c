#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main() {
    int parent = getpid();
    int first_child = fork();
    if (getpid() != parent) {
        printf("hi im child: %d\n", getpid());
    }
    int second_child;
    if (getpid() == parent) {
        printf("Yo im parent: %d\n", parent);
        // second_child = fork();
    } else if (getpid() == first_child){
        printf("yo im first child: %d\nMy parent is: %d\n", first_child, getppid());
    }

}
