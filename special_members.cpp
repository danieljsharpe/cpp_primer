/* Demonstration of the use of special members in C++ classes.
   There are six SPECIAL MEMBER FUNCTIONS that are implicitly defined as members of a class under
   certain circumstances. These are:
   Default constructor, destructor, copy constructor, copy assignment, move constructor,
   move assignment */

#include <iostream>
#include <string>

using namespace std;

class Birds2 {

    public:
    double * birds2ptr;
};

class Birds {

    private:

    string species;
    string* habitat = nullptr;
    double wingspan;

    public:

    double height, weight;

    /* The DEFAULT CONSTRUCTOR is the constructor called when objects of a class are declared, but
       are not initialised with any arguments. If a class definition has no constructors, then the
       compiler assumes the class to have an implicitly defined default constructor. But if a
       class includes a declaration for one or more parameterised constructors, where any number of
       arguments are explicitly declared, then the compiler no longer provides an implicit default
       constructor, and no longer allows the declaration of new objects of that class without
       arguments. Then, if we want to be able to instantiate ojects with no arguments, we have to
       explicitly declare the default constructor in the class. */
    Birds() { // default constructor
        std :: cout << "\nCalled the default constructor\n"; }
    // parameterised constructors (overloading; one or two args):
    Birds (const string& str) : species(str) {
        std :: cout << "\nCalled the parameterised constructor (w/ 1 arg)\n"; };
    Birds (const string& str1, const string &str2) : species(str1), habitat(new string(str2)) {
        std :: cout << "\nCalled the parameterised constructor (w/ 2 args)\n"; }

    /* A DESTRUCTOR essentially fulfils the opposite functionality of constructors: they are called
       when the class falls out of scope and are responsible for the necessary cleanup needed by a
       class when its lifetime ends. A common usage is to clear up any allocated resources. */
    ~Birds() { delete habitat; } // destructor

    /* When an object is passed a named object of its own type as an argument, its COPY CONSTRUCTOR
       is invoked in order to construct a copy. A copy constructor is a constructor whose first
       parameter is of type: 'reference to the class itself' (and possibly "const" qualified), and
       which can be invoked with a single argument of this type. */
    // Birds (const Birds& x) : species(x.get_species()) {} // copy constructor
    /* If a class has no custom copy nor move constructors (or assignments) defined, an implicit
       copy constructor is provided, which simply performs a copy of its own members
    // e.g. implicit (default) copy constructor for a class MyClass that has members a, b & c is
    // roughly equivalent to:
    // MyClass (const MyClass& x) : a(x.a), b(x.b), c(x.c) {}
       The copy constructor function defined on the previous line performs a SHALLOW COPY, only
       copying the members of the class themselves. However, if a class contains pointers, then
       a shallow copy will copy pointer *values*, but not the content itself. This means that both
       objects (the copy and the original) would be sharing a single object (i.e. the relevant
       pointer of each would be pointing to the same object) and at some point (i.e. on destruction)
       both objects would try to delete the same block of memory, probably causing the program to
       crash on runtime. This can be solved by defining a custom copy contructor that performs a
       so-called DEEP COPY */
    Birds (const Birds& x) : species(x.get_species()), habitat(new string(x.get_habitat())) {
        std :: cout << "\nCalled the copy constructor\n"; }
    /* Note that copy constructors cannot be overloaded, we can only define one */

    /* Objects are not only copied on construction, when they are initialised: they can also be
       copied on any assignment operation. If a class object is initialised on construction, then
       the copy constructor is called. Note that this is *not* an assignment operation, even though
       the syntax uses "=". If, however, an assignment operation is performed on an existing object
       (that was declared / initialised on a previous line), then the COPY ASSIGNMENT operator is
       called.
       The copy assignment operator is an overload of "operator=", which takes a *value* or
       *reference* of the class itself as a parameter. The return value is generally a reference to
       "*this" (although this is not required). */
    // The following copy assignment operator performs a shallow copy, and is the explicit equivalent
    // of what is defined implicitly:
    // Birds& operator= (const Birds&);
    /* Like for copy constructors, if the class contains pointers, then to avoid memory leaks (e.g.
       by not deleting the object pointed by the object before the assignment), we need a copy 
       assignment that deletes the previous object and performs a deep copy*/
    Birds& operator= (const Birds& x) {
        std :: cout << "\nCalled the copy assignment operator\n";
        delete habitat; // delete currently pointed object (here, string)
        habitat = new string (x.get_species()); // allocate space for new string, and copy
        return *this;
    }
    // Note that because the string member "habitat" that is being copied is not constant, we could
    // re-utlise the same string object. That is, we could replace the first two lines of this
    // special function with the single line:
    // *habitat = x.get_species();

    /* Similar to COPYING, MOVING also uses the value of an object to set the value of another object.
       But, unlike copying, the content is actually transferred from one object (the source) to the
       other (the destination): that is, the source loses that content, which is taken over by the
       destination. Moving only happens when the source of the value is an *unnamed* object. Such
       objects are temporary in nature, and thus haven't been given a name. Typical examples of
       unnamed objects are return values of functions or type-casts. Using the value of such a 
       temporary object to initialise another object or assign its value does not really require a
       copy: the object is never going to be used for anything else, and thus, its value can be
       moved into the destination object. These cases trigger the MOVE CONSTRUCTOR and MOVE ASSIGNMENT
       operator.
       The former is called when an object is initialised on *construction* using an unnamed
       temporary. Likewise, the latter is called on *assignment* of an object to the value of an
       unnamed temporary. */
    // Basic move constructor and move assignment operators for *shallow* copying:
    // Birds (Birds &&);
    // Birds& operator= (Birds&&);
    /* The move constructor and move assignment are members that take a parameter of type "rvalue
       reference to the class itself", specified by following the type with "&&". As a parameter, an
       'rvalue reference' matches arguments of temporaries of this type.
       In our example, we need a move constructor and a move assignment operator that each perform a
       *deep* copy... */
    Birds (Birds&& x) : species(x.get_species()), habitat(x.habitat) {
        x.habitat = nullptr;
        std :: cout << "\nCalled the move constructor\n";
        }

