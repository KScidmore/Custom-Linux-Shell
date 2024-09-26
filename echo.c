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

void tokenize(char *tokens[], char buffer[]){

    int i = 0;
    int tokenIndex = 0;
    char *start = 0;

    while(buffer[i] != '\0'){

        if(buffer[i] != ' ' && buffer[i] != '\n'){

            if(start == 0){

                start = &buffer[i];
            }
        }
        else{

            if(start != 0){

                buffer[i] = '\0';
                tokens[tokenIndex++] = start;
                start = 0;
            }
        }

        i++;

    }

    if(start != 0){

        tokens[tokenIndex++] = start;

    }

    tokens[tokenIndex] = 0;

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

