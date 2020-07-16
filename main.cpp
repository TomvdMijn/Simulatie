#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "Declarations.h"
#include "Filaments.h"
#include "PARAMETERS.h"
using namespace std;

vector<Filament> collection;
int a_growing [bins];
int a_shrinking [bins];
string file_name;
int main()
{
    /////////////// Initialisation ///////////////
    stamp();

    /////////////// Model ///////////////
    for(int t = 0; t < time_steps; t++) {
        cout << t << endl;
        evolve();
        measure();
        nucleation();
    }

    /////////////// Writing data ///////////////
    update_results();

    return 0;

}





/*
vector <filament> filament_ctr;              // create group of filaments
while (int t < T_max){                       // iterate over time
    nucleation()
    t++
*/
/*
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