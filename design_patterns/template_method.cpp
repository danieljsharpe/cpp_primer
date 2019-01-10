/*
C++ TEMPLATE METHOD Behavioural pattern
Defer the exact steps of an algorithm to a subclass.

INTENT
-Define the skeleton of an algorithm in an operation, deferring some steps to client subclasses. TEMPLATE METHOD lets
subclasses redefine certain steps of an algorithm without changing the algorithm's structure
-Base class declares algorithm 'placeholders', and derived classes implement the placeholders.

PROBLEM
-Two different components have significant similarities, but demonstrate no reuse of common interface or implementation.
If a change common to both components becomes necessary, duplicate effort must be expended.

DISCUSSION
-The component designer decides which steps of an algorithm are invariant (or standard), and which are variant (or
customisable). The invariant steps are implemented in an abstract base class, while the variant steps are either given
a default implementation, or no implementation at all. The variant steps represent "hooks" or "placeholders", that can, or
must, be supplied by the component's client in a concrete derived class.
-the component designer mandates the required steps of an algorithm, and the ordering of the steps, but allows the component
client to extend or replace some number of these steps.
-TEMPLATE METHOD is used prominently in frameworks. Each framework implements the invariant pieces of a domain's
architecture, and defines "placeholders" for all necessary or interesting client customisation options. In so doing, the
framework becomes the "centre of the universe", and the client customisations are simply "the third rock from the sun".


STRUCTURE

stepOne
stepTwo
stepThree               ApplicationClassOne -- +stepTwo()
    |                  /
    |                 /
FrameworkClass--------
    |                 \
    |                  \
+templateMethod()       ApplicationClassTwo -- +stepTwo()
+stepOne()
+stepTwo()
+stepThree()

The implementation of template_method() is: call step_one(), call step_two(), call step_three(). step_two() is a "HOOK" method - 
a PLACEHOLDER. It is declared in the base class, and then defined in derived classes. FRAMEWORKS (large scale reuse
infrastructures) use TEMPLATE METHOD a lot. All reusable code is defined in the framework's base classes, and then clients of
the framework are free to define customisations by creating derived classes (e.g. ApplicationClassOne, with its own
implementation of stepTwo()) as needed.


EXAMPLE

The TEMPLATE METHOD defines a "skeleton" of an algorithm in an operation, and defers some steps to subclasses. For example, imagine
we have a base class Worker, and subclasses FireFighter & Postman. The base class Worker features methods that all derived classes
(i.e. types of worker) must do, e.g. +have_lunch() and +take_break(). The base class Worker features a placeholder for +work(), and 
each derived class features its own implementation of +work(), since different types of worker have to do different types of work!

CHECK LIST

1. Examine the algorithm, and decide which steps are standard and which steps are peculiar to each of the current classes.
2. Define a new abstract base class to host the "don’t call us, we’ll call you" framework.
3. Move the shell of the algorithm (now called the "template method") and the definition of all standard steps to the new base class.
4. Define a placeholder or “hook” method in the base class for each step that requires many different implementations.
   This method can host a default implementation – or – it can be defined as abstract (Java) or pure virtual (C++).
5. Invoke the hook method(s) from the template method.
6. Each of the existing classes declares an “is-a” relationship to the new abstract base class.
7. Remove from the existing classes all the implementation details that have been moved to the base class.
8. The only details that will remain in the existing classes will be the implementation details peculiar to each derived class.

RULES OF THUMB


1. STRATEGY is like TEMPLATE METHOD except in its granularity.
2. TEMPLATE METHOD uses inheritance to vary part of an algorithm. STRATEGY uses delegation to vary the entire algorithm.
3. STRATEGY modifies the logic of individual objects. TEMPLATE METHOD modifies the logic of an entire class.
4. FACTORY METHOD is a specialization of TEMPLATE METHOD.


EXAMPLE IMPLEMENTATION

Below we look at an example implementation. Note the following steps:

1. Standardize the skeleton of an algorithm in a base class “template method”
2. Steps requiring peculiar implementations are “placeholders” in base class
3. Derived classes implement placeholder methods

*/

#include <iostream>
using namespace std;

class Base
{
    void a()
    {
        cout << "a  ";
    }
    void c()
    {
        cout << "c  ";
    }
    void e()
    {
        cout << "e  ";
    }
    // 2. Steps requiring peculiar implementations are "placeholders" in base class
    virtual void ph1() = 0;
    virtual void ph2() = 0;
  public:
    // 1. Standardize the skeleton of an algorithm in a base class "template method"
    void execute()
    {
        a();
        ph1();
        c();
        ph2();
        e();
    }
};

class One: public Base
{
    // 3. Derived classes implement placeholder methods
    /*virtual*/
    void ph1()
    {
        cout << "b  ";
    }
    /*virtual*/
    void ph2()
    {
        cout << "d  ";
    }
};

class Two: public Base
{
    /*virtual*/
    void ph1()
    {
        cout << "2  ";
    }
    /*virtual*/
    void ph2()
    {
        cout << "4  ";
    }
};

int main()
{
  One one;
  Two two;
  Base *array[] = 
  {
     &one, &two
  };
  for (int i = 0; i < 2; i++)
  {
    array[i]->execute();
    cout << '\n';
  }
}
