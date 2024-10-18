/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   prompt.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include "prompt.h"
#include "stringlib.h"

/*---------- FUNCTION: show_prompt -------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    N/A--No input parameters. 
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/

/* 
- I think this handles errors, haven't tested that thoroughly
- I always customize my prompt on my machine and I figured this would get us some brownie points, plus its super simple to implement with a few syscalls 
- pwd does work, just gives absolute instead of relative path which is way long, want to try to fix this because 4096 is the limit which is crazy
*/
void show_prompt() {
    struct passwd *passwd = getpwuid(getuid());
    char *username;
    if (passwd != NULL) {
        username = passwd->pw_name;
    } 
    else {
        username = "unknown";
    }

    char hostname[HOST_MAX] = {0};
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        string_copy(hostname, "unknownhost\0");
    }

    /*
    char pwd[PATH_MAX] = {0};
    if (getcwd(pwd, sizeof(pwd)) == NULL) {
        string_copy(pwd, "unknown-dir\0");
    }
    */

    write(2, ANSI_MAGENTA, sizeof(ANSI_MAGENTA) - 1); 
    write(2, username, sizeof(username));
    write(2, "@", 1);
    write(2, hostname, string_len(hostname));
    write(2, ANSI_RESET, sizeof(ANSI_RESET) - 1); 
    write(2, ":", 1);
    write(2, ANSI_CYAN, sizeof(ANSI_CYAN) - 1); 
    write(2, "kash", 4);
    /*
    write(2, pwd, string_len(pwd));
    */
    write(2, ANSI_RESET, sizeof(ANSI_RESET) - 1); 
    write(2, "$ ", 2);
}