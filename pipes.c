#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END  0
#define WRITE_END 1

int main()
{
    int pipefd[2];
    int pid1, pid2;
    int child_status;

    char *const argv1[] = { "/bin/ls", "-al", NULL };
    char *const argv2[] = { "/usr/bin/wc", "-l", NULL };
    char *const envp[] = { NULL };

    if (pipe(pipefd) == -1) { /* create pipe & error handling */
        perror("Error: pipe failed.");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("Error: fork failed.");
    }

    if (pid1 == 0) {
        close(pipefd[READ_END]);
        dup2(pipefd[WRITE_END], 1);
        execve("/bin/ls", argv1, envp);
    }

    close(pipefd[WRITE_END]);

    pid2 = fork();
    if (pid2 == -1) {
        perror("Error: fork failed.");
    }

    if (pid2 == 0) {
        close(pipefd[WRITE_END]);
        dup2(pipefd[READ_END], 0);
        execve("/usr/bin/wc", argv2, envp);
    }

    close(pipefd[READ_END]);

    waitpid(pid1, &child_status, 0); /* wait for children to terminate */
    waitpid(pid2, &child_status, 0);

    exit(EXIT_SUCCESS);
}