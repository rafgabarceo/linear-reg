/*
Developer: Arceo, Rafael Gabriel B.
Linear regression implementation using C. 
The expect input would be a csv file containing 2 headers. 
The C Program will read the csv file.

Expected output would be an equation where the two constants a_0 and a_1 are calculated.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BUFFER_SIZE 16
#define MAX_INT_BUFFER_SIZE 1024

float *a1_calculateTerm1(float* x, float* y, int n, float* result);
float *a1_calculateTerm2(float* x, float* y, int n,float* result);
float *a1_calculateTerm3(float* x, int n, float *result);
float *a1_calculateTerm4(float* x, int n, float* result);

float *a0_calculateTerm1(float* x, float* y, int n, float* result);
float *a0_calculateTerm2(float* x, float* y, int n,float* result);
float *a0_calculateTerm3(float* x, int n, float *result);
float *a0_calculateTerm4(float* x, int n, float* result);

int main(int argc, char **argv){

    float* ind = malloc(MAX_INT_BUFFER_SIZE * sizeof(float));
    float* dep = malloc(MAX_INT_BUFFER_SIZE * sizeof(float));
    float a0 = 0;
    float a1 = 0;
    int arrPointer = 0;
    int numberOfPoints = 0; 

    char* headers = malloc((sizeof(char) * MAX_BUFFER_SIZE));
    FILE *fp = fopen(argv[1], "r"); 
    if(fp == NULL){
        printf("Error: File not found.");
        return -1;
    } 

    char* stringBuffer = malloc(MAX_BUFFER_SIZE);
    fgets(stringBuffer, MAX_BUFFER_SIZE, fp); // reads the first line of the file
    *(headers) = *(stringBuffer);
    *(headers + 1) = *(stringBuffer + 2);

    printf("Independent Variable: %c, Dependent Variable: %c. Calculating linear regression equation. \n", *headers, *(headers + 1));

    /*
    
    TODO: Read line until ",". Parse entire function into a float. 
    fgets reads entire string. Go through entire string until , is noticed. 
    
    */
    while(fgets(stringBuffer, MAX_BUFFER_SIZE, fp)){
        char *commaLocation = strchr(stringBuffer, (int) ',');
        char *endLocation = strchr(stringBuffer, (int) '\r'); // find memory location of terminating character
        int zeroToCommaDifference = abs((stringBuffer - commaLocation)); // Get the difference of memory locations
        int commaToEndDifference = abs((stringBuffer - endLocation));

        char* indBuffer = malloc(sizeof(char) * zeroToCommaDifference);
        char* depBuffer = malloc(sizeof(char) * commaToEndDifference);

        indBuffer = strncpy(indBuffer, stringBuffer, zeroToCommaDifference);
        depBuffer = strncpy(depBuffer, (stringBuffer + zeroToCommaDifference + 1), commaToEndDifference);

        sscanf(indBuffer, "%f", (ind + arrPointer)); 
        sscanf(depBuffer, "%f", (dep + arrPointer)); 

        free(indBuffer);
        free(depBuffer);

        arrPointer++;
        numberOfPoints++; // one line represents one data point. Increment to find N. 
    }

    free(stringBuffer); // release stringBuffer

    //calculate a0     
    float* a0Term1 = malloc(sizeof(float));
    float* a0Term2 = malloc(sizeof(float));
    float* a0Term3 = malloc(sizeof(float));
    float* a0Term4 = malloc(sizeof(float));

    // calculate a1
    float* a1Term1 = malloc(sizeof(float));
    float* a1Term2 = malloc(sizeof(float));
    float* a1Term3 = malloc(sizeof(float));
    float* a1Term4 = malloc(sizeof(float));

    a1_calculateTerm1(ind, dep, numberOfPoints, a1Term1);
    a1_calculateTerm2(ind, dep, numberOfPoints, a1Term2);
    a1_calculateTerm3(ind, numberOfPoints, a1Term3);
    a1_calculateTerm4(ind, numberOfPoints, a1Term4);

    a0_calculateTerm1(ind, dep, numberOfPoints, a0Term1);
    a0_calculateTerm2(ind, dep, numberOfPoints, a0Term2);

    a0 = (*a0Term1 - *a0Term2)/(*a1Term3 - *a1Term4);
    a1 = (*a1Term1 - *a1Term2)/(*a1Term3 - *a1Term4);

    printf("Resulting equation: y = % 0.5f + %0.5fx", a0, a1);
    
    return 0;
}

float *a1_calculateTerm1(float* x, float* y, int n, float* result){
    float bufferX = 0;
    float bufferY = 0; 
    for(int i = 0; i < n; i++){
        bufferX = *(x + i);
        bufferY = *(y + i);
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
    *result *= n; 
    return result; 
}

float *a1_calculateTerm4(float* x, int n, float* result){
    for(int i = 0; i < n; i++){
        *result += *(x + i);
    }
    *result = powf(*result, 2);
    return result; 
}

float *a0_calculateTerm1(float* x, float* y, int n, float* result){
    float bufferX = 0;
    float bufferY = 0;
    for(int i = 0; i < n; i++){
        bufferX += powf(*(x + i), 2.0);
        bufferY += *(y + i);
    }
    *result = bufferX * bufferY;
    return result; 
}

float *a0_calculateTerm2(float* x, float* y, int n, float* result){
    float bufferX = 0;
    float bufferXY = 0;
    for(int i = 0; i < n; i++){
        bufferX += *(x + i);
        bufferXY += *(x + i) * *(y + i);
    }
    *result = bufferX * bufferXY; 
    return result; 
}