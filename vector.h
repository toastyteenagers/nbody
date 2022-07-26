#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct vec3 {
    double e1;
    double e2;
    double e3;
} vec3;

vec3* initVec3(double v1, double v2, int32_t v3) {
    vec3* retvec = (vec3*)(malloc(sizeof(vec3)));
    retvec->e1 = v1;
    retvec->e2 = v2;
    retvec->e3 = v3;
    return retvec;
}

void printVec(vec3* vec) {
    printf("%f %f %f\n", vec->e1, vec->e2, vec->e3);
}