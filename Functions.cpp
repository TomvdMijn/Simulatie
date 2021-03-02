#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <functional>
#include<cmath>
#include <sstream>
#include "Declarations.h"
#include "PARAMETERS.h"
#include "Filaments.h"

using namespace std;


double a_growing [bins];
double a_shrinking [bins];
double length_F [time_steps];
double turnover_time [time_steps];
double length_FG [time_steps];
vector<Filament> collection;
string file_name;
extern double R_s;
extern double L_tot;
double B_a;
double L_G;
double dl;
double dl_tot;



///// initial conditions
int outlier = 0;
int total = 0;
double points = 0;
int deads = 0;
int severed = 0;
double L_F = 0;


double B(double L_G){
    return r_u * B_tot / (r_u + r_b * L_G);
}

double r_sev(){
//    return (MSR - MSr) * (pow(B_s, q) / (pow(B_s, q) + pow(B_a, q))) + MSr;
    return R_s;
}

double r_nuc(double L_G){
    return (r_n * pow(L_G, p)) / (pow(L_s, p) + pow(L_G, p));
}

double v_g(double L_G){
    return ((V_g_max * L_G) / (L_s + L_G) - v_s);
}

double dl_g(double L_G){
    return  v_g(L_G) * dt;
}

double N_nuc(double L_G){
    double lambda =  r_nuc(L_G) * dt;
    return Poisson(lambda);
}


////// main functions //////
void offset(double dL){
    int nbr = dL / (V_g_max / r_c);
    double sz = dL / nbr;
    for (int i = 0; i < nbr; i++){
        Filament new_filament(sz);
        new_filament.cap();
        collection.push_back(new_filament);
        total++;
        dl_tot = dl_tot - sz;
        L_F = L_F + new_filament.size;
    }
    L_G = L_G + dl_tot;
}

void measure(){
    B_a = B(L_G);
    L_F = 0;
    for(auto& filament : collection){
        int bin = filament.size / bin_size;
        L_F = L_F + filament.size;
        // delete outlier value the next run
        if(bin >= bins){
            outlier ++;
        } else if (filament.state == SHRINKING){
            a_shrinking [bin] ++;
        } else {
            a_growing [bin] ++;
        }
    }

    //cout << "subtotal: " << L_G + L_F << endl;

}

void evolve(){
    dl = dl_g(L_G);
    dl_tot = 0;
    for(auto& filament : collection) {
        points++;
        filament.age += dt;
        double rndm = rnd();
        // In case a filament is in a growing state.
        if (filament.state == GROWING) {
            if (rndm < P_cap) {
                // 1: capped
                filament.cap();
            } else if (rndm < (P_cap + filament.size * r_sev())) {
                // 2: severed at a random position.
                double dl_s_temp = rnd() * filament.size;
                Filament new_filament(dl_s_temp);
                new_filament.state = SHRINKING;
                collection.insert(collection.begin(), 1, new_filament);
                total++;
                severed++;
                filament.severing(dl_s_temp);
            } else {
                // 3 Grow
                filament.grow();
                dl_tot = dl_tot - dl;
            }
        } else {
            // A filament in a shrinking state has two options:
            if (rndm < filament.size * r_sev()) {
                // 1: severed at random position.
                double dl_s_temp = rnd() * filament.size;
                Filament new_filament(dl_s_temp);
                new_filament.state = SHRINKING;
                collection.insert(collection.begin(), 1, new_filament);
                total++;
                severed++;
                filament.severing(dl_s_temp);
            } else {
                // 2a shrink the last piece of a filament
                if (filament.size < dl_s) {
                    dl_tot = dl_tot + filament.size;
                    filament.size = 0;
                    filament.state = DEAD;
                    deads++;
                } else {
                    // 2b shrink piece of bigger filament.
                    filament.shrink();
                    dl_tot = dl_tot + dl_s;
                }
            }
        }
    }
    // deletes all dead filaments from collection
    for (vector<Filament>::iterator filament = collection.begin(); filament!=collection.end(); /*it++*/) //<----------- I commented it.
    {
        if(filament -> state == DEAD)
            filament = collection.erase(filament);
        else
            ++filament;
    }
}

void nucleation(){
    int nbr = N_nuc(L_G);
    double dls = dl * rnd();
    double sum_new = 0;
    for (int i = 0; i < nbr; i++){
        Filament new_filament(dls);
        collection.push_back(new_filament);
        total++;
        dl_tot = dl_tot - dls;
        L_F = L_F + new_filament.size;
        sum_new = sum_new + new_filament.size;
    }
    L_G = L_G + dl_tot;
}

