/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   stringlib.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include "stringlib.h"

/*---------- FUNCTION: string_comp --------------------------------
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
/
/  CITATIONS:
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

    return 1;
    
}


/*---------- FUNCTION: string_len --------------------------------
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
/
/  CITATIONS:
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


/*---------- FUNCTION: string_copy --------------------------------
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
/
/  CITATIONS:
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

char *sub_string(const char *command){


    
}