/* Demonstration of friend functions and classes, and of class inheritance, in C++ */

#include <iostream>

using namespace std;

/* class Person is a friend of class Animal. This allows class Animal's member function to access
   private and protected members of Person, as occurs in the function transform().
   Note that the empty declaration of the class Person is required, since class Animal uses Person
   (as a param in member transform()), and Person uses Animal (declaring it as a friend). */
class Person;

class Animal {

    protected:

    double height, weight;

    void set_values (double x, double y) { height=x, weight=y; }

    public:

    Animal() { std :: cout << "Called the default constructor for Animal class\n";} // default constructor
    Animal (double x, double y) : height(x), weight(y) { // parameterised constructor w initialisation list
        std :: cout << "Called the parameterised constructor for Animal class\n";}

    double ratio() {return height/weight;}

    friend Animal clone (const Animal&); // declare function clone is a friend of class Animal

    void transform (Person person);

    double get_height() { return height; }
};

/* The function clone() is a friend of class Animal. Therefore the function clone() is able to
   access the private members height & weight of different objects of type Animal.
   Note that neither in the declaration of clone() nor in its later use in main(), function clone()
   is considered a member of class Animal - it isn't! It simply has access to the private and
   protected members of the class without being a member.
   A typical use case of friend functions, such as is given below, are operations that are conducted
   between two different classes (or objects thereof) (accessing private or protected members) */
Animal clone (const Animal& param) {

    Animal animal;
    animal.height = param.height;
    animal.weight = param.weight;
    return animal;
}

class Person {

    /* similar to friend functions, a friend class is a class whose members have access to the
       private or protected members of another class.
       Note that friendships are never corresponded unless specified. So here, Animal is considered
       a friend by class Person, but Person is not considered a friend by Animal. Therefore, the
       member functions of Animal can access the protected and private members of Person, but not
       vice versa. Of course, Person could also be declared friend of Animal, if needed, granting
       such access.
       Another property of friendships is that they are not transitive: the friend of a friend is
       not considered a friend unless explicitly specified. */
    friend class Animal;

    protected:

    int age;
    double height_person, weight_person;

    public:

    Person (int a, double x, double y) : age(a), height_person(x), weight_person(y) {}
};

/* Called from an object of class Animal and passed a parameter that is the corresponding object of
   class Person:
   Assign the animal the height & weight of that person.
   Because Person is a friend of class Animal, this function (a member of class Animal) can access
   the protected and private members of class Person. */
void Animal::transform (Person person) {

    height = person.height_person;
    weight = person.weight_person;
}

/* In C++ we can have inheritance between classes. The derived class inherits the members of the
   base class, on top of which it can add its own members. This effectively allows us to create
   new classes which retain characteristics of the base class, and so we can many derived classes
   that have certain common properties (variables and functions), which are members of the base
   class. Other features are specific to the individual base classes.
   The inheritance relationship of two classes is declared in the derived class, with the following
   syntax (where Bird is a derived class of base class Animal) (note that the access specifier
   can be any one of public, protected & private, and limits the most accessible level for the
   members inherited from the base class: the members with a more accessible level are inherited
   with this level instead, while the members with an equal or more restrictive access level keep
   their restrictive level in the derived class): */
class Bird: public Animal {

    public:

    double wingspan;

    Bird (double x) : wingspan(x) {}

    double get_wingspan() {return wingspan;}

    /* Bird is a derived class of base class Animal, so we can call
       Animal's protected function set_values(), and set the variables height & weight as
       members of Bird (even though these are declared in Animal (also as protected - we could
       not do this if they were declared private. Remember that using the public access specifier
       in the derived class declaration, the protected members of Animal keep their protected
       status with respect to Bird - i.e. they are not public with respect to Bird)
       (N.B. because set_values() is protected, we cannot call it directly from main() ) */
    void call_set_values(double x, double y) {
        set_values(x,y);
    }

};

// Instantiation of this derived class will call the parameterised constructor of the base class
class Fish: public Animal {

    public:

    double fin_length;

    Fish (double x, double y, double z) : fin_length(z), Animal (x,y) {}
};

/* A class may inherit from more than one class by specifying more base classes, in a comma-
   separated list, in the declaration of a derived class. */
class Ape: public Animal, public Person {

    public:

    Ape (double a, double x_1, double x_2, double y_1, double y_2) : \
        Person(a,x_1,y_1), Animal (x_2,y_2) {}

};

int main () {

    Animal toucan_2;
    Animal toucan_1(60.,600.);

    // Function taking object of class as a parameter
    toucan_2 = clone(toucan_1);

    std :: cout << "Height to weight ratio of toucan #2: " << toucan_2.ratio() << "\n";

    // Friend classes
    Animal eagle;
    Person john_seed (32,180.,60000.);
    eagle.transform(john_seed); // Person is friend of Animal, so can call transform() even
                                // though transform() is private (default, defined outside class)
    std :: cout << "Height to weight ratio of john seed as eagle: " << eagle.ratio() << "\n";

    // INHERITANCE
    Bird eagle_bird(200.); // Notice that the default constructor of Animal gets called here
    eagle_bird.call_set_values(90.,5000.);
    std :: cout << "Eagle wingspan: " << eagle_bird.wingspan << "\n";
    std :: cout <<" Eagle height: " << eagle_bird.get_height() << "\n";

    /* In principle, a publicly derived class inherits access to every member of a base class
       except: its constructors and its destructor, its assignment operator members, its friends,
       and its private members.
       Even though access to the constructors and destructor of the base class is not inherited
       as such, they are automatically called by the constructors and destructor of the derived
       class.
       Unless otherwise specified, the constructors of a derived class call the default constructor
       of its base classes (i.e. the constructor taking no arguments). Calling a different
       constructor of a base class is also possible, using the same snyax used to initialise
       member variables in the initialisation list */

    Fish tuna_fish (20.,200.,5.); // this will call the parameterised constructor of animal
    std :: cout << "Fin length of tuna: " << tuna_fish.fin_length << "\n";
    std :: cout << "Height of tuna: " << tuna_fish.get_height() << "\n";

    // Multiple inheritance
    Ape orangutan(15,120.,120.,15000.,15000.);
    std :: cout << "Height of orangutan: " << orangutan.get_height() << "\n";

    return 0;
}
