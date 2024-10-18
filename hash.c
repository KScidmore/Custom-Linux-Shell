/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   hash.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include <sys/stat.h>
#include <unistd.h>

/* get rid of after testing */
#include <stdlib.h>
#include <stdio.h> 

#define MAX_PATH_LENGTH 4096

/* delete these later*/
int string_comp(const char *str1, const char *str2, int len); 

/* not these */
char *get_path(char **path, char *envp[]);
int check_for_file(char *command, char *full_path, char *envp[]);
void test_check_for_file(char *fullpath, char *envp[]);

int main(int argc, char *argv[], char *envp[]) {
    
    char full_path[MAX_PATH_LENGTH];

    test_check_for_file(full_path, envp);
    
    return 0;
}

/* working now */
char *get_path(char **path, char *envp[]) {
    int i = 0;

    for (i = 0; envp[i] != NULL; i++) {
        if (string_comp(envp[i], "PATH=", 5) == 0) {
            return *path = envp[i] + 5;
        }
    }

    return *path = NULL; /* not found */
}

int check_for_file(char *command, char *full_path, char *envp[]) {
    struct stat sb;
    int path_index = 0;
    char *path;
    int i = 0;
    int j = 0;

    if (get_path(&path, envp) == NULL) {
        path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games";
    } /* assigns path and sets default if "PATH" not in envp */

    while (path[i] != '\0') {

        path_index = 0;
        j = 0;

        while(path[i] != ':' && path[i] != '\0') {
            full_path[path_index++] = path[i++];
        } /* append path to full_path */

        full_path[path_index++] = '/'; /* appending before command */

        while (command[j] != '\0') {
            full_path[path_index++] = command[j++];
        } /* appending the command to full_path */

        full_path[path_index] = '\0';

        if (stat(full_path, &sb) == 0) {
            return 0; /* file found */
        }

        i += 1; /* skip over the ':' delimiter before restarting loop */

    } /* null terminator reached */

    return 1; /* file not found */
}

/* working with this, need to test with other stuff or make 2 funcs */
int string_comp(const char *str1, const char *str2, int len){

    for (int i = 0; i < len; i++) {
        if(str1[i] != str2[i]){
            return -1;
        }
    }

    return 0;
}

void test_check_for_file(char *full_path, char *envp[]) {
    if (check_for_file("ls", full_path, envp) == 0) {
        printf("file found: %s\n", full_path);
    } else if (check_for_file("ls", full_path, envp) == -1) {
        printf("file not found\n");
    }

    if (check_for_file("wc", full_path, envp) == 0) {
        printf("file found: %s\n", full_path);
    } else if (check_for_file("ls", full_path, envp) == -1) {
        printf("file not found\n");
    }

     if (check_for_file("awk", full_path, envp) == 0) {
        printf("file found: %s\n", full_path);
    } else if (check_for_file("ls", full_path, envp) == -1) {
        printf("file not found\n");
    }

    if (check_for_file("grep", full_path, envp) == 0) {
        printf("file found: %s\n", full_path);
    } else if (check_for_file("ls", full_path, envp) == -1) {
        printf("file not found\n");
    }

    if (check_for_file("sed", full_path, envp) == 0) {
        printf("file found: %s\n", full_path);
    } else if (check_for_file("ls", full_path, envp) == -1) {
        printf("file not found\n");
    }

}