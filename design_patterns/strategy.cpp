/*
C++ STRATEGY Behavioural pattern
Encapsulates an algorithm inside a class.

INTENT
-Define a family of algorithms, encapsulate each one, and make them interchangeable. STRATEGY lets the algorithm vary
independently from the clients that use it
-Capture the abstraction in an interface, bury implementation details in derived classes

PROBLEM
-One of the dominant strategies of object-oriented design is the "open-closed" principle. This is routinely achieved
by encapsulating interface details in a base class, and burying implementation details in derived classes. Clients can
then couple themselves to an interface, and not have to experience the upheaval associated with change: no impact
when the number of derived classes changes, and no impact when te implementation of a derived class changes.

e.g. (where the client is a program to an interface, not an implementation):

Client --->  <<interface>> Abstraction
                           +doSomething()
                              |
           ___________________|__________________
           |                                    |
      ImplementationOne                     ImplementationTwo
      +doSomething()                        +doSomething()

-This design approach minimises coupling. Since the client is coupled only to an abstraction, and not a particular
realisation of that abstraction, the client could be said to be practicing "abstract coupling", an object-oriented
variant of the more generic exhortation "minimise coupling".
A more popular characterisation of this "abstract coupling" principle is "program to an interface, not an implementation".

-Clients should prefer the "additional level of indirection" that an interface (or an abstract base class) affords. The
interface captures the abstraction the client wants to exercise, and the implementations of that interface are
effectively hidden.

STRUCTURE
-The Interface entity could represent either an abstract base class, or the method signature expectations by the client. In the
former case, the inheritance hierarchy represents dynamic polymorphism. In the latter case, the Interface entity represents
template code in the client and the inheritance hierarchy represents static polymorphism.

Client
  |
  V       -strategy     Interface
context---------------->+algorithm()
           ___________________|__________________
           |                                    |
      ImplementationOne                     ImplementationTwo
      +algorithm()                          +algorithm()

EXAMPLE
-a STRATEGY defines a set of algorithms that can be used interchangeably. For example, one can travel to an airport by various
means:

TransportationToAirport------->Strategy
                                 |
                      ___________|___________
                      |          |           |
                     Bus        Car         Train

CHECK LIST

1. Identify an algorithm (i.e. a behavior) that the client would prefer to access through a “flex point”.
2. Specify the signature for that algorithm in an interface.
3. Bury the alternative implementation details in derived classes.
4. Clients of the algorithm couple themselves to the interface.

RULES OF THUMB

-STRATEGY is like TEMPLATE METHOD except in its granularity.
-STATE is like STRATEGY except in its intent.
-STRATEGY lets you change the guts of an object. DECORATOR lets you change the skin.
-STATE, STRATEGY, BRIDGE (and to some degree ADAPTER) have similar solution structures. They all share elements of the
‘handle/body’ idiom. They differ in intent - that is, they solve different problems.
-STRATEGY has 2 different implementations, the first is similar to STATE. The difference is in binding times
(STRATEGY is a bind-once pattern, whereas STATE is more dynamic).
-STRATEGY objects often make good FLYWEIGHTS.


IMPLEMENTATION & DISCUSSION
-the STRATEGY pattern suggests: encapsulating an algorithm in a class hierarchy, having clients of that algorithm hold a pointer
to the base class of that hierarchy, and delegating all requests for the algorithm to that "anonymous" contained object.
-in the example below, the STRATEGY base class knows how to collect a paragraph of input and implement the skeleton of the
"format" algorithm. It defers some details of each individual algorithm to the "justify" member which is supplied by each
concrete derived class of STRATEGY. The TestBed class models an application class that would like to leverage the services
of a run-time-specified derived "Strategy" object.

*/

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Strategy;

class TestBed
{
  public:
    enum StrategyType
    {
        Dummy, Left, Right, Center
    };
    TestBed()
    {
        strategy_ = NULL;
    }
    void setStrategy(int type, int width);
    void doIt();
  private:
    Strategy *strategy_;
};

class Strategy
{
  public:
    Strategy(int width): width_(width){}
    void format()
    {
        char line[80], word[30];
        ifstream inFile("quote.txt", ios::in);
        line[0] = '\0';

        inFile >> word;
        strcat(line, word);
        while (inFile >> word)
        {
            if (strlen(line) + strlen(word) + 1 > width_)
              justify(line);
            else
              strcat(line, " ");
            strcat(line, word);
        }
        justify(line);
    }
  protected:
    int width_;
  private:
    virtual void justify(char *line) = 0;
};

class LeftStrategy: public Strategy
{
  public:
    LeftStrategy(int width): Strategy(width){}
  private:
     /* virtual */void justify(char *line)
    {
        cout << line << endl;
        line[0] = '\0';
    }
};

class RightStrategy: public Strategy
{
  public:
    RightStrategy(int width): Strategy(width){}
  private:
     /* virtual */void justify(char *line)
    {
        char buf[80];
        int offset = width_ - strlen(line);
        memset(buf, ' ', 80);
        strcpy(&(buf[offset]), line);
        cout << buf << endl;
        line[0] = '\0';
    }
};

class CenterStrategy: public Strategy
{
  public:
    CenterStrategy(int width): Strategy(width){}
  private:
     /* virtual */void justify(char *line)
    {
        char buf[80];
        int offset = (width_ - strlen(line)) / 2;
        memset(buf, ' ', 80);
        strcpy(&(buf[offset]), line);
        cout << buf << endl;
        line[0] = '\0';
    }
};

void TestBed::setStrategy(int type, int width)
{
  delete strategy_;
  if (type == Left)
    strategy_ = new LeftStrategy(width);
  else if (type == Right)
    strategy_ = new RightStrategy(width);
  else if (type == Center)
    strategy_ = new CenterStrategy(width);
}

void TestBed::doIt()
{
  strategy_->format();
}

int main()
{
  TestBed test;
  int answer, width;
  cout << "Exit(0) Left(1) Right(2) Center(3): ";
  cin >> answer;
  while (answer)
  {
    cout << "Width: ";
    cin >> width;
    test.setStrategy(answer, width);
    test.doIt();
    cout << "Exit(0) Left(1) Right(2) Center(3): ";
    cin >> answer;
  }
  return 0;
}
