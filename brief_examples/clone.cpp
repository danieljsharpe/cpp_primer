/*
One can have a derived containing class that has total ownership of the objects that it creates.

For instance, to have a vector of derived classes, the containing class makes its own copies of the objects in the vector
(then there is no chance of the objects going out of scope).

The base class has a virtual clone() function, that is implemented in the derived class(es). The clone() function returns a
copy of the object on the heap pointed to by a Base* pointer. The containing class uses this to make its own copies of
everything it contains.
*/

#include <iostream>
#include <vector>
using namespace std;

/* abstract base class */
class Base
{
    public:

    Base() {};
    virtual ~Base() = default; // note virtual destructor

    virtual void doSomething() const = 0; // pure virtual function
    virtual void push_back(const Base&) {};
    virtual void set(int,const Base&) {};
    virtual void print_vec() {};

    virtual Base* clone() const = 0; // clone(). Overridden in derived class
};


class Derived : public Base
{
    vector<Base*> vec;

    public:

    // cloning
    virtual Derived* clone() const {
        return new Derived(*this); } // note that this calls the copy constructor!

    void push_back(const Base& obj)
        { vec.push_back(obj.clone()); }
    void set(int i, const Base& obj) {
        delete vec[i];                // note: make sure destructor is virtual
        vec[i] = obj.clone(); }
    //const obj& get(int i) const
    //    { return *vec[i]; }

    virtual void doSomething() const {
        cout << "Overridden virtual function doing what you tell me to!\n";
    }

    void print_vec() {
        cout << "Printing the vector for this instance of derived class\n";
        for (auto x: vec) {
            std::cout << " " << x << "  " << &x << "\n"; }
        std::cout << "\n";
    }
};


int main () {

    // declaration + cloning
    // Base base1; // cannot do this because Base is an abstract type (has pure virtual function(s))
    Base* derived1;
    derived1 = new Derived;
    derived1->doSomething();
    Base* derived2 = derived1->clone();
    derived2->doSomething();

    // alternative declaration + coding
    Derived derived3;
    Derived* derived4 = derived3.clone();

    cout << &derived2 << "\n";
    // playing with the vector of derived classes
    derived2->push_back(*derived1);
    derived2->push_back(derived3);
    derived2->push_back(*derived4);
    derived2->set(2,*derived4);
    derived2->print_vec();

    cout << "Compare with:\n" << &derived1 << " " << &derived3 << " " << &derived4 << "\n";

    return 0;
}

/*
In the above we do not make a copy of the object, we make a brand new instance of it, except based off of some premade stock
object. This makes all of those objects made off of that copy be owned by the original, so at the end of the program, when the
original object is destroyed, so are all the copies of it, ensuring that there is no memory leak. You are able to treat all the
copies just as if they were different objects changing their original values etc.

The clone() method in the base class (interface) delegates the object construction to the implementation itself!!
Notice that the return type of the clone() method differs between the base class (interface) and the derived class (implementation).
This is allowed because C++ allows overriding a virtual method with one that has a different return type, provided this
return type is a pointer (resp. reference) to a class convertible to the one pointed to (resp. referenced by) the return type
of the base class. This property is called COVARIANCE.
*/
