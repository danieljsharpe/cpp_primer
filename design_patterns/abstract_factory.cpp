/*
C++ ABSTRACT FACTORY Creational pattern
Creates an instance of several families of classes.

INTENT
-Provide an interface for creating families of related or dependent objects without specifying their concrete classes
-a hierarchy that encapsulates: many possible "plantforms", and the construction of a suite of "products"
-the NEW operator considered harmful.

PROBLEM
-if an application is to be portable, it needs to encapsulate platform dependencies. Too often, this encapsulation is not
engineered in advance, and lots of "#ifdef" case statements with options for all currently supported platforms begin
to procreate like rabbits throughout the code!!

DISCUSSION
-provide a level of indirection that abstracts the creation of families of related or dependent objects without directly
specifying their concrete classes. The "factory" object has the responsibility for providing creation services for the
entire platform family. Clients never create platform obects directly, they ask the factory to do that for them.
-this mechanism makes exchanging product families easy because the specific class of the factory object appears only once
in the application - where it is maintained. The application can wholesale replace the entire family of products simply
by instantiating a different concrete instance of the abstract factory.
-because the service provided by the factory object is so pervasive, it is routinely implemented as a SINGLETON

STRUCTURE
-the ABSTRACT FACTORY defines a FACTORY METHOD per product. Each FACTORY METHOD encapsulates the NEW operator and the
concrete, platform-specific, product classes. Each "platform" is then moddelled with a FACTORY derived class.


                                                                          <<interface>>
         Class1---------------------------------------------------------->AbstractProductOne
          |   |                                                                 |
          |   |_______________________                               ___________|___________
          |                          |                               |                      |
          |                          |                      ProductOnePlatformOne         ProductOnePlatformTwo
      <<interface>>                  |
      AbstractPlatform               |
          |                          |______________________
          |                                                 |
    ______|_____                                       <<interface>>
    |           |                                      AbstractProductTwo
PlatformOne    PlatformTwo                                  |
               +makeProductOne()               _____________|___________
               +makeProductTwo                 |                        |
                                     ProductTwoPlatformOne         ProductTwoPlatformTwo

where:     makeProductOne: return new ProductOnePlatformTwo
           makeProductTwo: return new ProductTwoPlatformTwo


EXAMPLE
-The purpose of the ABSTRACT FACTORY is to provide an interface for creating families of related objects, without specifying
concrete classes.
-As an illustrative example, consider the machinery used to manufacture cars. The same machinery is used to create different
body parts, i.e. it is an ABSTRACT FACTORY. The different body parts (wheels, hood, door) are concrete classes. Through the use
of rollers to change the moulds, the concrete classes produced by the machinery can be changed. Different car models have different
variations of the body parts (e.g. different wheels). So we have families of classes.

                                 Machinery<-----------------------Client (parts list for Model)
                                 +makePart()
            ________________________|______________________________
            |                       |                              |
     Model3Wheels                 Model3Hood                  Model3Door
     Model2Wheels                 Model2Hood                  Model2Door
     Model1Wheels                 Model1Hood                  Model1Door
     +makeWheel()                 +makeHood()                 +makeDoor()       (: all of family of classes contain this method).


CHECK LIST
1. Decide if “platform independence” and creation services are the current source of pain.
2. Map out a matrix of “platforms” versus “products”.
3. Define a factory interface that consists of a FACTORY METHOD per product.
4. Define a factory derived class for each platform that encapsulates all references to the NEW operator.
5. The client should retire all references to NEW, and use the FACTORY METHODs to create the product objects.

RULES OF THUMB

1. Sometimes creational patterns are competitors: there are cases when either PROTOTYPE or ABSTRACT FACTORY could be used
profitably. At other times they are complementary: ABSTRACT FACTORY might store a set of PROTOTYPEs from which to clone and
return product objects, BUILDER can use one of the other patterns to implement which components get built. ABSTRACT FACTORY,
BUILDER, and PROTOTYPE can use SINGLETON in their implementation.
2. ABSTRACT FACTORY, BUILDER, and PROTOYTPE define a factory object that’s responsible for knowing and creating the class of
product objects, and make it a parameter of the system. ABSTRACT FACTORY has the factory object producing objects of several
classes. BUILDER has the factory object building a complex product incrementally using a correspondingly complex protocol.
PROTOTYPE has the factory object (aka prototype) building a product by copying a PROTOTYPE object.
3. ABSTRACT FACTORY classes are often implemented with FACTORY METHODs, but they can also be implemented using PROTOTYPE.
4. ABSTRACT FACTORY can be used as an alternative to FACADE to hide platform-specific classes.
5. BUILDER focuses on constructing a complex object step by step. ABSTRACT FACTORY emphasizes a family of product objects
(either simple or complex). BUILDER returns the product as a final step, but as far as the ABSTRACT FACTORY is concerned,
 the product gets returned immediately.
6. Often, designs start out using FACTORY METHOD (less complicated, more customizable, subclasses proliferate) and evolve
toward ABSTRACT FACTORY, PROTOTYPE, or BUILDER (more flexible, more complex) as the designer discovers where more
flexibility is needed.


IMPLEMENTATION & DISCUSSION
-Think of constructors as factories that churn out objects. Here we are allocating the constructor responsibility to a factory
object, and then using inheritance and virtual member functions to provide a "virtual constructor" capability. So there are two
dimensions of decoupling occurring. The client uses the factory object instead of NEW to request instances; and the client
"hard-wires" the family, or class, of that factory only once, and throughout the remainder of the application only relies
on the abstract base class
*/

#include <iostream>

using namespace std;

class Shape {
  public:
    Shape() {
      id_ = total_++;
    }
    virtual void draw() = 0;
  protected:
    int id_;
    static int total_;
};
int Shape::total_ = 0;

class Circle : public Shape {
  public:
    void draw() {
      cout << "circle " << id_ << ": draw" << endl;
    }
};
class Square : public Shape {
  public:
    void draw() {
      cout << "square " << id_ << ": draw" << endl;
    }
};
class Ellipse : public Shape {
  public:
    void draw() {
      cout << "ellipse " << id_ << ": draw" << endl;
    }
};
class Rectangle : public Shape {
  public:
    void draw() {
      cout << "rectangle " << id_ << ": draw" << endl;
    }
};

class Factory {
  public:
    virtual Shape* createCurvedInstance() = 0;
    virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory {
  public:
    Shape* createCurvedInstance() {
      return new Circle;
    }
    Shape* createStraightInstance() {
      return new Square;
    }
};
class RobustShapeFactory : public Factory {
  public:
    Shape* createCurvedInstance()   {
      return new Ellipse;
    }
    Shape* createStraightInstance() {
      return new Rectangle;
    }
};


int main() {

#define SIMPLE = true

#ifdef SIMPLE // compile this part of the program since SIMPLE is defined
  Factory* factory = new SimpleShapeFactory;
#elif ROBUST
  Factory* factory = new RobustShapeFactory; // do not compile this part of the program since ROBUST is not defined
#endif
  Shape* shapes[3];

  shapes[0] = factory->createCurvedInstance();   // shapes[0] = new Ellipse;
  shapes[1] = factory->createStraightInstance(); // shapes[1] = new Rectangle;
  shapes[2] = factory->createCurvedInstance();   // shapes[2] = new Ellipse;

  for (int i=0; i < 3; i++) {
    shapes[i]->draw();
  }
}