void writing(double arry[], string name, int size){
    ofstream dummy;
    // Create data file for the growing data
    dummy.open("/Users/tomphilipvandermijn/Documents/Resultaten/" + file_name + "_" + name + ".txt");

    // Write date to file, separated by a space
    for (int i = 0; i < size; i++){
        dummy << arry[i] << ", ";
    }

    // Close the file
    dummy.close();
}

void update_results(int t){
    length_F [t] = L_F;
    turnover_time [t] = ((r_c / (r_nuc(L_G) * v_g(L_G))) * L_F);
    length_FG [t] = L_F/L_G;
}

void writing_results(){
    cout << endl << endl << "totaal aantal outliers: " << outlier << endl;
    cout << "totaal aantal filamenten: " << total << endl;
    cout << "totaal aantal punten: " << points << endl;
    cout << "totaal aantal doden: " << deads << endl;
    cout << "totaal aantal geknipte: " << severed << endl;


    writing(a_growing, "growing", sizeof(a_growing) / sizeof(a_growing[0]));
    writing(a_shrinking, "shrinking", sizeof(a_shrinking) / sizeof(a_shrinking[0]));
    writing(length_F, "length", sizeof(length_F) / sizeof(length_F[0]));
//    writing(turnover_time, "turnover", sizeof(turnover_time) / sizeof(turnover_time[0]));
//    writing(length_FG, "length_FG", sizeof(length_FG) / sizeof(length_FG[0]));
}



///// extra functions ////

string time_stamp()
{
    time_t now = time(NULL);
    tm *ltm = localtime(&now);
    // convert now to string form
    string del_t = to_string(1 + ltm->tm_mon) + "_" + to_string(ltm->tm_mday) + "_" + to_string(ltm->tm_hour) + "_" + to_string(ltm->tm_min) + "_" + to_string(ltm->tm_sec);

    return del_t;
}

void stamp()
{
    // create file were parameters are written to
    char ch;
    file_name = time_stamp();                                    // create a file name
    ofstream f;
    f.open("/Users/tomphilipvandermijn/Documents/Resultaten/" + file_name + "_parameters_con.txt");    // create file in seperate folder

    ifstream f_2;
    f_2.open("/Users/tomphilipvandermijn/Documents/Simulatie/PARAMETERS.h");
    if(!f_2.is_open() && !f.is_open()){                                         // check if files opened
        cout << "Oh no, didnt open the file" << endl;
    }

    while (!f_2.eof()) {
        f_2.get(ch);                                                         //reading from file object reading
        f << ch;                                                                // writing to file.
    }
    f.close();
    f_2.close();
}

void write_stamp(double sigma, double lambda)
{
    char ch;
    ofstream f;
    f.open("/Users/tomphilipvandermijn/Documents/Resultaten/" + file_name + "_parameters_var.txt");
    f << "simga:  " << sigma << endl;
    f << "lambda: " << lambda << endl;
    f.close();
}

double rnd()
{
    random_device device;                                             // generates random seed (very slow)
    mt19937 generator(device());                                      // PRNG that uses Mersenne twister
    uniform_real_distribution<double> distribution(0,1);        // distribution
    double rndm = distribution(generator);
    return rndm;
}

// Knuth's algorithm returns an integer
double Poisson(double lambda){
    int k = 0;
    double pp = 1.0;
    double L = exp(-lambda);
    while (pp > L){
        k++;
        pp = pp * rnd();
    }
    return k - 1;
}
/*
    if(filament.state == GROWING && rnd() < P_cap){
        filament.cap();
    } else if (rnd() < R_s * filament.size * dt){
        // sever the filament at a random position.
        double dl_s_temp = rnd() * filament.size;
        Filament new_filament (dl_s_temp);
        new_filament.state = SHRINKING;
        collection.push_back(new_filament);
        total++;
        severed++;
        filament.severing(dl_s_temp);
    } else if (filament.state == SHRINKING){
        if(filament.size < dl_s){
            double dl_s_temp = filament.size;
            dl_tot = dl_tot + dl_s_temp;
            filament.size = 0;
            filament.state = DEAD;
        }
        filament.shrink();
        dl_tot = dl_tot + dl_s;
    } else {
        filament.grow();
        dl_tot = dl_tot - dl;
    }
}
 */
