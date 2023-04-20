#include "codeA.h"
#include "codeB.h"

#define A "codecA"

int main (int argc, char *argv[]){
    if(strcmp(argv[1], A) == 0) {
        char * decoded = codea(argv);
        printf("%s\n", decoded);
    }
    else {
        char * decoded = codebDecode(argv);
        printf("%s\n", decoded);
    }
    return 0;
}