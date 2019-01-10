/*
C++ example demonstrating how one can initialise an array of pointers to a class using NEW
*/

#include <iostream>
using namespace std;

class Fish; // forward declaration of class Fish

// tank contains an array of pointers to fish (of type Fish class)
class Tank {

    public:

    Fish **fish; // fish represents an array of pointers to type Fish class
    int _tank_size; // how many fish can the tank hold?
    Tank(int tank_size);
    ~Tank();

} the_tank(5); // instance of Tank class that can hold 5 fish

class Fish {

    public:

    int _length;
    Fish () {};
    Fish (int length);
    void set_length(int length) { _length = length; };
};

Tank::Tank(int tank_size) {
    _tank_size = tank_size;
    // free memory for pointers to the Fish, contained in an array
    // (Fish*) is a pointer to class Fish
    cout << "in constructor\n";
    fish = new Fish* [_tank_size]; // NB NEW calls (implicitly defined) default constructor
    for (int i=0;i<_tank_size;i++) {
        fish[i] = new Fish(); // create new instances of Fish class as elems of the fish array
    }
}

Tank::~Tank () {
    for (int i=0;i<_tank_size;i++) {
        delete fish[i];
    }
    delete [] fish;
}

Fish::Fish(int length) {
    _length = length;
}

int main () {

    
    for (int i=0;i<the_tank._tank_size;i++) {
        the_tank.fish[i]->set_length(double(i)*2.);
        cout << "address of fish i: " << &(the_tank.fish)+i << \
                "  length of the fish: " << the_tank.fish[i]->_length << "\n";
    }
    

    return 0;
}
