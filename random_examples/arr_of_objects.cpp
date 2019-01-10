/* C++ code demonstrating declaration and instantiation of an array of class objects */

#include <iostream>
using namespace std;

// the first class that we are going to create an array of instances of - constructor takes no args
class MyClass1 {

    public:

    MyClass1() {}; // default constructor
};

// the second class that we are going to create an array of instances of - constructor takes a single arg
class MyClass2 {

    public:

    int param1;
    MyClass2() {}; // default constructor
    MyClass2(int arg) { param1 = arg; }; // overloading: have parameterised constructor too
    void assign_param1(int arg) { param1 = arg; };
};

int main () {

    int nobjs = 5;

    MyClass1 *objarr1[nobjs]; // pointer to an array of objects of type MyClass1, with nobjs elems
    MyClass2 *objarr2[nobjs];

    for (int i=0;i<nobjs;i++) {
        objarr1[i] = new MyClass1();
        // new ALWAYS calls the DEFAULT constructor of an object, we CANNOT pass an argument
        // into the class...
        objarr2[i] = new MyClass2();
        // ...we can work around this by having a separate function assign variables
        objarr2[i]->assign_param1(i);
        // note that is objarr2 had been declared with "MyClass2 objarr2[nobjs]", i.e. not as
        // a pointer, then we would not have to use new. The declaration would call the
        // default constructor, so we would again have to use a separate member function to
        // assign variables.

        // print parameter of objarr2
        cout << "param: " << i << " of objarr2 is: " << objarr2[i]->param1 << "\n";
    }

    // cleanup memory
    for (int i=0;i<nobjs;i++) {
        delete objarr1[i];
        delete objarr2[i];
    }

    /* Note that another way of getting around this problem is to use a std::vector container,
       of type <MyClass>, and instantiate elements with a call to emplace_back, the argument
       to which is a call to the parameterised constructor of the class. The default 
       constructor of the class is never invoked. */

    return 1;
}
