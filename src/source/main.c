/*
Developer: Arceo, Rafael Gabriel B.
Linear regression implementation using C. 
The expect input would be a csv file containing 2 headers. 
The C Program will read the csv file.

Expected output would be an equation where the two constants a_0 and a_1 are calculated.

*/

#include <stdio.h>

int main(int argc, char **argv){
    char headers[1][2]; // headers assumes that the input headers are only one variable e.g. x, y
    FILE *fp; 
    if((fp = fopen(argv[1], "r")) == NULL){
        printf("Error: File not found.");
        return -1;
    } 

    char* stringBuffer = fgets(stringBuffer, 16, fp); // reads the first line of the file.
    headers[0][0] = *stringBuffer;
    headers[0][1] = *(stringBuffer + 2); 

    printf("Hello, world!");
    return 0;
}