// File: src/main.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");

    const char* text = "Hello, World";
    char buf[100];
    char buf2[100];

    printf("mystrlen(\"%s\") = %d\n", text, mystrlen(text));

    int n = mystrcpy(buf, text);
    printf("mystrcpy: buf = \"%s\" (copied %d chars)\n", buf, n);

    n = mystrncpy(buf2, "Operating Systems", 9);
    printf("mystrncpy (n=9): buf2 = \"%s\" (copied %d chars)\n", buf2, n);

    n = mystrcat(buf, " from OS lab");
    printf("mystrcat: buf = \"%s\" (new length %d)\n", buf, n);

    printf("\n--- Testing File Functions ---\n");

    // Create a sample file to test with
    FILE* fp = fopen("sample.txt", "w");
    if (fp == NULL) {
        perror("fopen (write)");
        return 1;
    }
    fputs("Operating systems manage hardware.\n", fp);
    fputs("Linux is an operating system.\n", fp);
    fputs("Kali Linux is used for security.\n", fp);
    fputs("Make builds programs from source files.\n", fp);
    fclose(fp);

    fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        perror("fopen (read)");
        return 1;
    }

    int lines, words, chars;
    if (wordCount(fp, &lines, &words, &chars) == 0)
        printf("wordCount: lines=%d, words=%d, chars=%d\n", lines, words, chars);
    else
        printf("wordCount failed\n");

    rewind(fp);  // go back to start of file for mygrep

    char** matches = NULL;
    int count = mygrep(fp, "Linux", &matches);
    if (count >= 0) {
        printf("mygrep(\"Linux\"): %d match(es)\n", count);
        for (int i = 0; i < count; i++) {
            printf("  %d: %s\n", i + 1, matches[i]);
            free(matches[i]);
        }
        free(matches);
    } else {
        printf("mygrep failed\n");
    }

    fclose(fp);
    return 0;
}
