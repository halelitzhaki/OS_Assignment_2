#include "codeA.h"
#include "codeB.h"

#define A "codecA"

int main (int argc, char *argv[]){
    if(strcmp(argv[1], A) == 0) {
        char * encoded = codea(argv);
        printf("%s\n", encoded);
    }
    else {
        char * encoded = codebEncode(argv);
        printf("%s\n", encoded);
    }
    return 0;
}