#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F "-f"
#define V "-v"


int main (int argc, char *argv[]){
    FILE *file1 = fopen(argv[1], "r");
    if(file1 == NULL) {
        if (((argc >= 4) && (strcmp(argv[3], V) == 0)) || ((argc == 5) && (strcmp(argv[4], V) == 0))) printf("output: general failure\n");
        return 1;
    }
    int result = 0;
    char c;
    if(((argc >= 4) && (strcmp(argv[3], F) == 0)) || ((argc == 5) && (strcmp(argv[4], F) == 0))) { // if there is flag -f
        FILE *file2 = fopen(argv[2], "w");
        while(((c = fgetc(file1)) != EOF)) {
            fputc(c, file2);
            if(feof(file1)) break;
        }
        fclose(file2);
    }
    else {
        FILE *file2 = fopen(argv[2], "r");
        if(file2 == NULL) {
            file2 = fopen(argv[2], "w");
            while(((c = fgetc(file1)) != EOF)) {
                fputc(c, file2);
                if(feof(file1)) break;
            }
            fclose(file2);
        }
        else {
            result = 1;
            fclose(file2);
        }
    }

    if(((argc >= 4) && (strcmp(argv[3], V) == 0)) || ((argc == 5) && (strcmp(argv[4], V) == 0))) { // if there is flag -v
        if(result == 1) printf("output: target file exist\n");
        else printf("output: success\n");
    }

    fclose(file1);

    return result;
}