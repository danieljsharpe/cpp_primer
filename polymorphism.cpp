/* Demonstration of polymorphism in C++ classes */

#include <iostream>

using namespace std;

class Animal {

    protected:

    int height, weight;

    public:

    Animal (double x, double y) : height(x), weight(y) {}

    void update_values(double x, double y) {
        height = x;
        weight = y;
    }

    double get_height() { return height; }
    double get_weight() { return weight; }
    virtual double get_property() { return 0.; }
    virtual int get_type() =0; // pure virtual member function (Animal is therefore an abstract
                               // base class)
    void print_type() { std :: cout << this->get_type() << "\n"; }
};

class Bird: public Animal {

    public:

    double wingspan;

    Bird (double x, double y, double z) : wingspan(z), Animal (x,y) {}

    double get_property() { return wingspan; }
    int get_type(void) { return 1; } // "void" argument is optional here
};

class Fish: public Animal {

    public:

    double fin_length;

    Fish (double x, double y, double z) : fin_length(z), Animal (x,y) {}

    double get_property() { return fin_length; }
    int get_type(void) { return 2;}
};

int main () {

    Bird flamingo(125.,2300.,100.);
    Fish tuna(15.,1800.,20.);

    std :: cout << "Height of flamingo is: " << flamingo.get_height() << "\n";

    /* One of the key features of class inheritance is that a pointer to a derived class is type-
       compatible with a pointer to its base class. Polymorphism is the art of taking advantage
       of this simple but powerful and versatile feature.
       Below, animal1 is a pointer to an object of class Animal, but we can assign to the address
       of an object of class Bird, since Bird is a derived class of base class Animal */
    Animal * animal1 = &flamingo;
    Animal * animal2 = &tuna;

    /* Dereferencing the above pointers of type Animal is valid, and allows us to access the
       members of their pointed objects */
    animal1->update_values(130.,2400.);
    (*animal2).update_values(18.,1900.); // recall: (*x).y is equivalent to x->y

    std :: cout << "Flamingo has grown, new height is: " << flamingo.get_height() << "\n";
    std :: cout << "Tuna has also grown, new weight is: " << tuna.get_weight() << "\n";

    /* Because the type of the pointers declared above is the base class Animal, only the members
       of the objects flamgo & tuna that are inherited from the base class Animal can be accessed
       via the pointer, and not members belonging to the derived classes Bird & Fish,
       respectively. Hence the following is not legal: */
    // animal1->wingspan; // is not valid: wingspan is not a member of the base class Animal, which
                          // is the type of the pointer
    
    /* If we define a pointer of type corresponding to the derived class, then members declared in
       both the derived classes and the base class(es) are accessible via the pointer...
       This is POLYMORPHISM */
    Bird * bird1 = &flamingo;

    std :: cout << "Wingspan of the flamingo: " << bird1->wingspan << "\n";
    std :: cout << "Weight of the flamingo: " << bird1->get_weight() << "\n";

    // VIRTUAL MEMBERS
    /* A virtual member is a member function that can be redefined in a derived class, while
       preserving its calling properties through references. The syntax for a function to become
       virtual is to precede its declaration (in the base class) with the "virtual" keyword.
       In the below example, the virtual member function get_property() returns wingspan for the
       Bird derived class, fin_length for the Fish derived class, and a default value (0.) for
       the Animal base class */
    Fish * fish1 = &tuna;

    std :: cout << "Wingspan of the flamingo: " << bird1->get_property() << "\n";
    std :: cout << "Fin length of the fish: " << fish1->get_property() << "\n";
    /* Note that non-virtual members can also be redefined in derived classes, but non-virtual
       members of derived classes cannot be accessed through a reference of the base class, whereas
       virtual members can. For non-virtual members, a call via a derived class will always call
       the version of the function that appears in the pointer type declaration.
       Therefore, essentially, what the virtual keyword does is to allow a member of a derived
       class with the same name as the one in the base class to be appropriately called from a
       pointer, and more precisely when the type of the pointer is a pointer to the base class
       that is pointing to an object of the derived class, as in the following example: */
    std :: cout << "Wingspan of the flamingo: " << animal1->get_property() << "\n";
    std :: cout << "Fin length of the fish: " << (*animal2).get_property() << "\n";
    /* If the get_property() function was not virtual, then the above 2 lines would return 0., as
       the base class (pointer type of animal1 is base class Animal) member function would be
       called. The two lines before that, however, would still return the wingspan and fin_length,
       respectively, as the respective pointers have types corresponding to the relevant
       derived classes.
       A class that declares or inherits a virtual function is a POLYMORPHIC CLASS. */

    // ABSTRACT BASE CLASSES
    /* Abstract base classes are classes that can only be used as base classes, and thus are allowed
       to have virtual member functions without definition (known as PURE VIRTUAL FUNCTIONS). The
       syntax is to replace their definition by "=0".
       With the inclusion of the get_type() pure virtual member function in the base class
       Animal, Animal is an abstract base class (such a class is defined as one containing at least
       one pure virtual member function.
       Abstract base classes *cannot* be used to instantiate objects, hence we cannot use an
       abstract base class to declare object like so: */
    // Animal puffin; // not valid, Animal is an abstract base class
    /* But we can create pointers to an abstract base class, and take advantage of all its
       polymorphic abilities, and e.g. the pointers can be dereferenced when pointing to objects of
       derived (non-abstract) classes, like so: */
    Bird puffin(18.,500.,50.);
    Animal * animal3 = &puffin;

    std :: cout << "Type identifier for animal #3: " << animal3->get_type() << "\n";
    std :: cout << "Type identifier for animal #2: " << (*animal2).get_type() << "\n";
    /* In this example, objects of different but related types are referred to using a unique type
       of pointer (Animal*) and the proper member function (i.e. of the correct derived class) is
       called every time, owing to use of the virtual property.
       It is possible for a member of the abstract base class Animal to use the special pointer "this"
       to access the proper virtual members, even though Animal itself has no implementation for
       this function... */
    std :: cout << "Using 'this' pointer in base class to find type identifier for animal #3: ";
    animal3->print_type();

    /* Virtual members and abstract classes grant C++ polymorphic characteristics. Such features can
       also be applied to arrays of objects or dynamically allocated objects: */
    // Note that the following pointer is declared as being of type "pointer to Animal", but the
    // object allocated has been declared having the derived class type (Bird) directly:
    Animal * animal4_emu = new Bird(170.,5000.,110.);
    std :: cout << "Wingspan of emu: " << animal4_emu->get_property() << "\n";
    delete animal4_emu;

    return 0;
}
