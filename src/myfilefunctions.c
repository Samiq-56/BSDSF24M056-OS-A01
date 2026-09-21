// File: src/myfilefunctions.c
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "../include/myfilefunctions.h"

// Counts lines, words and characters. Returns 0 on success, -1 on failure.
int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (file == NULL || lines == NULL || words == NULL || chars == NULL) return -1;

    *lines = 0;
    *words = 0;
    *chars = 0;

    int c;
    int inWord = 0;
    while ((c = fgetc(file)) != EOF) {
        (*chars)++;
        if (c == '\n') (*lines)++;
        if (isspace(c)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            (*words)++;
        }
    }
    return 0;
}

// Finds all lines containing search_str. Fills *matches with a dynamically
// allocated array of strings. Returns number of matches, or -1 on failure.
// The caller must free each string and then the array itself.
int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (fp == NULL || search_str == NULL || matches == NULL) return -1;

    *matches = NULL;
    char* line = NULL;
    size_t cap = 0;
    ssize_t len;
    int count = 0;

    while ((len = getline(&line, &cap, fp)) != -1) {
        if (strstr(line, search_str) == NULL) continue;

        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        char** tmp = realloc(*matches, (count + 1) * sizeof(char*));
        char* copy = (tmp != NULL) ? malloc(strlen(line) + 1) : NULL;
        if (tmp == NULL || copy == NULL) {
            // memory error: clean up everything and fail
            if (tmp != NULL) *matches = tmp;
            for (int i = 0; i < count; i++) free((*matches)[i]);
            free(*matches);
            *matches = NULL;
            free(line);
            return -1;
        }
        *matches = tmp;
        strcpy(copy, line);
        (*matches)[count] = copy;
        count++;
    }

    free(line);
    return count;
}
