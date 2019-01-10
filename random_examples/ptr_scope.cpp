/* C++ example code illustrating the scope of a pointer variable */

/*
It is necessary to distinguish between the pointer (a variable that holds a memory location)
and the object to which the pointer points (the object at the memory address held by the pointer).

A pointer is a variable that contains a memory location.
A pointer can point to objects on the stack (local storage / static allocation) or on the
heap (dynamic storage / dynamic allocation i.e. through new or malloc), and like all
variables, can itself, like its value (the memory location) exist on either the heap or stack.
N.B. generally speaking you can only access dynamically allocated memory using a pointer.
If you use NEW to allocate the object, it will be on the heap.
If the pointer is declared in the body of a function, then it will be a local variable and
live in local storage (i.e. on the stack).
If the pointer is a global variable (or static class member), it will live somewhere in your
application's data section.

If a pointer goes out of scope or its parent object is deleted, the object that the pointer
references still exisits in memory. Therefore any code that allocates an object with NEW is
said to 'own' the object and we should DELETE the object when it is no longer needed.
*/

class MyClass {

    public:

    MyClass() {};
    ~MyClass() { delete [] p2; }; // manually free memory associated with p2
    void func1(), func2(), func3(), func4(int n);
    int *p2; // p2 is a member variable. It will go out of scope when the parent object goes
             // out of scope or is deleted from the heap.
} class1;

void MyClass::func1()
{
  int x = 1;
  int *p = &x; // pointer on stack
}
// p goes out of scope, so does the memory it points to

void MyClass::func2()
{
  int *p = new int; // pointer on heap
}
// p goes out of scope, the memory it points to DOES NOT

void MyClass::func3()
{
  int x = 1;
  int **pp = new int*;
  *pp = &x;
}
// pp goes out of scope, the pointer it points to does not, the memory it points to does

void MyClass::func4(int n)
{
  // int *p2[n]; // doesn't really do anything - the pointer is doomed to remain incomplete
  p2 = new int[n]; // this is the correct way to declare the pointer
}
// p2 still within scope of class

int main () {

    class1.func1();
    class1.func2();
    class1.func3();
    class1.func4(3);

    return 1;
}
