/*
C++ structural design pattern: PROXY
An object representing another object.

We desire to:
-provide a surrogate or placeholder for another object to control access to it
-use an extra level of indirection to support distributed, controlled or intelligent
access
-add a wrapper and delegation to protect the real component from undue complexity.

The problem:
-you need to support resource-hungry obects, and you do not want to instantiate such
objects unless and until they are actually requested by the client.

The solution:
-design a surrogate (or PROXY) object that:
  -instantiates the real object the first time the client makes a request for the proxy
  -remembers the identity of this real object
  -forwards the instigating request to this real object.
 (then all subsequenet requestes are simply forwarded directly to the encapsulated
  real object).

Situations in which the PROXY pattern is applicable:
1. a virtual proxy is a placeholder for "expensive to create" objects. The real object
is only created when a client first requests/accesses the object.
2. a remote proxy provides a local representative for an objecct that resides in a
different address space.
3. a protective proxy controls access to a sensitive master object. The surrogate object
checks that the caller has the access permissions required prior to forwarding the
request.
4. a smart proxy interposes additional actions when an object is accessed. Typical uses
include:
    -counting the no. of references to the real object so that it can be freed
     automatically when there are no more references (aka smart pointer)
    -loading a persistent object into memory when its first referenced
    -checking that the real object is locked before it is accessed to ensure that no
     other object can change it.

Structure:
the proxy object stands in place of the real object

          Real object
         /
Interface
         \
          Proxy object

all the above classes have the do_it() method. The proxy object is asociated with a
wrappee and can incorporate additional optional functionality (wrappee->do_it())

Check list:
1. identify the leverage or "aspect" that is best implemented as a wrapper or surrogate
2. define an interface that will make the proxy and the original component inter-
changeable
3. consider defining a FACTORY that can encapsulate the decision of whether a proxy or
original object is desirable.
4. the wrapper class holds a pointer to the real class and implements the interface
5. the pointer may be initialised at construction, or on first use
6. each wrapper method contributes its leverage, and delegates to the wrappee object.

Rules of thumb:
- ADAPTER provides a different interface to its subject. PROXY provides the same
interface. DECORATOR provides an enhanced interface.
- DECORATOR and PROXY have different purposes but similar structures. Both describe how
to provide a level of indirection to another object, and the implementations keep a
reference to the object to which they forward requests.


Design pattern to achieve initialisation on first use (VIRTUAL PROXY)
(illustrated in code below):
1. design an "extra level of indirection" wrapper class
2. the wrapper class holds a pointer to the real class
3. the pointer is initialised to null
4. when a request comes in, the real object is created "on first use"
5. the request is always delegated
*/

#include <iostream>
using namespace std;

class RealObject {
    int m_id;
    public:
        RealObject (int id) {
            m_id = id;
            cout << " called RealObject constructor for id: " << m_id << "\n";
        }
        ~RealObject() {
            cout << " called RealObject destructor for id: " << m_id << "\n";
        }
        void do_it() {
            cout << " called do_it() for RealObject with id: " << m_id << "\n"; 
        }
};

// step 1.
class Wrapper {
    // step 2.
    RealObject *m_the_real_object;
    int m_id;
    static int s_next;
    public:
        Wrapper() {
            m_id = s_next++;
            // step 3.
            m_the_real_object = 0;
        }
        ~Wrapper() { delete m_the_real_object; }
        void do_it() {
            // step 4.
            if (!m_the_real_object) {
                cout << " first initialisation request: creating new real object\n ";
                m_the_real_object = new RealObject(m_id);
            }
            // step 5.
            m_the_real_object->do_it();
            }
};
int Wrapper::s_next = 1;


int main () {

    Wrapper objects[5];

    for (int i; true;) {
        // note that you will only get the "first initialisation request" message
        // the first time that you type a number!
        cout << "User input: Exit[0], Object[1-5] ... ";
        cin >> i;
        if (i==0) break;
        objects[i-1].do_it();
    }

    return 0;
}
