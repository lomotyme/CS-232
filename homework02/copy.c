/*
 *  Name: Robert Akinie
 *  Course: CS 232 - A
 *  Homework 2: Making system calls from a c program
 *  Date: 2/22/2021
 *  Copy.c: The purpose of this student is to give student experience with writing a low
 *          level tool in C. This program copies the contents of one file to another.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char * argv[]) {

    char file_getter;
    char * src = argv[1];
    char * dest = argv[2];
    FILE * destination_file = NULL;
    FILE * source_file = NULL;
    


    /* checking if file type is regular
     * www.gnu.org/spftware/libc/manual/html_node/Testing-File-Type.html */
    struct stat buf;
    stat(src, &buf);

    if (S_ISREG(buf.st_mode == 0)) {
        fprintf(stderr, "File not regular: %s\n", src);
        return -1;
    }

    else {

        /* checking for access permission
         * www.programiz.com/c-programming/c-file-input-output */
        if (access(src, R_OK) != 0 ) {
        fprintf(stderr, "Permission denied. %s\n", src);
        return -1;  
        }

        //open the file
        source_file = fopen(src, "r");
        if (source_file == NULL) {
            fprintf(stderr, "Cannot open file %s\n", src);
            return -1;
        }
        
        destination_file = fopen(dest, "w");
        if (destination_file == NULL) {
            fprintf(stderr, "Cannot open file %s\n", dest);
            return -1;
        }
        
        /* copying the file to a destination
         * www.tutorialspoint.com/c-program-to-copy-the-contents-of-one-file-to-another-file */
        file_getter = fgetc(source_file);
        while (file_getter != EOF) {
            fputc(file_getter, destination_file);
            file_getter = fgetc(source_file);
        }

        fclose(source_file);
        fclose(destination_file);
        return 0;
    }
}
