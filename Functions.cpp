#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <functional>
using namespace std;
#include "Declarations.h"
#include "PARAMETERS.h"
#include "Filaments.h"
int shrink_ctr = 0;
int grow_ctr = 0;
int outlier = 0;

void nucleation(){
    Filament new_filament;
    if (rnd() < P_nuc){
        collection.push_back(new_filament);
    }
}

void evolve(){
    for(auto& filament : collection){
        filament.age += dt;
        if(filament.state == SHRINKING){
            filament.shrink();
            if(filament.size < 0){
                filament.state = DEAD;
            }
        } else if (filament.state == GROWING && rnd() < P_cap){
            filament.cap();
        } else {
            filament.grow();
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

void measure(){
    for(auto& filament : collection){
        int bin = filament.size / bin_size;
        // delete outlier value the next run
        if(filament.size > L_s){
            outlier ++;
            filament.size = 0;
            filament.state = SHRINKING;
        } else if (filament.state == SHRINKING){
            a_shrinking [bin] ++;
        } else {
            a_growing [bin] ++;
        }
    }
}

void update_results(){
    cout << outlier << endl;
    ofstream f_growing;
    // Create data file for the growing data
    f_growing.open("/Users/tom/ownCloud/Resultaten/" + file_name + "_growing");
    // Write date to file, separated by a space
    for (auto i : a_growing){
        f_growing << i << " ";
    }
    // Close the file
    f_growing.close();
    ofstream f_shrinking;
    // Create data file for the shrinking data
    f_shrinking.open("/Users/tom/ownCloud/Resultaten/" + file_name + "_shrinking");
    // Write data to file, separated by a space
    for (auto i : a_shrinking){
        f_shrinking << i << " ";
    }
    // Close the file
    f_shrinking.close();
}


string time_stamp()
{
    time_t now = time(NULL);

    // convert now to string form
    string del_t = ctime(&now);

    return del_t;
}

void stamp()
{
    // create file were parameters are written to
    char ch;
    file_name = Project_name + time_stamp();                                    // create a file name
    ofstream f;
    f.open("/Users/tom/ownCloud/Resultaten/" + file_name + "_parameters");    // create file in seperate

    ifstream f_2;
    f_2.open("/Users/tom/ownCloud/Simulatie/PARAMETERS.h");
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


double rnd()
{
    random_device device;                                             // generates random seed (very slow)
    mt19937 generator(device());                                      // PRNG that uses Mersenne twister
    uniform_real_distribution<double> distribution(0,1);        // distribution
    double rndm = distribution(generator);
    return rndm ;
}

