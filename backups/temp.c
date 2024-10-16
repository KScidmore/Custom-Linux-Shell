void mystrtok(char *string, const char *delimiter) {
    int i = 0;
    int token_index = 0; 
    char *start = 0; 

    while (buffer[i] != '\0') { /*runs till end of buffer*/
        if (!is_delimiter(buffer[i], delimiters)) {
            if (buffer[i] != ' ' && buffer[i] != '\n') { 
                if (start == 0) { /*if start is null */
                    start = &buffer[i]; /*set start to point at the start of token to be copied*/
                }
            }
        }
        else { /*else whitespace is found*/
            if (start != 0) { /*if start already points to a token to be copied*/
                buffer[i] = '\0'; /*null terminate token*/
                tokens[token_index++] = start; /*set tokens at specified index to point at start of token*/
                start = 0; /* reset start*/
            }
        }
        i++;
    }

    if (start != 0) { /*check to make sure all tokens were accounted for*/
        tokens[token_index++] = start; 
    }

    tokens[token_index] = 0; /*null terminate token array*/
}

/* helper function for mystrtok */
int is_delimiter(char ch, const char delimiters[]) {
    for (int i = 0; delimiters[i] != '\0'; i++) {
        if (ch == delimiters[i]) {
            return 1;
        }
    }
    return 0;
}

