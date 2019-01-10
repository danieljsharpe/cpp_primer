/*
C++ creational design patterns: FACTORY METHOD
Creates an instance of several derived classes.

A factory method allows a class to defer instantiation to subclasses, by design of a
VIRTUAL CONSTRUCTOR. Individual subclasses will be allowed to define their own domain
objects and provide for their instantiation.

A superclass specifies all standard and generic behaviour (using pure virtual "placeholders"
for creation steps) and then delegates the creation dtails to subclasses. In this way,
a factory method is to creating objects what a template method is to implementing an
algorithm.

People often use factory method as the standard way to create objects, but it isn't
necessary to do so if a) the class that is instantiated never changes or (b) instantiation
takes place in an operation that subclasses can easily override (e.g. initialisation
operation).

A concise definition of a factory method is: a STATIC method of a class that returns an
object of that class' type. But unlike a constructor, the actual object that it returns
might be an instance of a subclass.

The factory method defines an interface for creating objects, but lets subclasses decide
which classes to instantiate.

Considerations
1. If you have an inheritance hierarchy that exercises polymorphism, consider adding a
polymorphic creation capability by defining a STATIC factory method in the base class.
2. Design the arguments to the factory method to reflect what const characteristics are
necessary and sufficient to identify the correct derived class to instantiate.
3. Consider designing an internal "object pool" that will allow objects to be reused
instead of created from scratch.
4. Consider making all constructors PRIVATE or PROTECTED.

Rules of thumb
1. Abstract factory classes are often implemented with factory methods, but they can also
be implemented using prototype.
2. Factory methods are usually called within template methods
3. factory method: creation through inheritance. Vs
   prototype: creation through delegation.
4. Prototype doesn't require subclassing, but it does require an initialise operation. The
   converse is true for facotry methods.
5. the advantage of a factory method is that it can return the same instance multiple
   times, or can return a subclass rather than an object of that exact type
6. factory methods essentially provide an alternative to the NEW operator. The NEW operator
   always creates an object, and fails to encapsulate object creation. A factory method
   enforces that encapsulation, and allows an object to be requested without inextricable
   coupling to the act of creation.
*/


/*
Example: we have a framework (Toy & ToyMaker classes) for creating toys. The framework
knows when a new toy needs to be made, but not what kind of toy.
The ToyMaker framework class declares the placeholder (i.e. virtual function) "CreateToy()",
and the client is expected to specify the type of toy (see declaration of
ToyMaker::CreateToy() in MyToyMaker derived class). Then, when the client asks for
ToyMaker::CreateToy(), the framework will subsequently call the client's
MyToyMaker::CreateToy().
*/

#include <iostream>
#include <string.h>
using namespace std;

// abstract base class declared by framework
class Toy {
    public:
        Toy(const char *fn) {
            strcpy(toy_type,fn);
        }
    const char *get_toy_type() {
            return toy_type;
        }
    virtual void On() = 0;
    virtual void Off() = 0;
    private:
        char toy_type[5];
};

// concrete derived class defined by client
class MyToy: public Toy {
    public:
        MyToy(const char *fn): Toy(fn) {}
        void On() { cout << "Called On()\n"; }
        void Off() { cout << "Called Off()\n"; }
};

// framework declaration
class ToyMaker {
    public:
        ToyMaker(): _index(0) {}
        // the client will call this "entry point" of the framework
        void newtoy(const char *toy_type) {
            _toys[_index] = CreateToy(toy_type);
            _toys[_index++]->On();
        }
        void report_toys();
        // framework declares a "hole" for the client to customise
        virtual Toy *CreateToy(const char*) = 0;
    private:
        int _index;
        // framework uses Toy's base class
        Toy *_toys[10];  
};

void ToyMaker::report_toys() {
    cout << "_index is: " << _index << "\n";
    for (int i=0;i<_index;i++) {
        cout << " " << _toys[i]->get_toy_type() << "\n";
    }
}

// customisation of framework defined by client
class MyToyMaker: public ToyMaker {
    public:
        MyToyMaker() {}
        // client defines framework's "hole"
        Toy *CreateToy(const char *fn) {
            return new MyToy(fn);
        }
};

int main() {

    MyToyMaker mytoymaker;

    mytoymaker.newtoy("duck");
    mytoymaker.newtoy("boat");
    mytoymaker.newtoy("squid");

    mytoymaker.report_toys();

    return 0;
}
