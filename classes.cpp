#include <iostream>

using namespace std;


class Birds { // Identifier for the class

    protected: /* protected members are accessible from other members of the same class (or from their
                  "friends", and also from members of their derived classes.
                  Other access specifiers: private (members accesible only from within members of the same
                  class, or their "friends", and public (members accessible from anywhere where object
                  is visible */

    double wingspan; // protected (or private) variable cannot be accessed from instantiation
                     // of object in main()

    // protected (or private) function cannot be accessed from instantiation of object in main()
    int estimate_popn(int protect_status) {
        if (protect_status == 0) {return 10000;}
        else if (protect_status == 1) {return 50000;}
        else {return 100000;}
    }

    public:

    void set_values(int,double); // a member function declared here with prototype within class, but defined outside class
    Birds (int,double); // let us declare the constructor here. Constructors can be inline (defined within class)
                        // or not inline (defined outside of class) (as here. Needs to be declared within class).
    Birds (); // alt constructor (constructor is overloaded)

    ~Birds () {n_instances--;} // destructor is called when object falls out of scope

    int no_of_eggs;

    int find_flock_size(int x) {
        if (x == 0) {return 1;}
        else if (x == 1) {return 10;}
        else {return 100;}
    }

    /* A STATIC member of a class (either variable or function) is also known as a 'class variable'
    because there is only one common variable for all the objects of that same class, sharing the
    same value.
    One common use is as a counter for the number of instances of the object that have been created*/
    static int n_instances;
    static void make_bird_noise();

    /* The member functions of a CONST object can only be called if they are themselves specified as
       const members. To specify that a member function is a const member, the const keyword follows
       the function prototype, after the closing parenthesis for its params */
    void lay_egg() const {std :: cout << "Laying an egg\n";}
    /* Note that const can be used to qualify the type returned by a member function. This const is
       not the same as the one which specifies a member as const. Both are indep and are located at
       different places in the function prototype */
    const int& lay_x_eggs() {return no_of_eggs;} // member function returning a const&
    const int& lay_eggs_const() const {return no_of_eggs;} // const member function returning a const&

    /* Let us declare the (protected) function estimate_popn() in Birds as a friend of main(),
       so that we are able to call it from within main */
    friend int main();

} duck, goose; // instantiations of class (optional)

/* The scope operator, ::, is used to define a member of the class outside the class itself. The scope operator
specifies the class to which the member being defined belongs, granting exactly the same scope properties as if
this function definition was directly included within the class definition.
Here the function sets (or updates) values for member variables of the class.
Must also be declared as being in the scope of the class. */
void Birds::set_values (int x, double y) {
    no_of_eggs = x;
    wingspan = y; // protected and private members of the class can be accessed, as normal
}

/* This is the CONSTRUCTOR for the class. A constructor is a special member function that is automatically
called whenever a new object of the class is instantiated, allowing the class to initialise member variables,
allocate storage etc.
The constructor function is declared just like a regular member function, but with a name that matches the class
name and without any return type (not even void!)
Constructors cannot be called explicitly as if they were regular member functions. They are only executed once,
when a new object of that class is created. */
Birds::Birds (int x, double y) {
    std :: cout << "Calling the constructor w/ arguments\n";
    n_instances++;
    set_values(x,y);
}
/* Like any other function, a constructor can be overloaded with different versions taking a different no, of
params and/or different param types. The compiler will automatically call the one whose parameters match the
arguments.
A constructor that takes no parameters (so-called default constructor) is special. It is called when an object
is declared but is not initialised with any arguments, i.e. it is called for, e.g.: Birds emu;, but NOT
e.g.: Birds emu(); */
Birds::Birds () {
    std :: cout << "Calling the default constructor\n";
    n_instances++;
    set_values(1,1.);
}

