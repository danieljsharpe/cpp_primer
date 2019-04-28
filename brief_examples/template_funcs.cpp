/*
C++ example of use of template functions and demonstrate ADL (argument-dependent lookup) for user-defined functions
*/

#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

int deal_with_int (int x) { x++; }

double deal_with_dbl (double y); // a forward declaration of function deal_with_dbl, declared
                                 // fully later

bool deal_with_bool (bool b) {}

// do_something() function is overloaded depending on arguments
// because it is a user-defined function, ADL is performed
int do_something (int x) { cout << "in int version of do_something()" << endl; }
double do_something (double y) { cout << "in double version of do_something()" << endl; }
bool do_something (bool z) { cout << "in bool version of do_something()" << endl; }

/* with a template function, we can pass  */
template <class T>
T myfunc(T arg) {

    T aval, retval;
    if (typeid(T) == typeid(int)) {
        cout << "myfunc() got given an int!" << endl;
        // for user-declared functions, ADL is performed, so it is fine to have overloaded
        // do_something() function
        retval = do_something(arg);
        aval = deal_with_int(arg); }
    else if (typeid(T) == typeid(double)) {
        cout << "myfunc() got given a double!" << endl;
        retval = do_something(arg);
        aval = deal_with_dbl(arg); }
    else if (typeid(T) == typeid(bool)) {
        cout << "myfunc() got given a bool!" << endl;
        retval = do_something(arg);
        aval = deal_with_bool(arg); }
    return retval;
}
/* we couldn't do with a built-in function what we have done with do_something(), because of the lack of ADL
   for built-in functions, without some extra lines! */

double deal_with_dbl (double y) { y += 2.; }

int main () {

    int x = 1;
    double y = 1.5;
    bool quack = true;

    int z1 = myfunc(x);
    double z2 = myfunc(y);
    bool z3 = myfunc(quack);

    return 0;
}
