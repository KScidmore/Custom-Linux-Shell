/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   stringlib.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include "stringlib.h"
#include <sys/types.h>

/*---------- FUNCTION: string_comp -------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    const char *str1
/      TODO 
/    const char *str2
/      TODO 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
int string_comp(const char *str1, const char *str2){

    while(*str1 && *str2){

        if(*str1 != *str2){

            return -1;
        }
        str1++;
        str2++;
    }
    if(*str1 != *str2){

        return -1;
    }

    return 0;
    
}


/*---------- FUNCTION: string_len --------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    const char *str
/      TODO 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
int string_len(const char *str){

    int length = 0;

    while(*str != '\0'){

        length++;
        str++;

    }


    return length;
}


/*---------- FUNCTION: string_copy -------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    const char *src
/      TODO 
/    char *dst
/      TODO 
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void string_copy(const char *src, char *dst){

    while(*src != '\0'){

        *dst = *src;

        src++;
        dst++;
    }

    *dst = '\0';

}

void pid_to_string(pid_t pid, char *buffer){
    int i = 0;

    if (pid == 0) {
        buffer[i++] = '0';
    } else {

        while (pid > 0) {
            buffer[i++] = (pid % 10) + '0'; 
            pid /= 10; 
        }
    }

    buffer[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}