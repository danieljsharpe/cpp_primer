/*
SMART POINTERs in C++

A SMART POINTER is an abstract data type that simulates a pointer while providing added features, such as automatic memory
management and bounds checking. Such features are intended to reduce bugs caused by the misuse of pointers, while retaining
efficiency. In particular, SMART POINTERs prevent most situations of memory leaks by making the memory deallocation
(or, more generally, object destruction) automatic: an object controlled by a SMART POINTER is automatically destroyed
(finalised and then deallocated) when the last (or only) owner of an object is destroyed, for example because the owner is a
local variable, and execution leaves the variable's scope. Smart pointers also eliminate dangling pointers by postponing
destruction until an object is no longer in use.

In C++, a SMART POINTER is implemented as a template class that mimics, by means of operator overloading, the behaviours of a
traditional (raw) pointer (e.g. dereferencing, assignment) while providing additional memory management features.
SMART POINTERs can facilitate so-called "intentional programming" by expressing, in the type, how the memory of the referent
of the pointer will be managed. e.g. if a C++ function returns a pointer, there is no way to know whether the caller should
delete the memory of the referent when the caller is finished with the information:

some_type* ambiguous_function(); // What should be done with the result?

C++11 introduced a way to ensure correct memory management in this case by declaring the function to return an abstract data
type: std::unique_ptr (defined in the header <memory>), e.g.

std::unique_ptr<some_type> obvious_function();

The declaration of the function return type as a unique_ptr makes explicit the fact that the caller takes ownership of the
result, and the C++ runtime ensures that the memory for *some_type will be reclaimed automatically.
The use of SMART POINTERs is generally preferred to, and helps avoid the use of, (excessive) NEW and DELETE statements.

A std::unique_ptr can be made with the std::make_unique function. However, this function was only introduced in C++14, see
the recommended workaround implementation below.
*/

#include <iostream>
#include <memory>
#include <cassert>
using namespace std;

// workaround implementation to make std::unique_ptr in C++11 (from cppreference)
// note: this implementation does not disable this overload for array types
// make_unique is effectively a modern alternative to the NEW operator
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


// example returning a unique_ptr in a function
std::unique_ptr<int> ret_int_unique_ptr (int x, int y) {
    return make_unique<int>(x+y);
}

// integer vector (of length 3) structure used to illustrate std::unique_ptr data structures of custom types
struct Vec3 {
    int x, y, z;
    Vec3() : x(0), y(0), z(0) { }
    Vec3(int x, int y, int z) :x(x), y(y), z(z) { }

    friend std::ostream& operator<<(std::ostream& os, Vec3& v) {
        return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}'; }
};

// function for testing std::weak_ptr
void observe_weak_ptr(std::weak_ptr<int> gw) {
    cout << "weak_ptr use_count: " << gw.use_count() << endl;
    // lock is used to ensure the validity of the weak_ptr
    if (auto spt = gw.lock()) { // a weak_ptr (gw) has to be copied into a shared_ptr (spt) before usage
        cout << "object referenced by gw is: " << *spt << "\n"; }
    else {
        cout << "gw is expired: " << gw.expired() << endl; }
}

