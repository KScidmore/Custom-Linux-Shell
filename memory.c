/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   memory.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include "memory.h"

char heap[HEAP_SIZE];
char *p_free_heap = heap;

/*---------- FUNCTION: alloc -------------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    unsigned int size 
/      TODO 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
char *alloc(unsigned int size) {
    /*Calculate the new pointer after allocation*/
    char *new_free_heap = p_free_heap + size;
    
    /*Check if the new pointer would exceed the allocated heap size*/
    if (new_free_heap <= (p_free_heap + HEAP_SIZE)) {
        char *p_alloced = p_free_heap;
        p_free_heap = new_free_heap;
        return p_alloced;
    } else {
        return NULL; /* error if memory runs out, but shouldn't reach this */
    }
}

/*---------- FUNCTION: free_all ----------------------------
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
void free_all() {
    p_free_heap = heap;
}