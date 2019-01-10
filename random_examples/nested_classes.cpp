/*
C++ demonstration of nested classes

A nested class is a class which is declared in another enclosing class. A nested class is a member and as such has the same
access rights as any other member. The members of an enclosing class have no special access to members of a nested class;
the usual access rules shall be obeyed. 
*/

#include<iostream> 
using namespace std; 
  
class Enclosing {       

    int x = 1;
    class Nested2 {};

    public:
     
    class Nested { 

        int y = 2;
        Nested2* nested2; // allowed because Nested can access private members of enclosing (such as Nested2)

        public:

        void nested_func(Enclosing *e) {
            Nested2 *nested2inst = new Nested2;
            delete nested2inst;
            cout << e->x << endl;  // works fine: nested class can access  
                                   // private members of Enclosing class
        }
        static int z;
    };

    void enclosing_func(Nested *n) {
        // cout << n->y << endl; // compiler error: y is private in Nested
        cout << n->z << endl; // okay: x is public in nested
    }
};

typedef Enclosing::Nested Encnest;
int Encnest::z = 3;
  
int main() {

    Enclosing *enclosing1, *enclosing2;
    Encnest* encnest1;

    encnest1->nested_func(enclosing2);
    enclosing1->enclosing_func(encnest1);

    return 0;
}
