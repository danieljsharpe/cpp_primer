/* Demonstration of const member functions in C++
Member functions specified to be CONST cannot modify non-static data members nor call other non-
const member functions. In essence, const members shall not modify the state of an object.
CONST objects are limited to access only member functions marked as const, but non-const objects
are not restricted and thus can access both const and non-const member functions alike.
*/

#include <iostream>

using namespace std;

class Birds {

    public:

    int n_birds;

    /* Note the use of alternative syntax syntax for a parameterised constructor.
       The colon syntax specifies use of an initialisation list to initialise fields. If there are
       multiple fields to be initialised, they are comma-separated. */
    Birds(int x) : n_birds(x) {}

    /* Member functions can be overloaded on their constness. i.e. a class may have two member
       functions with identical signatures except that one is const and the other is not. In this
       case, the const version is called only when the object is itself const, and the non-const
       version is called when the object is itself non-const. */
    int get_n_birds() {return n_birds;} // non-const member function
    const int& get_n_birds_const() {return n_birds;} // non-const member function returning a const&
    int get_n_birds() const {return n_birds;} // const member function
    const int& get_n_birds_const() const {return n_birds;} // const member function returning a const&
};

/* CONST objects are actually very common - (most) functions taking classes as parameters actually
take them by const reference. Thus, these functions can only access their const members.
Therefore it is actually often worth marking all members that don't modify the object as const. */
void print_n_birds (const Birds& bird) {
    // recall const objects, such as being passed as a parameter to this function, only have access
    // to const member functions
    std :: cout << "Number of birds: " << bird.get_n_birds_const() << "\n";
}

int main() {

    const Birds flamingo(10); // create const object of class Birds
    // flamingo.n_birds = 20; // is illegal: flamingo is a const object of the class, so its (non-
                              // static) members cannot be modified
    std :: cout << "Number of flamingos: " << flamingo.n_birds << "\n";
    // flamingo.get_n_birds(); // is illegal: const object cannot call non-const functions
    // But const objects can call member functions that are themselves specified as const members:
    std :: cout << "Number of flamingos: " << flamingo.get_n_birds_const() << "\n";

    print_n_birds(flamingo);

    return 0;
}
