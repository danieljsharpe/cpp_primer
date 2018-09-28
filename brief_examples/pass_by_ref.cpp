/* C++ example of passing arguments by reference to a function */

#include <iostream>
using namespace std;

// Array parameter decays to pointer
void update_value1 (double * x) {
    x[1] = -1.;
}

// Create a reference-to-array
void update_value2 (double (&x)[5]) {
    x[1] = -2.;
}

// 'normal' function syntax - function parameter is copied
void update_int1 (int i) {
    i += 1; // only updated locally
}

// pass integer by reference - the *reference* of the argument is copied into the formal function parameter
// i.e. the arguments to the function point to the (true) variables
void update_int2 (int &i) {
    // inside the function, the reference is used to access the *actual* argument used in the call
    i += 1; 
}

int main () {

    int i;
    double foo [5] = {};
    for (i=0;i<5;i++) {
        foo[i] = double(i);
    }

    std::cout << "2nd elem of array: " << foo[1] << "\n";
    update_value1(foo);
    std::cout << "2nd elem of array IS updated by call to first function: " << \
                 foo[1] << "\n";
    std::cout << "2nd elem of array IS NOT updated by call to second function: " << \
                 foo[1] << "\n";

    i = 0;
    std::cout << "Integer: " << i << "\n";
    update_int1(i);
    std::cout << "Integer IS NOT updated by call to first function: " <<  i << "\n";
    update_int2(i);
    std::cout << "Integer IS updated by call to second function: " << i << "\n";

    return 1;
}
