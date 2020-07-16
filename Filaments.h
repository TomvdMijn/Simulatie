#ifndef FILAMENTS_H_INCLUDED
#define FILAMENTS_H_INCLUDED
#include "PARAMETERS.h"

using namespace std;
enum states{GROWING, SHRINKING, DEAD};
class Filament{
    public:

        double size;
        double age;
        states state;

        Filament(){
           size = 10;
           age = 0;
           state = GROWING;
        }


    void grow()
    {
        size = size + (V_g - V_s) * dt;
    }

    void shrink()
    {
        size = size - (V_s * dt);
    }

    void cap()
    {
        state = SHRINKING;
    }

};

#endif // FILAMENTS_H_INCLUDED





/*
class Node{
        public:
        int size;
        Node* next = NULL;
        Node* previous = NULL;

        Node(int x = 0){
            size = x;
        }

    };

class LinkedList{
    public:
        Node* head = NULL;
        Node* tail = NULL;

        void add_node(int x){
            Node *tmp = new Node;
            tmp->size = x;
            tmp->next = NULL;
            tmp->previous = tail;

            if(head == NULL)
            {
                head = tmp;
                tail = tmp;
            } else {
                cout << tail -> size << endl;
                tail->next = tmp;
                tail = tail->next;
                //cout << tail -> previous -> size << endl;
            }

        }
        void print_list(){
            Node* current_node = head;
            while (current_node){
                    //cout << current_node -> size << endl;
                    if (current_node -> previous != NULL && current_node -> next != NULL){
                        cout << "previous: " << current_node -> previous -> size << " current: " << current_node -> size <<  " next: " << current_node ->next -> size << endl;
                    }
                    current_node = current_node -> next;
                }
        }



        void remove(){

        }

};

 */