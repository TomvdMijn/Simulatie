#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <functional>
#include "Declarations.h"
using namespace std;
/*    void Filament::growing()
    {
        length = length + (V_g - V_s) * dt;
    }
    void shrinking()
    {
        length = length - V_s * dt;
    }
    void capping()
    {
        state = states[1];
    }

    // generates uniformly a random number between 0 and 1 by using the rdmg mt19937 which uses a mersenne twister algorithm
    double rnd()
    {
        mt19937::result_type seed = 2;
        auto real_rand = std::bind(std::uniform_real_distribution<double>(0,1),
                           mt19937(seed));
        return real_rand();
    }

    void nucleation()
    {
        if (rdm() < P_nuc){

        }
    }


    void Stamp()
    {
        time_t now = time(0);

        // convert now to string form
        char* dt = ctime(&now);

        // attach timestamp to filename
        string filename = "Test ";
        filename =  filename + dt;

        // create file with filename
        ofstream f;
        f.open( C:filename.c_str() );
        f.close();
  }

  void check_filaments()
  {
    for (auto f : filament_ctr){             // Iterate over filaments
            if(f.state == growing)
            {
                if (rdm() < P_c){
                    f.capping();
                } else if (rdm() < P_c){
                    severing();
                } else {
                    f.growing();
                }

            } else {

            }
        }
  }

void Stamp()
    {
        // create file with filename
        ofstream f;
        f.open(string("/home/ipausers/vdmijn/ownCloud/Documents/Particle-based stochastic model for actin duynamics/Resultaten/") + filename );
        f << "yeah kijk is aan" << endl;
        f.close();
  }
string("c://home/ipausers/vdmijn/ownCloud/Documents/Particle-based stochastic model for actin duynamics/Resultaten/"
*/

string Time_stamp()
{
    time_t now = time(0);

    // convert now to string form
    string dt = ctime(&now);

    return dt;
}

void Stamp()
{
    // create file with filename
    fstream f;
    //char ch;
    f.open("eindelijk");
    //reading.open("PARAMETERS.h");
    if(!f.is_open()){
        cout << "Oh no, didnt open the file" << endl;
    }
    f << "hello world";
    //while (!reading.eof()){
    //    reading.get(ch);    //reading from file object reading
        //cout << ch;         //cout << ch;
    //    writing << ch;  //writing to file.
    //}
    //reading.close();
    f.close();
}
