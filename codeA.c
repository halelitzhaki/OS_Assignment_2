#include "codeA.h"

char* codea(char*argv[]) {
    char * str = argv[2];
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] >= 97 && str[i] <= 122) {// str[i] lower
            str[i] -= 32;
        }
        else if(str[i] >= 65 && str[i] <= 90) {
            str[i] += 32;
        }
    }
    return str;
}