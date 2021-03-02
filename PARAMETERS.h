#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED
#include "Filaments.h"
#include <math.h>

/////////////////////////// GLOBEL VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define T_MAX           300
#define dt              0.001                        // [t]
#define r_n             100                         // [t]^-1
#define V_g_max         15.6                        // [l] / [t]        documented
#define v_s             0.1                         // [l] / [t]        documented
#define r_c             3                           // [t]^-1           documented
#define L_s             2000.0                      // [l]
#define p               1
#define bins            640
#define cos_grain       50

//////////////// uitbreiding ///////////////
#define B_tot           1
#define B_s             0.55
#define r_u             850
#define r_b             0.13
#define MSR             70
#define MSr             0.27
#define q               17


////////////////////// DERIVED VARIABLES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const double P_cap = r_c * dt;
const double dl_s = v_s * dt;
const double bin_size = (L_s / cos_grain) / bins;
const int time_steps = T_MAX / dt;


#endif // PARAMETERS_H_INCLUDED
