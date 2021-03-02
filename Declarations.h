#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED
#include "Filaments.h"
#include "PARAMETERS.h"

void write_stamp(double sigma, double lambda );
void offset(double dL);
double r_nuc(double L_G);
double v_g(double L_G);
void stamp();
void nucleation();
void evolve();
void measure();
void writing_results();
void writing(double arry [], string name, int size);
void update_results(int t);
string time_stamp();
double N_nuc(double L_G);
double Poisson(double lambda);
double B(double L_G);
double r_sev();

#endif // DECLARATIONS_H_INCLUDED


