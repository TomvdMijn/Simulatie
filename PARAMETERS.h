#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED
#define Project_name    "simulatie "
#include "Filaments.h"
#include <math.h>


/////////////////////////// GLOBEL VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define T_MAX           1                       // [t]
#define R_nuc           2                       // [t]^-1
#define V_g             15.6                    // [l] / [t]        documented
#define V_s             0.1                     // [l] / [t]        documented
#define R_c             3                       // [t]^-1           documented
#define dt              0.001                   // [t]
#define L_s             40                      // [l]


////////////////////// DERIVED VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const double P_nuc = R_nuc * dt;
const double P_cap = R_c * dt;
const double time_steps = T_MAX / dt;
const int bins = 100;
const double bin_size = L_s / bins;


#endif // PARAMETERS_H_INCLUDED
