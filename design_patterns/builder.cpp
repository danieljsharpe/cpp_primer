/*
C++ creational design patterns: BUILDER
Separates object construction from its representation

Intent:
-separate the construction of a complex object from its representation so that the same
construction process can create different representations
-parse a complex representation, create one of several targets

The problem:
an application needs to create the elements of a complex aggregate. The specification for the
aggregate exists on secondary storage and one of many representations needs to be built in
primary storage.

A BUILDER pattern constructs the target step by step, under the control of the "director".
This distinguishes the BUILDER from other creational patterns, and affords finer control over
the construction process. The "director" invokes BUILDER services. The BUILDER creates part
of the complex object each time it is called and maintains all in an intermediate state. When
the product is finished, the client retrieves the result from the BUILDER.
In other words, the BUILDER hierarchy makes possible the polymorphic creation of many
different targets/representations.
In summary, the BUILDER pattern separates the construction of a complex object from its
representation so that the same construction process can create different representations.

Check list:
1. Decide if a common input and many possible representations (or outputs) is the problem at hand.
2. Encapsulate the parsing of the common input in a "Reader" class
3. Design a standard protocol for creating all possible output representations. Capture the
steps of this protocol in a BUILDER interface.
4. Define a BUILDER derived class for each target representation
5. the client create a "Reader" object and a "Builder" object, and registers the latter with
the former.
6. The client asks the "Reader" to "construct"
7. The client asks the "Builder" to return the result

Rules of thumb:
-sometimes creational patterns are complementary: BUILDER can use one of the other patterns to
implement which components get built. ABSTRACT FACTORY, BUILDER & PROTOTYPE can use SINGLETON
in their implementations.
-BUILDER focusses on constructing a complex object step by step. ABSTRACT FACTORY emphasises
a family of product objects (either simple or complex). BUILDER returns the product as a final
step, but in ABSTRACT FACTORY the product gets returned immediately.
-BUILDER often builds a COMPOSITE

Discussion:
The forte of BUILDER is constructing a complex object step by step. An abstract base class
declares the standard construction process, and concrete derived classes define the
appropriate implementation for each step of the process.
Use of a BUILDER means that each platform that can be built by the BUILDER has its own
platform-specific mechanisms defined in each platform's concrete derived class. A single
"Reader" object (ie parser) retrieves the specifications for building and proceeds to
delegate each build step to the builder object that was registered by the client. Upon
completion, the client retrieves the end result from the BUILDER.

*/

#include <iostream>
#include <string.h>
using namespace std;

enum SandwichType {
    bread_type, filling1, filling2
};

struct SandwichAttribute {
    SandwichType swtype;
    char value[30];
};

class Sandwich {
    public:
        Sandwich(const char *swtype) {
            cout << "Making a sandwich of type: " << swtype << "\n";
        }
        void set_bread_type(const char *name_bread_type, const char *skewer) {
            cout << " In set_bread_type()\n" << " name of bread type: " << \
                    name_bread_type << " skewer specification: " << skewer << "\n";
            strcat(_desc,_temp);
        }
        void set_filling1(const char *name_filling1, const char *temperature) {
            cout << " In set_filling1()\n" << " name of filling #1: " << \
                    name_filling1 << " how hot?: " << temperature << "\n";
            strcat(_desc,_temp);
        }
        void set_filling2(const char *name_filling2, const char *how_much) {
            cout << " In set_filling2()\n" << "name of filling #2: " << \
                    name_filling2 << " how much of filling #2?: " << how_much << "\n";
            strcat(_desc,_temp);
        }
        const char *get_state() {

        }
    private:
        char _desc[30], _temp[30];
};

class Builder {
    public:
        virtual void configure_bread_type(const char *) = 0;
        virtual void configure_filling1(const char *) = 0;
        virtual void configure_filling2(const char *) = 0;
        Sandwich *get_result() {
            return _result;
        }
    protected:
        Sandwich *_result;
};

class ChurrascoBuilder: public Builder {
    public:
        ChurrascoBuilder () {
            _result = new Sandwich("Churrasco");
        }
        void configure_bread_type(const char *skewer) {
            _result->set_bread_type("toasted_bun",skewer);
        }
        void configure_filling1(const char *temperature) {
            _result->set_filling1("steak",temperature);
        }
        void configure_filling2(const char *how_much) {
            _result->set_filling2("avocado",how_much);
        }
};

class MilanesaBuilder: public Builder {
    public:
        MilanesaBuilder () {
            _result = new Sandwich("Milanesa");
        }
        void configure_bread_type(const char *skewer) {
            _result->set_bread_type("baguette",skewer);
        }
        void configure_filling1(const char *temperature) {
            _result->set_filling1("breaded_meat",temperature);
        }
        void configure_filling2(const char *how_much) {
            _result->set_filling2("shredded_lettuce",how_much);
        }
};

class Reader {
    public:
        void setBuilder(Builder *b) {
            _builder = b;
        }
        void construct(SandwichAttribute[], int);
    private:
        Builder *_builder;
};

void Reader::construct(SandwichAttribute list[], int num) {
    for (int i=0;i<num;i++) {
        if (list[i].swtype==bread_type) {
            _builder->configure_bread_type(list[i].value); }
        else if (list[i].swtype==filling1) {
            _builder->configure_filling1(list[i].value); }
        else if (list[i].swtype==filling2) {
            _builder->configure_filling2(list[i].value); }
    }
}

const int NUM_ENTRIES = 6;
SandwichAttribute input[NUM_ENTRIES] = {
    { bread_type, "with_olive" },
    { bread_type, "without_olive" },
    { filling1, "cold" },
    { filling1, "hot" },
    { filling2, "heaps of" },
    { filling2, "just a little"}
};

int main () {

    Reader reader;

    // make 2 churrasco sandwiches with the specifications (3x2=6) outlined in the "input"
    // SandwichAttribute object
    ChurrascoBuilder churrascobuilder;
    reader.setBuilder(&churrascobuilder);
    reader.construct(input,NUM_ENTRIES);
    cout << churrascobuilder.get_result()->get_state() << "\n";
    cout << "\n\n";

    // make 2 milanesa sandwiches with the specifications (3x2=6) outlined in the "input"
    // SandwichAttribute object
    MilanesaBuilder milanesabuilder;
    reader.setBuilder(&milanesabuilder);
    reader.construct(input,NUM_ENTRIES);
    cout << milanesabuilder.get_result()->get_state() << "\n";


    return 0;
}
