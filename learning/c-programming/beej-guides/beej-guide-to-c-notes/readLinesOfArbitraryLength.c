#include <stdio.h>
#include <stdlib.h>

// Note this strips the newline from the results
// if the newline character is needed it would be best to use a do-while loop




char *readLine(FILE *fp){

    int offset = 0;  // Index next char goes in the buffer
    int bufsize = 4;  // preferably power of 2 initial size
    char *buf;  // the buffer
    int c;  // the character we've read in

    // allocate memory to the buffer with an initial size of 4
    buf = malloc(bufsize);

    // error check!
    // new format i will try to follow without the curly braces '{}'
    // beej does a great job of giving us options on how to write things!
    if (buf == NULL)
        return NULL;

        // read until the newline or end of file
    while (c = fgetc(fp), c != '\n' && c != EOF) {
        
        // check if we;re out of room int he buffer accounting
        // for the extra byte for the Nul terminator
        if (offset == bufsize - 1){

             bufsize *= 2;

            // we create a new buffer and realloc the buf with the new size
            // that we get from multiplying the bufsize * 2
                char *new_buf = realloc(buf, bufsize);

            // Check for errors! if it errors free the space and bail
                if (new_buf == NULL){
                    free(buf);
                    return NULL;
                }
                // if successful reassign the buf to the new buf
                buf = new_buf;

            }
                    // Add the byte onto the buffer
                    buf[offset++] = c;

        }

        // We hit newline or EOF...


        //  If at EOF and we read no bytes free the buffer
        // and return NULL to indicate we're at EOF
        if (c == EOF && offset == 0) {
            free(buf);
            return NULL;
        }

        // shrink to fit
        if (offset < bufsize - 1) {
            char *new_buf = realloc(buf, offset + 1);


            // check if successful, point to new_buf
            // otherwise leave the buf where it is
            if (new_buf != NULL)
                buf = new_buf;
        }
        // Add the NUL terminator
        buf[offset] = '\0';
        return buf;


        
}



   int main(void){

            FILE *fp = fopen("test.txt", "r");

            char *line;

            while ((line = readLine(fp)) != NULL) {
                printf("%s\n", line);
                free(line);
            }
            fclose(fp);
        }