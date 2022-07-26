#include "orbitalEntry.h"
double const bigG = 6.67e-11;
int const numPlanets = 2;
int const dt = 1;

void freeEntryList(orbitalEntry** entries) {
    for (int i = 0; i<numPlanets; i++) {
        free(entries[i]->velocity);
        free(entries[i]->position);
        free(entries[i]);
    }
    free(entries);
}

void runSimulation(orbitalEntry** entryList, int t_final) {
    int t = 0;

    while (t < t_final) {
        for (int m1_index = 0; m1_index < numPlanets; m1_index++) {
            vec3* a_g = initVec3(0,0,0);
            for (int m2_index = 0; m2_index < numPlanets; m2_index++) {
                if (m2_index != m1_index) {
                    vec3* r_vector = initVec3(0,0,0);
                    r_vector->e1 = entryList[m1_index]->position->e1 - entryList[m2_index]->position->e1;
                    r_vector->e2 = entryList[m1_index]->position->e2 - entryList[m2_index]->position->e2;
                    r_vector->e3 = entryList[m1_index]->position->e3 - entryList[m2_index]->position->e3;

                    double r_mag = sqrt(r_vector->e1*r_vector->e1 + r_vector->e2*r_vector->e2 + r_vector->e3*r_vector->e3);

                    double acceleration = -1.0 * bigG * (entryList[m2_index]->mass) / pow(r_mag,2.0);

                    vec3* r_unit = initVec3(r_vector->e1/r_mag, r_vector->e2/r_mag,r_vector->e3/r_mag);

                    a_g->e1 = acceleration * r_unit->e1;
                    a_g->e2 = acceleration * r_unit->e2;
                    a_g->e3 = acceleration * r_unit->e3;
                    free(r_vector);
                    free(r_unit);
                }
            }

            entryList[m1_index]->velocity->e1 += a_g->e1 * dt;
            entryList[m1_index]->velocity->e2 += a_g->e2 * dt;
            entryList[m1_index]->velocity->e3 += a_g->e3 * dt;
            printOrbitalEntry(entryList[m1_index]);
            free(a_g);
        }
        for (int entry_index = 0; entry_index < numPlanets; entry_index++) {
            entryList[entry_index]->position->e1 += entryList[entry_index]->velocity->e1;
            entryList[entry_index]->position->e2 += entryList[entry_index]->velocity->e2;
            entryList[entry_index]->position->e3 += entryList[entry_index]->velocity->e3;
        }

        t+=dt;
    }
}


int main(void) {
    orbitalEntry** entryList = malloc(sizeof(orbitalEntry*) * numPlanets);
    entryList[0] = initOrbitalEntry(0,0,0,0,0,0,2e24);
    entryList[1] = initOrbitalEntry(4,0,0,2e4,0,0,2e10);
    int t_final = 60;
    runSimulation(entryList, t_final);
    freeEntryList(entryList);
    return 0;
}