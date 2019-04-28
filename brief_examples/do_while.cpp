/*
Short C++ script demonstrating that a "do while" loop is entered if the condition is not initially met
*/

#include <iostream>

using namespace std;

int main() {

    int i=0;
    bool mybool = false;

    do {
        cout << "iter. no. " << i << " mybool: " << mybool << endl;
        i++;
    } while(mybool);
    cout << "exited loop after " << i << " iterations " << endl;

    return 0;
}
