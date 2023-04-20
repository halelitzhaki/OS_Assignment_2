#include "codeB.h"

char* codebEncode(char *argv[]) {
    char *str = argv[2];
    for(int i = 0; i < strlen(str); i++) {
        str[i] += 3;
    }
    return str;
}

char* codebDecode(char *argv[]) {
    char *str = argv[2];
    for(int i = 0; i < strlen(str); i++) {
        str[i] -= 3;
    }
    return str;
}