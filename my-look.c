/** 
 * Copyright 2021 Isha Padmanaban
 * Name : Isha Padmanaban
 * Email : ipadmanaban@wisc.edu
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/** 
 * This program takes a string as an input and return any 
 * lines in a file that contain that string as a prefix
 */

int main(int argc, char ** argv) {
    int opt, result, file_found = 0;
    char *prefix;
    char buffer[128];
    FILE *fp;

    /* The input arguments are parsed using getopt */

    while ((opt  = getopt(argc, argv, "Vhf:")) != -1) {
        switch (opt) {
            case 'V':
                printf("my-look from CS537 Spring 2021\n");
                exit(0);
            case 'h':
                printf("my-look takes a string as input and returns any lines");
                printf(" in a file that contain that string as a prefix\n");
                exit(0);
            case 'f':
                fp = fopen(optarg, "r");
                if (fp == NULL) {
                    printf("my-look: cannot open file\n");
                    exit(1);
                }
                file_found = 1;
                break;
            case '?':
                printf("my-look: invalid command line\n");
                exit(1);
        }
    }

    int iter = 0;
    for (; optind < argc; optind++) {
        if (iter > 0) {
            printf("my-look: invalid command line\n");
            exit(1);
        }
        prefix = argv[optind];
        iter++;
    }

    if (prefix == NULL) {
        printf("my-look: invalid command line\n");
        exit(1);
    }

    if (file_found == 0) {
        fp = stdin;
    }

    /** 
     * The input string is checked with the contents 
     * in the file/stdin for valid prefix to output
     */

    while (fgets(buffer, 128, fp) != NULL) {
        result = strncasecmp(prefix, buffer, strlen(prefix));
        if (result == 0) {
            printf("%s", buffer);
        }
    }

    fclose(fp);
    return 0;
}
