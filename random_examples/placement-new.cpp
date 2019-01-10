/*
C++ example code: using the placement-new method for object array initialisation
without invoking the default constructor.

This avoids gratuitous default constructors.

In general, placement-new is a powerful method that allows us to split the usual function
of NEW into separate steps; we pass a preallocated memory and construct an object in the
passed memory.
The key step is allocation of raw memory with the OPERATOR NEW[] syntax.
*/

#include <new>
#include <iostream>
using namespace std;

class Car {
    int _no;
public:
    Car( int no ) :_no( no ) { // parameterised constructor
    }
    int get_car_no () { return _no; }
};

int main() {
    int NUM_CARS = 5;
    void* raw_memory = operator new[]( NUM_CARS * sizeof( Car ) );
    Car* ptr = static_cast<Car*>( raw_memory );
    for( int i = 0; i < NUM_CARS; ++i ) {
        new( &ptr[i] )Car( i );
        cout << "i = " << i << "\tCar(i)._no = " << Car(i).get_car_no() << "\n";
    }
    // destruct in inverse order    
    for( int i = NUM_CARS - 1; i >= 0; --i ) {
        ptr[i].~Car();
    }
    operator delete[]( raw_memory );
    return 0;
}