/* Static members have the same properties as non-member variables but they enjoy class scope.
For that reason, and to avoid them having to be declared several times, they cannot be
initialised directly in the class, but need to be initialised somewhere outside it */
int Birds::n_instances=0; // initially no objects of class Birds are instantiated

/* Classes can also have static member functions. These represent the same: members of a
class that are common to all objects of that class, acting exactly as non-member functions but
being accessed like members of the class. They cannot access non-static members of the class,
neither member variables nor member functions, and cannot use the keyword "this".
Note that the "static" keyword is given when declaring, not when defining */
void Birds::make_bird_noise () { std :: cout << "hoot! quack! honk!\n"; };

/* Objects can be pointed to by pointers. *Once declared*, a class becomes a valid type, so it can be used
as the type pointed to by a pointer.*/
Birds * bird_ptr_1, * bird_ptr_2, * bird_ptr_3; // pointer to an object of class Birds

int main() {

    int goose_flock_size;

    Birds swan(4,6.); // new object (instance of class). The arguments are the arguments to the constructor.
    goose.no_of_eggs = 3; // access members by the general syntax: object_name.member_name
    goose_flock_size = goose.find_flock_size(0); // same syntax for calling member functions
    std :: cout << "Number of goose eggs: " << goose.no_of_eggs << " Size of goose flock: " << goose_flock_size << "\n";
    swan.set_values(4,5.); // update values of members

    // example use of pointers to classes
    bird_ptr_1 = &swan; // assign pointer to address of object being pointed to
    bird_ptr_2 = new Birds (3,6.); // assign pointer to a new object of the class
    bird_ptr_3 = new Birds[2] {{2,4.2},{8,5.6}}; // assign pointer to an array of new objects of the class
    std :: cout << "No. of eggs of 3rd bird: " << bird_ptr_3->no_of_eggs << "\n";
    std :: cout << "Flock size of 2nd bird: " << bird_ptr_2->find_flock_size(1) << "\n";
    // N.B. Use of (*x).y is equivalent to x->y :
    std :: cout << "No. of eggs of 3rd bird: " << (*bird_ptr_3).no_of_eggs << "\n";
    // Recall that x[n] is the (n+1_th object pointed to by x :
    std :: cout << "No. of eggs of 4th bird: " << bird_ptr_3[1].no_of_eggs << "\n";
    delete bird_ptr_2;
    delete[] bird_ptr_3;

    /* static members are accessed through the scope (::) operator (since they are not tied to any
       particular instance of the class, but rather to the class itself), but can also be accessed
       in the same way as non-static members... */
    std :: cout << "Number of class instances active: " << Birds::n_instances << "\n";
    std :: cout << "Number of class instances active: " << swan.n_instances << "\n";
    Birds::make_bird_noise();
    swan.make_bird_noise();

    /* Constant member functions:
       When an object is qualified as a const object, the access to its data members from outside the
       class is restricted to read-only, as if all its data members were const for those accessing
       them from outside the class. Note though, that the constructor is still called an is allowed
       to initialise an modify these data members */
    const Birds ostrich;
    std :: cout << "Number of ostrich eggs: " << ostrich.no_of_eggs << "\n";
    // ostrich.no_of_eggs = 4; // is illegal: member variable of const object cannot be modified
    ostrich.make_bird_noise(); // static functions can be called from const objects
    // ostrich.find_flock_size(1); // is illegal: cannot call non-static funcs from const objects...
    ostrich.lay_egg(); // ...unless such functions are themselves constant
    std :: cout << "Ostrich lays this many eggs: " << ostrich.lay_eggs_const() << "\n";

    /* Recall that we declared main() to be a friend of class Birds, so we can call the protected
    (and private) functions of Birds within main() */
    std :: cout << "Estimate population size of swan: " << swan.estimate_popn(1) << "\n";

    // Aside: a quick note on exceptions
    try {
        throw 10;
    } catch (...) {
        std :: cout << "Test: an error has been manually thrown\n";
    }
    
    return 0;
}
