#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define I "-i"
#define V "-v"

int sameLetter(char, char);

int main (int argc, char *argv[]){
    FILE *file1 = fopen(argv[1], "r"), *file2 = fopen(argv[2], "r");
    if(file1 == NULL || file2 == NULL) {
        printf("no files");
        return 1;
    }
    int result = 0;
    char c1, c2;
    if(((argc >= 4) && (strcmp(argv[3], I) == 0)) || ((argc == 5) && (strcmp(argv[4], I) == 0))) { // if there is flag -i
        while(((c1 = fgetc(file1)) != EOF) && ((c2 = fgetc(file2)) != EOF)) {
            if(c1 != c2 && (sameLetter(c1, c2) == 1)) {
                result = 1;
                break;
            }
            if(feof(file1) || feof(file2)) break;
        }
        if(((c1 == EOF) && (c2 != EOF)) 
            || ((c1 != EOF) && (c2 == EOF))) {
                result = 1;
        }
    }
    else {
        while(((c1 = fgetc(file1)) != EOF) && ((c2 = fgetc(file2)) != EOF)) {
            if(c1 != c2) {
                result = 1;
                break;
            }
            if(feof(file1) || feof(file2)) break;
        }
        if(((c1 == EOF) && (c2 != EOF)) 
            || ((c1 != EOF) && (c2 == EOF))) {
                result = 1;
        }
    }

    if(((argc >= 4) && (strcmp(argv[3], V) == 0)) || ((argc == 5) && (strcmp(argv[4], V) == 0))) { // if there is flag -v
        if(result == 1) printf("output: distinct\n");
        else printf("output: equals\n");
    }

    fclose(file1);
    fclose(file2);

    return result;
}

int sameLetter(char a, char b) {
    if(a - b == 32 || a - b == -32) {
        return 0;
    }
    return 1;
}
