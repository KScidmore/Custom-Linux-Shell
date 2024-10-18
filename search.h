/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   search.h
/
/  Program Purpose(s):
/    User-defined header file for search.c. 
/---------------------------------------------------------*/

#ifndef SEARCH_H
#define SEARCH_H

#define MAX_PATH_LENGTH 4096

/* delete these later*/
int str_comp_by_len(const char *str1, const char *str2, int len); 

/* not these */
char *get_path(char **path, char *envp[]);
int check_for_file(char *command, char *full_path, char *envp[]);
void test_check_for_file(char *fullpath, char *envp[]);

#endif