/*
A second example of the PROTOTYPE creational pattern.

Here, we re-write the script in prototype_before.cpp so that it DOES implement the PROTOTYPE design pattern. A clone() method
has been added to the Stooge hierarchy. Each derived class implements that method by returning an instance of itself. A
FACTORY class has been introduced that maintains a suite of "breeder" objects (aka proto-types) and knows how to delegate
to the correct prototype.
*/

#include <iostream>
#include <vector>
using namespace std;

class Stooge {
public:
   virtual Stooge* clone() = 0;
   virtual void slap_stick() = 0;
};

class Factory {
public:
   static Stooge* make_stooge( int choice );
private:
   static Stooge* s_prototypes[4];
};

class Larry : public Stooge {
public:
   Stooge*   clone() { return new Larry; }
   void slap_stick() {
      cout << "Larry: poke eyes\n"; }
};
class Moe : public Stooge {
public:
   Stooge*   clone() { return new Moe; }
   void slap_stick() {
      cout << "Moe: slap head\n"; }
};
class Curly : public Stooge {
public:
   Stooge*   clone() { return new Curly; }
   void slap_stick() {
      cout << "Curly: suffer abuse\n"; }
};

Stooge* Factory::s_prototypes[] = {
   0, new Larry, new Moe, new Curly
};
Stooge* Factory::make_stooge( int choice ) {
   return s_prototypes[choice]->clone();
}


int main() {
   vector<Stooge *> roles;
   int choice;

   while (true) {
      cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
      cin >> choice;
      if (choice == 0)
         break;
      roles.push_back(
         Factory::make_stooge( choice ) );
   }

   for (int i=0; i < roles.size(); ++i)
      roles[i]->slap_stick();
   for (int i=0; i < roles.size(); ++i)
      delete roles[i];
}
