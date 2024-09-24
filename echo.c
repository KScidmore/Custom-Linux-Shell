#include <unistd.h>
#include <fcntl.h>

int stringComp(const char * str1, const char * str2);

int main(){

    const char * dollar = "$ ";
    char buffer[1024];
    ssize_t bytesRead;

    write(1, dollar, 2);

    while(1){

        bytesRead = read(0, buffer, 1024 - 1);

        buffer[bytesRead] = '\0';
        if (stringComp(buffer, "exit\n") == 1){
            break;
        }
        write(1, buffer, bytesRead);
        write(1, dollar, 2);
    }
    return 0;
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