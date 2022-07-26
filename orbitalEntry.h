#include "vector.h"

typedef struct orbitalEntry {
    vec3* position;
    vec3* velocity;
    double mass;
} orbitalEntry;

orbitalEntry* initOrbitalEntry(double r1, double r2, double r3, double v1, double v2, double v3, double m) {
    orbitalEntry* retEntry = (orbitalEntry*)(malloc(sizeof(orbitalEntry)));
    retEntry->position = initVec3(r1,r2,r3);
    retEntry->velocity = initVec3(v1,v2,v3);
    retEntry->mass = m;
    return retEntry;
}

void printOrbitalEntry(orbitalEntry* entry) {
    printVec(entry->position);
    printVec(entry->velocity);
}