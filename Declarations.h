#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED
#include "Filaments.h"
#include "PARAMETERS.h"

extern int a_growing [bins];
extern int a_shrinking [bins];
extern vector<Filament> collection;
extern string file_name;
void stamp();
void nucleation();
void evolve();
void measure();
void update_results();
double rnd();

#endif // DECLARATIONS_H_INCLUDED


