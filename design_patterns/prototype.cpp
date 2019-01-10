/*
C++ creational pattern: PROTOTYPE

INTENT
-specify the kinds of objects to create using a prototypical instance, and create new objects by copying this PROTOTYPE
-co-opt one instance of a class for use as a breeder of all future instances
-the NEW operator considered harmful

PROBLEM
-application "hard wires" the class of object to create in each NEW expression

DISCUSSION
-declare an abstract base class that specifies a pure virtual "clone" method, and maintains a dictionary of all "cloneable"
concrete derived classes. Any class that needs a "polymorphic constructor" capability: derives itself from the abstract base
class, registers its prototypical instance, and implements the clone() operation
-the client then, instead of writing code that invokes the NEW operator on a hard-wired class name, calls a "clone" operation
on the abstract base class, supplying a string or enumerated data type that designates the particular concrete derived class
that is desired.

STRUCTURE
-the FACTORY knows how to find the correct PROTOTYPE, and each Product knows how to spawn new instances of itself.

clonerRegistry is populated
each image derived class
registering an instance of itself
       |
       |                -clonerRegistry
   ImageHandler     ------------------------>  Image
   +populateImages()------------------------>  +clone(): image
       |                -images                   |
       |                                          |
       |                __________________________|____________________
       |                |                                             |
       |             ImageOne                                      ImageTwo
       |             +clone(): ImageOne
       |                |
       |            return new ImageOne this;
       |
       |
   images next
   clonerRegistry.get  lookupKey.clone;

EXAMPLE
-the PROTOTYPE pattern specifies the kind of objects to create using a prototypical instance. Prototypes of new products are
often built prior to full production, but in this example, the Prototype is passive and does not participate in copying itself -
(not a PROTOTYPE design pattern).
-mitotic division of a cell is an example of the PROTOTYPE design pattern - the prototype plays an *active* role in copying itself.
i.e. the cell clones itself

   Cell
   +split()
     ^
     |
     |
   SingleCellOrganism------------------------Clones
   +split()

CHECK LIST

1. Add a clone() method to the existing “product” hierarchy.
2. Design a “registry” that maintains a cache of prototypical objects. The registry could be encapsulated in a new FACTORY class,
   or in the base class of the “product” hierarchy.
3. Design a FACTORY METHOD that: may (or may not) accept arguments, finds the correct PROTOTYPE object, calls clone() on that
   object, and returns the result.
4. The client replaces all references to the NEW operator with calls to the FACTORY METHOD.

RULES OF THUMB

1. Sometimes creational patterns are competitors: there are cases when either PROTOTYPE or ABSTRACT FACTORY could be used properly.
   At other times they are complementary: ABSTRACT FACTORY might store a set of PROTOTYPEs from which to clone and return product
   objects. ABSTRACT FACTORY, BUILDER, and PROTOTYPE can use SINGLETON in their implementations.
2. ABSTRACT FACTORY classes are often implemented with FACTORY METHODs, but they can be implemented using PROTOTYPE.
3. FACTORY METHOD: creation through inheritance. PROTOTYPE: creation through delegation.
4. Often, designs start out using FACTORY METHOD (less complicated, more customizable, subclasses proliferate) and evolve toward
   ABSTRACT FACTORY, PROTOTYPE, or BUILDER (more flexible, more complex) as the designer discovers where more flexibility is needed.
5. PROTOTYPE doesn’t require subclassing, but it does require an “initialize” operation. FACTORY METHOD requires subclassing, but
   doesn’t require Initialize.
6. Designs that make heavy use of the COMPOSITE and DECORATOR patterns often can benefit from PROTOTYPE as well.
7. PROTOTYPE co-opts one instance of a class for use as a breeder of all future instances.
8. PROTOTYPEs are useful when object initialisation is expensive, and you anticipate few variations on the initialization parameters.
   In this context, PROTOTYPE can avoid expensive "creation from scratch", and support cheap cloning of a pre-initialized PROTOTYPE.
9. PROTOTYPE is unique among the other creational patterns in that it doesn’t require a class – only an object. Object-oriented
   languages like Self and Omega that do away with classes completely rely on prototypes for creating new objects.


DISCUSSION + EXAMPLE
-Consider the example below. The Image base class provides the mechanism for storying, finding and cloning the PROTOTYPE for all
derived classes. Each derived class specifies a private static data member whose initilisation "registers" a PROTOTYPE of itself
with the base class. When the client asks for a "clone" of a certain type, the base class finds the PROTOTYPE and calls clone()
on the correct derived class...

*/

#include <iostream>
using namespace std;

enum imageType
{
  LSAT, SPOT
};

class Image
{
  public:
    virtual void draw() = 0;
    static Image *findAndClone(imageType);
  protected:
    virtual imageType returnType() = 0;
    virtual Image *clone() = 0;
    // As each subclass of Image is declared, it registers its prototype
    static void addPrototype(Image *image)
    {
        _prototypes[_nextSlot++] = image;
    }
  private:
    // addPrototype() saves each registered prototype here
    static Image *_prototypes[10];
    static int _nextSlot;
};

Image *Image::_prototypes[];
int Image::_nextSlot;

// Client calls this public static member function when it needs an instance
// of an Image subclass
Image *Image::findAndClone(imageType type)
{
  for (int i = 0; i < _nextSlot; i++)
    if (_prototypes[i]->returnType() == type)
      return _prototypes[i]->clone();
  return NULL;
}

class LandSatImage: public Image
{
  public:
    imageType returnType()
    {
        return LSAT;
    }
    void draw()
    {
        std::cout << "LandSatImage::draw " << _id << std::endl;
    }
    // When clone() is called, call the one-argument ctor with a dummy arg
    Image *clone()
    {
        return new LandSatImage(1);
    }
  protected:
    // This is only called from clone()
    LandSatImage(int dummy)
    {
        _id = _count++;
    }
  private:
    // Mechanism for initializing an Image subclass - this causes the
    // default ctor to be called, which registers the subclass's prototype
    static LandSatImage _landSatImage;
    // This is only called when the private static data member is initiated
    LandSatImage()
    {
        addPrototype(this);
    }
    // Nominal "state" per instance mechanism
    int _id;
    static int _count;
};

// Register the subclass's prototype
LandSatImage LandSatImage::_landSatImage;
// Initialize the "state" per instance mechanism
int LandSatImage::_count = 1;

class SpotImage: public Image
{
  public:
    imageType returnType()
    {
        return SPOT;
    }
    void draw()
    {
        std::cout << "SpotImage::draw " << _id << std::endl;
    }
    Image *clone()
    {
        return new SpotImage(1);
    }
  protected:
    SpotImage(int dummy)
    {
        _id = _count++;
    }
  private:
    SpotImage()
    {
        addPrototype(this);
    }
    static SpotImage _spotImage;
    int _id;
    static int _count;
};

SpotImage SpotImage::_spotImage;
int SpotImage::_count = 1;

// Simulated stream of creation requests
const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] =
{
  LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT
};

int main()
{
  Image *images[NUM_IMAGES];

  // Given an image type, find the right prototype, and return a clone
  for (int i = 0; i < NUM_IMAGES; i++)
    images[i] = Image::findAndClone(input[i]);

  // Demonstrate that correct image objects have been cloned
  for (int i = 0; i < NUM_IMAGES; i++)
    images[i]->draw();

  // Free the dynamic memory
  for (int i = 0; i < NUM_IMAGES; i++)
    delete images[i];
}
