/*
C++ demonstration of nested classes

A nested class is a class which is declared in another enclosing class. A nested class is a member and as such has the same
access rights as any other member. The members of an enclosing class have no special access to members of a nested class;
the usual access rules shall be obeyed. 
*/

#include<iostream> 
using namespace std; 
  
class Enclosing {       
    private:

    int x = 1; 
     
    class Nested { 
        int y = 2;
        void NestedFun(Enclosing *e) {
        cout << e->x;  // works fine: nested class can access  
                       // private members of Enclosing class
        }
        public:
        int z = 3;
    };
    void enclosing_func(Nested *n) {
        // cout << n->y; // compiler error: y is private in Nested
        cout << n->z; // okay: x is public in nested
    }
};
  
int main() {

    Enclosing* enclosing1;


    return 0;
} 

