#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED

//////////////////// GLOBEL VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define T_MAX       1000
#define R_nuc       100
#define V_g         15.6
#define V_s         0.1
#define R_c         3
#define dt          0.000001





////////////////////// DERIVED VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const double P_nuc = R_nuc * dt;


#endif // PARAMETERS_H_INCLUDED
