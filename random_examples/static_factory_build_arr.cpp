/*
Example C++ code illustrating a static factory method of a class that builds an array containing
elements of that class.
This method uses NEW so invokes the default constructor.
This method does not require the default constructor to be public.
*/

#include <iostream>
using namespace std;

class Car
{
private:
  Car(){};
  int _no;
public:
  Car(int no)
  {
    _no=no;
  }
  int getNo()
  {
    return _no;
  }
  void setNo(int no)
  {
    _no=no;
  }

  static Car *createcararray(int n);
};

// factory method for building array containing elems of type Car class
// note that we don't use the static keyword again here
Car *Car::createcararray(int n) {
    return new Car[n]; // but recall always calls default constructor
}

int main () {

    int n_elems = 5;
    Car *car_arr = Car::createcararray(n_elems);

    for (int i=0;i<n_elems;i++) {
        car_arr[i].setNo(i);
        cout << car_arr[i].getNo() << "\n"; // note car_arr is not pointer type
    }

    // alternative:
    // if we wanted to use the parameterised constructor, we could create an array of pointers
    Car** mycars = new Car*[n_elems];
    for (int i=0;i<n_elems;i++) {
        mycars[i] = new Car(i);
        cout << mycars[i]->getNo() << "\n";
    }
    // cleanup memory
    for (int i=0;i<n_elems;i++) {
        delete mycars[i];
    }
    delete [] mycars;

    return 0;
}
