/* illustration of aspects of a class having pointer members */

#include <iostream>

using namespace std;

class B; // note forward declaration

class C {
    public:
    int y;
    C() { y=8; }
    ~C() {}
};

class A {
    public:
    B *b1, *b2, *b3, *b4; // you can declare a member to be a pointer of an incomplete type
    C c; // a non-member pointer must be of a complete type. This doesn't work if you try and call a constructor with args
    A();
    ~A();
    A(const A &a); // the default copy constructor fails if the classes have pointer members, so we need an explicit copy constructor
    A & operator=(const A &a); // we also need an explicit assignment operator in classes with pointer members
};

class B {
    public:
    int x;
    B(int x_) : x(x_) {}
    ~B() {}
    B(const B &b) { cout << "called copy constructor for class B" << endl; }
    B & operator=(const B &b) { cout << "called assignment operator for class B" << endl; }
};

A::A() {
    B b_obj(7); // to create an object of a type, the type must be complete at this stage
    cout << "assigning b1..." << endl;
    b1 = &b_obj; // b1 does not hold its memory because b_obj goes out of scope at the end of A::A()
    cout << "assigning b2 using new..." << endl;
    b2 = new B(7); // b2 holds its memory because we have allocated it
    cout << "assigning b3 from b1..." << endl;
    b3 = b1; // b3 does not hold its memory because it is merely made to point to the same place as b1 (note no copying or assignment is done here)
    this->b4 = &b_obj; // this is just different syntax to assigning b1 as above
}

A::~A() {
    if (b2) delete b2;
}

int main() {
    A a_obj;
    cout << "b1.x: " << a_obj.b1->x << endl;
    cout << "b1.x: " << a_obj.b1->x << endl; // value of b1.x gets scrambled when accessed for the second time
    cout << "b2.x: " << a_obj.b2->x << endl;
    cout << "b2.x: " << a_obj.b2->x << endl;
    cout << "b3.x: " << a_obj.b3->x << endl; // likewise b3.x is scrambled here
    cout << "b4.x: " << a_obj.b4->x << endl; // likewise b4.x is scrambled here
    cout << "c.y: " << a_obj.c.y << endl;
}
