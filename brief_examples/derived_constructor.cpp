/*
C++ code to demonstrate calling a non-default base class constructor from derived class constructor
*/

#include <iostream>
#include <string>

using namespace std;

// base class
class Fish {

    protected:

    string river;

    public:

    Fish();
    Fish(string);
    ~Fish();
    Fish(const Fish&);
    string get_river();
};

Fish::Fish() {
    cout << "  in Fish default constructor" << endl;
}

Fish::Fish(string river) {
    cout << "  in Fish non-default constructor" << endl;
    this->river=river;
}

Fish::~Fish() {
    cout << "  in Fish destructor" << endl;
}

Fish::Fish(const Fish& fish) {
    cout << "  in Fish copy constructor" << endl;
    this->river = fish.river;
}

string Fish::get_river() {
    if (!this->river.empty()) {
        return this->river;
    } else {
        string alttext ("Unknown river");
        return alttext;
    }
}

// derived class
class Gar : public Fish {

    protected:

    string subspecies;

    public:

    Gar(string);
    Gar(string,string);
    ~Gar();
    Gar(const Gar&);
    string get_subspecies();
};

// this constructor calls the default constructor of the base class, i.e. calls Fish::Fish()
Gar::Gar(string subspecies) {
    cout << "  in Gar constructor 1" << endl;
    this->subspecies=subspecies;
}

// this constructor calls the explicit constructor of the base class, i.e. calls Fish::Fish(string)
Gar::Gar(string subspecies, string river) : Fish(river) {
    cout << "  in Gar constructor 2" << endl;
    this->subspecies=subspecies;
}

Gar::~Gar() {
    cout << "  in Gar destructor" << endl;
}

// this copy constructor calls the copy constructor of the base class, i.e. calls Fish::Fish(const Fish&)
Gar::Gar(const Gar &gar) : Fish(gar) {
    cout << "  in Gar copy constructor" << endl;
    this->subspecies = gar.subspecies;
}

string Gar::get_subspecies() {
    return this->subspecies;
}


int main() {

    /* when instantiating an object of a derived class, a constructor of the base class must always be called. But which one?
       observe which constructors are visited in the following */

    cout << "\nHere is the first gar..." << endl;
    Gar gar1("Alligator");
    cout << gar1.get_subspecies() << endl;
    cout << gar1.get_river() << endl;

    cout << "\nHere is a second gar..." << endl;
    Gar gar2("Longnose","Mississippi");
    cout << gar2.get_subspecies() << endl;
    cout << gar2.get_river() << endl;

    cout << "\nHere is a copy of the second gar..." << endl;
    Gar gar3 = gar2;
    cout << gar3.get_subspecies() << endl;
    cout << gar3.get_river() << endl;

    cout << "\nfinished looking at fish now..." << endl;

    return 0;
}
