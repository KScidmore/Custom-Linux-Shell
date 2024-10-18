/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   search.c
/
/  Program Purpose(s):
/    Custom library built to manage a linear search for file
/    names using the PATH environment variable. 
/---------------------------------------------------------*/

#include <sys/stat.h>
#include <unistd.h>
#include "stringlib.h"

/*---------- FUNCTION: get_path ----------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    TODO - purpose of input parameters 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
char *get_path(char **path, char *envp[]) {
    int i = 0;

    for (i = 0; envp[i] != NULL; i++) {
        if (str_comp_by_len(envp[i], "PATH=", 5) == 0) {
            return *path = envp[i] + 5;
        }
    }

    return *path = NULL; /* not found */
}

/*---------- FUNCTION: check_for_file ----------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    TODO - purpose of input parameters 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
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


/*

if (check_for_file("ls", full_path, envp) == 0) {
    printf("file found: %s\n", full_path);
} else if (check_for_file("ls", full_path, envp) == -1) {
    printf("file not found\n");
}

*/