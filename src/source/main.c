/*
Developer: Arceo, Rafael Gabriel B.
Linear regression implementation using C. 
The expect input would be a csv file containing 2 headers. 
The C Program will read the csv file.

Expected output would be an equation where the two constants a_0 and a_1 are calculated.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BUFFER_SIZE 8
#define MAX_INT_BUFFER_SIZE 1024

float *a1_calculateTerm1(float* x, float* y, int n, float* result);
float *a1_calculateTerm2(float* x, float* y, int n,float* result);
float *a1_calculateTerm3(float* x, int n, float *result);
float *a1_calculateTerm4(float* x, int n, float* result);

int main(int argc, char **argv){

    float* ind = malloc(MAX_INT_BUFFER_SIZE * sizeof(float));
    float* dep = malloc(MAX_INT_BUFFER_SIZE * sizeof(float));
    int arrPointer = 0;
    int numberOfPoints = 0; 

    char headers[1][2]; // headers assumes that the input headers are only one variable e.g. x, y
    FILE *fp = fopen(argv[1], "r"); 
    if(fp == NULL){
        printf("Error: File not found.");
        return -1;
    } 

    char* stringBuffer = malloc((char) MAX_BUFFER_SIZE);
    fgets(stringBuffer, MAX_BUFFER_SIZE, fp); // reads the first line of the file.
    headers[0][0] = *stringBuffer;
    headers[0][1] = *(stringBuffer + 2); 

    printf("Independent Variable: %c, Dependent Variable: %c. Calculating linear regression equation. \n", headers[0][0], headers[0][1]);

    while(fgets(stringBuffer, MAX_BUFFER_SIZE, fp)){
        sscanf((stringBuffer), "%f", (ind + arrPointer));
        sscanf((stringBuffer + 2), "%f", (dep + arrPointer));
        arrPointer++;
        numberOfPoints++; // one line represents one data point. Increment to find N. 
    }


    //calculate a0     

    // calculate a1
    float* a1Term1 = malloc(sizeof(float));
    float* a1Term2 = malloc(sizeof(float));
    float* a1Term3 = malloc(sizeof(float));
    float* a1Term4 = malloc(sizeof(float));

    a1_calculateTerm1(ind, dep, numberOfPoints, a1Term1);
    a1_calculateTerm2(ind, dep, numberOfPoints, a1Term2);
    a1_calculateTerm3(ind, numberOfPoints, a1Term3);

    return 0;
}

float *a1_calculateTerm1(float* x, float* y, int n, float* result){
    for(int i = 0; i < n; i++){
        float bufferX = *(x + i);
        float bufferY = *(y + i);
        *result += bufferX*bufferY;     
    }
    *result *= n;
    return result; 
}

float *a1_calculateTerm2(float* x, float* y, int n, float* result){
    float bufferX = 0;
    float bufferY = 0;
    for(int i = 0; i < n; i++){
        bufferX += *(x + i);
        bufferY += *(y + i);
    }
    *result = bufferX * bufferY;
    return result; 
}

float *a1_calculateTerm3(float* x, int n, float *result){
    for(int i = 0; i < n; i++){
        *result += powf(*(x + i), 2.0);
    }
    return result; 
}

float *a1_calculateTerm4(float* x, int n, float* result){

}