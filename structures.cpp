#include <iostream>

using namespace std;

// A data structure is a group of data elements (members) grouped together under one name
struct fruit { // declare structure type "fruit"
    char colour[10]; // list data members
    double price;
    int weight;
    int * weight_ptr;
} apple, banana; // optional object_names can be used to directly declare objects of the structure type

fruit melon, kiwi; // another way of declaring objects of the structure type
fruit pineapple[3]; // because structures are types, they can also be used as the type of arrays
fruit * fruit_ptr; // like any other type, structures can be pointed to by its own type of pointers
                   // here, fruit_ptr is a pointer to point to objects of structure type fruit

// structures can also be nested in such a way that an element of a structure is itself another structure
struct customer {
    char * name;
    int age;
    fruit fav_fruit;
} john, jacob, joseph, faith;
customer * customer_ptr = &john;

/* Unions are similar in syntax to structures. Their purpose is to save memory by using the same memory
region for storing different objects at different times. So if you know that several objects in your
program hold values with non-overlapping value-lifetimes, then you can "merge" these objects into a
union and thus save memory. A union can have any number of members, but only one is "active" at any one
time. Only this "active" member can be read. By writing into another member, the "active" status is
switched to that member. */
union limit {
    int hi; // N.B. all members refer to the same location in memory
    int lo; // note that, in general, the members can be of different types
} current_bound;


int main() {

    melon.price = 1.20; // use dot syntax to directly access members of a structure type, e.g. assignment
    std :: cout << "Price of melon: " << melon.price << "\n";

    /* Not only the data members but also the objects themselves (e.g. apple) are variables of the
    struct_type (here, fruit). So, for e.g., both can be passed to functions just as if they were
    simple variables. Therefore, one of the features of data structures is the ability to refer to
    both their members individually or to the entire structure as a whole. In both cases the same
    identifier is used: the name of the structure   */

    // Let's say there are multiple variants of pineapple, the members for each of which are accessed thus:
    pineapple[0].weight = 10;
    std :: cout << "Weight of type 1 pineapple: " << pineapple[0].weight << "\n";

    // Using pointers to structures
    fruit_ptr = &melon; // value of pointer fruit_ptr assigned address of object melon
    fruit_ptr->price = 1.40; // the arrow operator is a dereference operator that is used
            // exclusively with pointers to objects that have members. This operator serves to
            // access the member of an object directly from its address
    (*fruit_ptr).weight = 5; // for all purposes, this expression is equivalent to the arrow operator
    std :: cout << "New price of melon: " << melon.price << " Weight: " << melon.weight << "\n";
    
    apple.weight_ptr = &apple.weight;
    *apple.weight_ptr = 6; // access value pointed by the pointer member weight_ptr of the object apple
                           // equivalent to *(apple.weight_ptr)
    std :: cout << "Weight of apple: " << apple.weight << "\n";

    // using nesting structures:
    john.name = "John Seed";
    john.age = 32;
    customer_ptr->fav_fruit = melon;
    std :: cout << "Name of customer: " << (*customer_ptr).name << "\n";
    std :: cout << "Price of John's favourite fruit: " << john.fav_fruit.price << "\n";
    std :: cout << "Weight of John's favourite fruit: " << customer_ptr->fav_fruit.weight << "\n";

    // unions
    current_bound.hi = 10;
    // assume that we no longer need hi, and instead are interested in a lower bound
    current_bound.lo = 2;

    return 0;
}
