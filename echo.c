#include <unistd.h>
#include <fcntl.h>
#include  <stdio.h>

#define BUFFER_SIZE 1024
#define MAX_TOKENS 256

int stringComp(const char *str1, const char *str2);
void tokenize(char *tokens[], char buffer[]);

int main(){

    const char *dollar = "$ ";
    char buffer[BUFFER_SIZE];
    char *tokens[MAX_TOKENS];
    ssize_t bytesRead;

    int i, j;

    write(1, dollar, 2);

    while(1){

        bytesRead = read(0, buffer, 1024 - 1);

        buffer[bytesRead] = '\0';
        if (stringComp(buffer, "exit\n") == 1){
            break;
        }
        write(1, buffer, bytesRead);

        tokenize(tokens, buffer);

        for(i = 0; tokens[i] != 0; i++){
            j = 0;
            while(tokens[i][j] != '\0'){
                write(1, &tokens[i][j], 1);
                j++;
            }

            write(1, "\n" , 1);
        }
        write(1, dollar, 2);
    }
    return 0;
}

/*Breaks buffer into command line arguments (tokens) based on whitespace*/
void tokenize(char *tokens[], char buffer[]){

    int i = 0;
    int tokenIndex = 0; /*tracks the index of next token to be placed in array*/
    char *start = 0; /*Pointer For start of string being tokenized*/

    while(buffer[i] != '\0'){ /*Runs till end of buffer*/

        if(buffer[i] != ' ' && buffer[i] != '\n'){ /*checks for whitespace or carriage return*/

            if(start == 0){ /*if start is Null */

                start = &buffer[i]; /*Set start to point at the start of token to be copied*/
            }
        }
        else{ /*Else whitespace IS found*/

            if(start != 0){ /*If start already points to a token to be copied*/

                buffer[i] = '\0'; /*Null terminate token*/
                tokens[tokenIndex++] = start; /*set tokens at specified index to point at start of token*/
                start = 0; /* reset start*/
            }
        }

        i++;

    }

    if(start != 0){ /*Check to make sure all tokens were accounted for*/

        tokens[tokenIndex++] = start; 

    }

    tokens[tokenIndex] = 0; /*Null terminate token array*/

}
int stringComp(const char * str1,const char * str2){

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

