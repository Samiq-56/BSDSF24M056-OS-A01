// File: src/mystrfunctions.c
#include <stddef.h>
#include "../include/mystrfunctions.h"

// Returns the length of s (without '\0'), or -1 if s is NULL.
int mystrlen(const char* s) {
    if (s == NULL) return -1;
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

// Copies src into dest (including '\0'). Returns number of chars copied, or -1 on error.
int mystrcpy(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return -1;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

// Copies at most n chars of src into dest and always adds '\0'
// (dest must have space for n+1 chars). Returns number of chars copied, or -1 on error.
int mystrncpy(char* dest, const char* src, int n) {
    if (dest == NULL || src == NULL || n < 0) return -1;
    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

// Appends src at the end of dest. Returns new length of dest, or -1 on error.
int mystrcat(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return -1;
    int d = mystrlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[d + i] = src[i];
        i++;
    }
    dest[d + i] = '\0';
    return d + i;
}
