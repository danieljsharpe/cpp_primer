/*
Demonstration of argument-dependent lookup (ADL) for template functions
*/

#include <iostream>
using namespace std;

/* without this forward declaration of h(), we get:
   "error: there are no arguments to ‘h’ that depend on a template parameter, so a declaration of ‘h’ must be available" */
void h ();

template <typename T>
void f(T arg) {

    cout << "in f" << endl;

    T g(); // fine without forward declaration
    h(); // not fine without forward declaration

    int x = g();
    cout << "x is: " << x << endl;
}

int g () { cout << "in int g()" << endl; return 1; }

void h () {}

int main () {

    int x=2;
    f(x);

    return 0;
}