int main () {

    // std::unique_ptr
    /*
    A std::unique_ptr is a container for a raw pointer, which the unique_ptr is said to "own". A unique_ptr explicitly prevents
    copying of its contained pointer (as would happen with normal assignment), but the std::move function can be used to transfer
    ownership of the contained pointer to another unique_ptr. A unique_ptr cannot be copied because its copy constructor and
    assignment operators are explicitly deleted.
    */
    std::unique_ptr<int> p1(new int(5));
    // std::unique_ptr<int> p2 = p1; // Compile error (see explanation above)
    std::unique_ptr<int> p3 = std::move(p1); // Transfers ownership. p3 now owns the memory and p1 is set to nullptr.

    std::unique_ptr<Vec3> v1 = make_unique<Vec3>(); // call default constructor of Vec3
    std::unique_ptr<Vec3> v2 = make_unique<Vec3>(0,1,2); // call constructor of Vec3 that matches 3x int args

    std::cout << "make_unique<Vec3>():      " << *v1 << "\n"
              << "make_unique<Vec3>(0,1,2): " << *v2 << "\n";

    // member function reset() replaces the managed object. NB a unique_ptr that owns no object is called "empty"
    p3.reset(); // Deletes the memory.
    p1.reset(); // Does nothing. (p1 was previously std::move'd to p3)
    // reset() can be used to replace an owned instance of a class with a new class...
    std::unique_ptr<Vec3> v3 = make_unique<Vec3>();
    v3.reset(new Vec3()); // this calls the deleter for the old Vec3
    v3.reset(nullptr); // this releases and deletes the owned Vec3

    // member function release() releases the ownership of the managed object (if any). get() returns nullptr after the call.
    // the return value of release() is a pointer to the managed object or nullptr if there was no managed object, i.e. the
    // value which would be returned by get() before the call
    std::unique_ptr<Vec3> v4(new Vec3()); // create new Vec3
    Vec3* v4_raw = v4.release(); // release Vec3
    assert (v4.get()==nullptr); // Vec3 is no longer owned by the unique_ptr
    delete v4_raw; // v4_raw is a raw pointer so we have to DELETE the memory ourselves

    std::unique_ptr<int> returned_unique_ptr = ret_int_unique_ptr(2,3);
    // note that you cannot print a unique_ptr with <<, as this operator is not overloaded in the unique_ptr type
    // cout << "Value of ptr " << ptr << "\n"; // doesn't work
    // the dereference operators * and -> dereference the pointer to the managed object (thereby working as for a raw pointer)
    cout << "Value pointed ptr:    " << *returned_unique_ptr << "\n"; // does work
    cout << "Value of ptr->get():    " << v1.get() << "\n"; // also works
    // to access elems, the member function get() returns a pointer to the managed object (or nullptr if no object is owned).

    /*
    We can also have unique_ptr data structures referencing arrays.
    The single-object version of the type is defined unique_ptr<T>, the array version unique_ptr<T[]>
    The array version has defined (and therefore overloaded) operator[], allowing access to elements of an array managed by
    a unique_ptr, via the usual raw pointer syntax.
    */
    const int size = 10;
    std::unique_ptr<int[]> fact(new int[size]);
    for (int i = 0; i < size; ++i) {
        fact[i] = (i == 0) ? 1 : i * fact[i-1];
    }
    for (int i = 0; i < size; ++i) {
        std::cout << i << ": " << fact[i] << "  " << fact.get()[i] << "\n"; // note use of equivalent syntaxes
    }
    /* Note that as the unique_ptr type that manages a single object is allocated with NEW, the unique_ptr type that manages
    a dynamically-allocated array of objects is allocated with NEW[] */


    /*
    we don't need to worry about tidying with DELETE statements etc.; the unique_ptr handles this for us :)

    In summary: unique_ptr is a SMART POINTER that owns and manages another object through a pointer and disposes of that
    object when the unique_ptr goes out of scope.
    */

    // std::shared_ptr
    /*
    C++11 also introduced std::shared_ptr and std::weak_ptr defined in the header <memory>, and the std::make_shared function to
    safely allocate dynamic memory for shared_ptr variables.
    Like a unique_ptr, a shared_ptr is a container for a raw pointer (i.e. is a SMART POINTER). unique_ptr, as its
    name suggests, can only point to one resource. i.e. there can be at most one unique_ptr pointing at any one resource, and the
    resource is automatically reclaimed when that unique_ptr is destroyed. Thus e.g. any attempt to make a copy of a unique_ptr
    causes a compile-time error:

    unique_ptr<T> myptr(new T); // okay
    unique_ptr<T> myotherptr = myptr; // error: not allowed to copy unique_ptr.

    shared_ptr, by contrast (and again as its name suggests), uses "reference counting" to track how many pointers refer to a
    resource (NB so you must be careful not to introduce any reference cycles), and multiple pointers are allowed to point to the
    same resource. Whereas with unique_ptr the resource is freed when the single (i.e. unique) smart pointer has gone out of scope
    (i.e. the object is destroyed and memory is deallocated), with shared_ptr the resource is freed when the last smart pointer
    (number of owning smart pointers is tracked by the reference counter) goes out of scope.

    In summary: unique_ptr is a smart pointer which owns an object exclusively, whereas shared_ptr is a smart pointer for shared
    ownership, and is both copyable and moveable.
    */

    /* shared_ptr has the get(), reset(), swap(), operator=() (assignment), operator*() and operator->() member functions,
    same as unique_ptr, but not release(). */
    std::shared_ptr<int> sp0(new int(5)); // valid, allocates 1 integer and initialize it with value 5
    // note: shared_ptr does not work with arrays until C++17
    // std::shared_ptr<int[]> sp1(new int[5]); // valid, allocates 5 integers (not initialised)
    std::shared_ptr<int> sp2 = sp0; // Both sp2 and sp0 now own the memory. This (copying) would not be allowed for a unique_ptr

    sp0.reset(); // Memory still exists, due to sp2.
    sp2.reset(); // Deletes the memory, since no one else owns the memory.

    // a more complex example using AUTO (not allowed for std::make_unique until C++14) and a custom struct
    struct mystruct {
        mystruct(int i): i(i) {} // NB explicit constructor needed
        int i;
    };
    auto sp3 = std::make_shared<mystruct>(12);
    std::cout << sp3->i << "\n";

    // std::weak_ptr
    /*
    A weak_ptr is another container for a raw pointer. It is created as a copy of a shared_ptr. The existence or destruction of
    weak_ptr copies of a shared_ptr have no effect on the shared_ptr or its other copies. After all copies of a shared_ptr have
    been destroyed, all weak_ptr copies become empty.
    */

    std::shared_ptr<int> sp4 = std::make_shared<int>(5);
    std::weak_ptr<int> wp1 {sp4}; // sp4 owns the memory.

    /* the lock() member function of std::weak_ptr creates a shared_ptr that manages the referenced object */
    std::shared_ptr<int> sp5 = wp1.lock(); // Now sp4 and sp5 own the memory.
    // sp5 is initialized from a weak pointer, so you have to check if the memory still exists!
    if (sp5) { /* ... */ } // this code does not get executed
    //sp5 is destroyed. Memory is owned by sp4.

    sp4.reset(); // Delete the memory.

    std::shared_ptr<int> sp6 = wp1.lock(); 
    // Memory is gone (both sp4 and sp5 destroyed), so we get an empty shared_ptr for sp6.
    if (sp6) { /* ... */ } // this code does not get executed

    /*
    In summary, std::weak_ptr is a smart pointer that holds a non-owning (i.e. "weak") reference to an object that is managed by
    std::shared_ptr. It must be converted to std::shared_ptr (via its lock() member function) in order to access the referenced
    object. In this way, std::weak_ptr models temporary ownership: when an object needs to be accessed only if it exists, and it
    may be deleted at any time by someone else, std::weak_ptr is used to track the object, and it is converted to std::shared_ptr
    to assume temporary ownership. If the original std::shared_ptr is destroyed at this time, the object's lifetime is extended
    until the temporary std::shared_ptr is destroyed as well.
    In addition, std::weak_ptr is used to break circular references of std::shared_ptr.

    std::weak_ptr also has the following member functions (among others) in addition to lock():
    - operator=     assigns the weak_ptr
    - reset         releases the ownership of the managed object (as for std::unique_ptr and std::shared_ptr)
    - use_count     returns the number of shared_ptr objects that manage the object (as for std::shared_ptr)
    - expired       checks whether the referenced object was already deleted
    */

    std::weak_ptr<int> wptr;
    {
    auto sp7 = std::make_shared<int>(42);
    wptr = sp7; // assignment of weak_ptr from shared_ptr
    observe_weak_ptr(wptr); // weak_ptr wptr has not expired
    }
    observe_weak_ptr(wptr); // now outside the curly braces, weak_ptr wptr has expired (the object it references, the int 42
                            // declared within the curly braces, has gone out of scope

    /* to emphasise; it is not possible to access the stored pointer in a weak_ptr without locking it (via lock() member func) into
    a shared_ptr */

    return 0;
}
