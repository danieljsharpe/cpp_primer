/*
C++ strucutral pattern: DECORATOR
Add responsibilities to objects dynamically.

A DECORATOR is used to attach additional responsibilities to an object dynamically.
Decorators provide a flexible alternative to subclassing for extending functionality.
Decorators achieve client-specified embellishment of a core object by recursively
wrapping it.

Decorators are used when you want to add behaviour to individual objects at run-time.
Inheritance is not feasible because it is static and applies to an entire class.

Rather than having a complex inheritance hierarchy, we can have a single decorator
pattern that gives the client the ability to specify whatever combination of features
is required. The decorator will then chain features together to produce a custom object.
The solution to the problem outlined above is to encapsulate the original object
inside an abstract wrapper interface. Both the decorator objects and the core object
inherit from this abstract interface. The interface uses recursive composition to
allow an unlimited number of decorator 'layers' to be added to each core object.

Note that this pattern allows responsibilites to be added to an object, not methods
to an object's interface. The interface presented to the client must remain constant
as successive layers are specified.

Also note that the core object's identity has now been "hidden" inside of a decorator
object. Trying to access the core object directly is now a problem.

Structure:
-optional methods always delegate to the wrapper (decorator) base class, and that class
always delegates to the contained 'wrappee' object.

          Core functionality
         /
Interface                  Optional functionality 1
         \                /
          Optional wrapper-Optional functionality 2
                          \
                           Optional functionality 3

Here, all the above classes (incl the interface) have a do_this() method. The optional
wrapper class acts on a wrappee.


The decorator attaches additional respnsibilities to an object dynamically.


Check list:
1. ensure that the context is: a single core (ie non-optional) component, several
optional embellishments or wrappers, and an interface that is common to all.
2. create a "lowest common denominator" interface that makes all classes interchange-
able.
3. Create a second level base class (decorator) to support the optional wrapper classes.
4. the core class and decorator class inherit from the LCD interface.
5. the decorator class declares a composiiton relationship to the LCD interface,
and this data member is initialised in its constructor.
6. the decorator class delegates to the LCD object.
7. define a decorator derived class for each optional embellishment
8. decorator derived classes implement their wrapper functionality and delegate to
the decorator base class.
9. The client configures the type and ordering of core and decorator objects.

Rules of thumb:
1. ADAPTER provides a different interface to its subject. PROXY provides the same
interface. DECORATOR provides an enhanced interface.
2. ADAPTER changes an object's interface, DECORATOR enhances an object's responsibilities.
Decorator is thus more transparent to the client. As a consequence, decorator
supports recursive composiiton, which isn't possible with pure adapters.
3. COMPOSITE and DECORATOR have similar structure diagrams, reflecting the fact that
they both rely on recursive composiiton to organise an open-ended no. of objects.
4. a DECORATOR can be viewed as a degenerate COMPOSITE with only one component.
However, a decorator adds additional responsibilities - it isn't intended for object
aggregation.
5. DECORATOR is designed to let you add responsibilities to objects without subclassing.
COMPOSITE's focus is not on embellishment but on representation. These intents are
distinct but complementary. Consequently, composite and decorator are often used in
concert.
6. COMPOSITE could use chain of responsibility to let components access global properties
through their parent. It could use DECORATOR to override these properties on parts of the
composition.
7. DECORATOR and PROXY have different purposes but similar structures. Both describe
how to provide a level of indirection to another object, and the implementations keep a
reference to the object to which they forward requests.


We can summarise the DECORATOR design pattern thusly:
1. Create a "lowest common denominator" (interface) that makes classes interchangeable
2. Create a second level base class for optional functionality
3. core & decorator classes declare an "is a" relationship
4. Decorator class "has a" instance of the LCD
5. Decorator class delegates to the "has a" object
6. Create a decorator derived class for each optional embellishment
7. Decorator derived classes delegate to base class AND add extra stuff
8. Client has the responsibility to compose desired configurations.
*/

#include <iostream>
using namespace std;

// the LCD (/interface)
class Gun {
    public:
        virtual void aim_and_fire() = 0;
};

// core class
class BaseGun: public Gun { // "is a" relationship
    int _rounds;
    public:
        BaseGun(int rounds) {
            _rounds = rounds;
        }
        // virtual
        void aim_and_fire() {
            cout << "Firing BaseGun. # of rounds: " << _rounds << "\n";
        }
};

// 2nd level base class (Decorator)
class WeaponAccessories: public Gun { // "is a" relationship
    Gun *gun; // "has a" relationship
    public:
        WeaponAccessories(Gun *g) {
            gun = g;
        }
        // virtual
        void aim_and_fire() {
            gun->aim_and_fire(); // delegation
        }
};

class Silencer: public WeaponAccessories {
    public:
        // optional embellishment
        Silencer(Gun *g): WeaponAccessories(g) {}

        // virtual
        void aim_and_fire() {
            // delegate to base class and add extra stuff
            WeaponAccessories::aim_and_fire();
            cout << " Silencer equipped " << "\n";
        }
};

class Scope: public WeaponAccessories {
    public:
        // optional embellishment
        Scope(Gun *g): WeaponAccessories(g) {}

        // virtual
        void aim_and_fire() {
            // delegate to base class and add extra stuff
            WeaponAccessories::aim_and_fire();
            cout << " Scope equipped " << "\n";
        }
};

int main () {

    // client has the responsibility to compose desired configurations
    Gun *a_gun = new Silencer(new Scope(new BaseGun(30)));
    a_gun->aim_and_fire();

    return 0;
}
