/* C++ example demonstrating the use of the keyword THIS
The THIS keyword represents a pointer to the object whose member function is being executed.
It is used within a class's remember function to refer to the object itself.
One of its uses can be to check if a parameter passed to a member function is the object
itself (see function isitme() in the program below) */

#include <iostream>
using namespace std;

class Dummy {
  public:
    bool isitme (Dummy& param);
    const int x = 3;
};

// Function isitme() takes an object instance of class Dummy as its argument
bool Dummy::isitme (Dummy& param)
{
  int y;

  std :: cout << "Calling isitme()\n";
  y = this->x;
  std :: cout << "Param of object whose member func is being executed: " << y << "\n"; 
  if (&param == this) return true;
  else return false;
}

int main () {

  Dummy a;
  Dummy* b = &a; // assign pointer to address of object instance
  if ( b->isitme(a) ) // use this pointer to call isitme(), passing that object instance as the function
    cout << "yes, &a is b\n";

  /* Do the same again, but this time call isitme() member from an object that is NOT the same as
     the object instance passed as an argument to the function */
  Dummy c;
  Dummy* d = &c;
  if ( not d->isitme(a) )
    cout << "no, &a is not d\n";

  return 0;
}
