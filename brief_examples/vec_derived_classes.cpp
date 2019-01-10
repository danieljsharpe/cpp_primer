/*
The std::vector container can be used to hold objects that are different derived classes of the same base class.

Putting an object of derived type into a vector of base type will compile, but the result is "object slicing": only the
base subobject will be stored in the vector, losing everything that the derived class added.

What is needed is a vector of *pointers* to the base class.

Having an array/vector of base classes is one of the most useful properties of *polymorphism*. The concept of polymorphism is that
a pointer of a base class can point to any class that derives from it.

Consider the example below... (expected output: 6 7 5 7 6).

*/

#include <iostream>
#include <vector>
using namespace std;

class a
{
protected:
    int test;
public:
    virtual void SetTest(int arg) {test = arg;}
    int GetTest() {return test;}
};

class b : public a
{
public:
    void SetTest(int arg) {test = arg+1;}
};

class c : public a
{
public:
    void SetTest(int arg) {test = arg+2;}
};

int main()
{
    vector<a *> derivedClassHolder; // note use of *pointer* to base class
    derivedClassHolder.push_back(new b);
    derivedClassHolder.push_back(new c);
    derivedClassHolder.push_back(new a);
    derivedClassHolder.push_back(new c);
    derivedClassHolder.push_back(new b);

    for(int i = 0; i < (int)derivedClassHolder.size() ; i++)
    {
        derivedClassHolder[i]->SetTest(5);
    }

    for(int i = 0; i < (int) derivedClassHolder.size() ; i++)
    {
        cout << derivedClassHolder[i]->GetTest() << "  ";
    }
    cout << "\n";
    return 0;
}

/*
Note that the use of:
vector<Base *>
is not ideal - there is some ambiguity as to who owns the memory pointed to (i.e. is it the vector or is it something else that
created the object?). This leads to the potential for memory leaks and/or dangling pointers.
A more robust option is to use so-called *smart pointers*, for example with:
std::vector<std::unique_ptr<Base>>
or with
boost::ptr_vector<Base>
*/
