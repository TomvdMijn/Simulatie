#include <iostream>
#include "chrono"
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include "Declarations.h"
#include "Filaments.h"
#include "PARAMETERS.h"
#include <sstream>
#include <cstdlib>
using namespace std;
extern double L_F;
extern double L_G;
extern double dl_tot;

double lambda;
double sigma;
double R_s;
double L_tot;



int main(int argc, char** argv)
{
    auto start = chrono::steady_clock::now();
    /////////////// Initialisation ///////////////
    stamp();
    sigma = atof(argv[1]);
    lambda = atof(argv[2]);
    write_stamp(sigma, lambda);


    R_s = (sigma * pow(r_c,2) / v_s) * dt;
    L_tot = lambda * L_s;
    L_G = L_tot;


//    offset(4000);
    cout << "lambda: " << lambda << endl;
    cout << "sigma: " << sigma << endl;

    /////////////// Model ///////////////
    for(int t = 0; t < time_steps; t++) {
        if (t % 10000 == 0){
            cout << "step: " << t << endl;
            cout << L_F << endl;

        }
//
//        if (t == 4000){
//            L_G = L_G - 1500;
//        }
//        if (t == 8000){
//            L_G = L_G + 1500;
//        }

        measure();
        evolve();
        nucleation();
        update_results(t);
    }

    /////////////// Writing data ///////////////
    writing_results();


    auto end = chrono::steady_clock::now();

    cout << "Execution time: " << chrono::duration_cast<chrono::seconds> (end - start).count() <<" seconds" << endl;
    return 0;

}





/*
vector <filament> filament_ctr;              // create group of filaments
while (int t < T_max){                       // iterate over time
    nucleation()
    t++

// string filename = Project + Time_stamp();
//cout << filename << endl;
//Stamp();

LinkedList collection;

collection.add_node(5);
collection.add_node(10);
collection.add_node(12);
collection.add_node(15);
collection.add_node(20);
collection.add_node(25);

collection.print_list();

Node a;
a.size = 10;
Node b;
b.size = 20;
Node* ptr = &b;
Node c;
c.size = 30;

a.next = &b;
b.next = &c;


Node current_node = a;
Node next_node;
cout << current_node.size << endl;
next_node = *current_node.next;
cout << next_node.size << endl;
*/


//cout << a.next << endl;
//cout << ptr << endl;
//cout << b.next  << endl;


/* Test Poisson distribution
 *
    cout << Poisson(4) << endl;

    double lamb = 4;
    int pois [20] = {0};
    for (auto &l : pois){
        cout << l << endl;
    }
    int ctr;
    for (int t = 0; t <= 100000; t++){
        int result = Poisson(lamb);
        cout << result << endl;
        if (result < 20 && result >= 0){
            cout << result << endl << endl;
            ctr++;
            pois [result] ++;
        }
    }
    for (auto &l : pois){
        cout << l << endl;
    }

    ofstream f_poi;
    f_poi.open("/Users/tomphilipvandermijn/Documents/Resultaten/poisson_test.txt");
    for (auto i : pois){
        f_poi << i << ", ";
    }
    f_poi << endl << endl << "ctr = " << ctr << endl;
    f_poi << "lambda = " << lamb << endl;
    f_poi.close();
 */