    // A move constructor for implicit type conversion
    Birds (Birds2&& b2) {
        b2.birds2ptr = nullptr;
        std :: cout << "\nCalled the move constructor for implicit type conversion\n";
    }

    // Move assignment operator
    Birds& operator= (Birds&& x) {
        std :: cout << "\nCalled the move assignment operator\n";
        delete habitat;
        habitat = x.habitat;
        x.habitat = nullptr;
        return *this;
    }

    // Operator overloading (perform "+" operation on type "Birds") - get a new "added together" habitat
    Birds operator+(const Birds& bird) {
        return Birds(bird.get_species(),get_habitat() + bird.get_habitat());
    }

    /* The concept of moving is most useful for objects that manage the storage they use, such as
       objects that allocate storage with the "new" and "delete" keywords. In such objects, copying
       and moving are really different operations:
       -copying from A to B means that new memory is allocated to B and then the entire content of A
        is copied to this new memory allocated for B
       -moving from A to B means that the memory already allocated to A is transferred to B without
        allocating any new storage. It simply involves copying the pointer.
       Compilers already optimise many cases that formally require a move-construction call.
       Most notably, when the value returned by a function is used to initialise an object. In
       these cases, the move constructor may actually never get called! This is COPY ELISION.
       We can force the move constructor to be called by combining the object initialisation
       with an implicit type conversion (see use of "Birds2" class below) */

    double get_wingspan() { return wingspan; }
    const string& get_species() const { return species; }
    const string& get_habitat() const { return *habitat; }

    // set or update parameters
    void update_params(double x, double y, double z) {
        height = x;
        weight = y;
        wingspan = z;
    }

    void set_species(const string& str) {
        species = str;
    }

    void set_habitat(const string& str) {
        habitat = new string(str);
    }

    /* Recall that dependent on circumstances, any of the six special member functions may be 
       implicitly defined for the class. We can select explicitly which of these members exist
       with their default definition or which are deleted by using the "default" and "delete"
       keywords, respectively.
       For example, if we did not want the implicitly defined version of the move constructor operator
       to be defined (we don't need to do this because we already explicitly declared a move
       constructor operator, and this special function cannot be overloaded), then we would do:  */
    // Birds (Birds &&) = delete;
    /* Similarly if, for example, we wanted the copy constructor to be explicitly defined as its
       default (recall the default copy constructor copies all members, see above) then we would do:*/
    // Birds (const Birds& x) = default;
    /* N.B. Somewhat confusingly, notice that the "default" keyword used to define, for instance, a
       constructor, does not explicitly define a member function equal to the *default constructor*
       (i.e. that which takes no parameters), but rather that equal to the constructor that would
       be *implicitly defined* (if not deleted). */
};

int main() {

    Birds ibis("Ibis");
    ibis.update_params(60.,940.,97.); // American white ibis
    ibis.set_habitat("Wetland");

    std :: cout << "Species of bird: " << ibis.get_species() << "\n";
    std :: cout << "Wingspan of bird: " << ibis.get_wingspan() << "\n";
    std :: cout << "Habitat of bird: " << ibis.get_habitat() << "\n";

    Birds crane;
    crane.set_species("Crane");
    crane.update_params(115.,4500.,210.); // common (Eurasian) crane

    std :: cout << "Species of bird: " << crane.get_species() << "\n";
    std :: cout << "Wingspan of bird: " << crane.get_wingspan() << "\n";

    // COPY CONSTRUCTOR
    Birds ibis2 = ibis;

    std :: cout << "Species of bird: " << ibis2.get_species() << "\n";
    std :: cout << "Habitat of bird: " << ibis2.get_habitat() << "\n";

    // COPY ASSIGNMENT
    Birds ibis3;
    ibis3 = ibis;

    // Note that the bird species is blank: we have defined the copy assignment operator so that it
    // copies the habitat to the new object, but not the species.
    std :: cout << "Species of bird: " << ibis3.get_species() << "\n";
    std :: cout << "Habitat of bird: " << ibis3.get_habitat() << "\n";

    // MOVE CONSTRUCTOR & MOVE ASSIGNMENT
    Birds cassowary = Birds("Cassowary","Rainforest"); // move-construction
    // Note that the move constructor is actually not called here; COPY ELISION OCCURS

    std :: cout << "Species of bird: " << cassowary.get_species() << "\n";
    std :: cout << "Habitat of bird: " << cassowary.get_habitat() << "\n";

    // Here, in the initialistion, we force the move constructor to be called because we combine the
    // initialisation with implicit type conversion (that is, the source object and destination are
    // *not* of the same type)
    Birds duck = Birds2();
    duck.update_params(50.,1150.,90.);
    duck.set_habitat("Pond");
    std :: cout << "Height of bird: " << duck.height << "\n";
    std :: cout << "Habitat of bird: " << duck.get_habitat() << "\n";

    // call the move assignment operator
    // this gives a "hybrid habitat" for the bird!
    cassowary = cassowary + ibis; // use of overloaded "+" operator for type "Birds"
            // this invokes the move assignment operator

    std :: cout << "Species of bird: " << cassowary.get_species() << "\n";
    std :: cout << "Hybrid habitat of bird: " << cassowary.get_habitat() << "\n";

    return 0;
}
