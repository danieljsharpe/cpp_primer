/* C++ script to demonstrate the use of class templates */

#include <iostream>
using namespace std;

/*
Just like we can create function templates, we can also create class templates, allowing classes to have members that use
template parameters as types. e.g.:
*/

template <class T>
class mypair {

    T values [2];

    public:
    mypair (T first, T second) { // constructor declared inline (with the class definition)
        values[0]=first; values[1] = second; }

    T getmax (); // member function of class template declared outside
};


// in case that a member function is defined outside the definition of the class template, it is preceded with the prefix:
// template <...>
template <class T>
T mypair<T>::getmax () {
    T retval;
    retval = values[0]>values[1]? values[0] : values[1]; // note use of "?", the conditional operator. Syntax:
                                                         // condition ? result_if_true : result_if_false
    return retval;
}
/*
Note that there are 3 Ts in the above two-line declaration. The first one is the template parameter. The second refers to the
type returned by the function. The third T is also a requirement: it specifies that this function's template parameter is also
the class template parameter.
*/


/*
It is possible to define a different implementation for a template when a specific type is passed as template argument. This is
called a TEMPLATE SPECIALISATION.
e.g. lets suppose we have a very simple class called mycontainer that can store one elem of any type and that has just one member
function called increase(), which increases its value. But we find that when mycontainer stores an elem of type char it would be
more convenient to have a completely different implementation with a function member uppercase(), so we decide to declare a class
template specialisation for that type...
*/
// class template:
template <class T>
class mycontainer {
    T elem;
    public:
    mycontainer (T arg) { elem=arg; }
    T increase () { return ++elem; }
};
// class template specialisation:
// note the syntax:
// template <> class myclass <char> { ... };
// compare to the generic class template syntax:
// template <class T> class myclass { ... };
template <>
class mycontainer <char> {
    char elem;
    public:
    mycontainer (char arg) { elem=arg; }
    char uppercase () {
        if ((elem>=97)&&(elem<=122)) {
            elem-=32; // subtract 32 from the ASCII value of the char
            return elem; }
    }
};
/*
More on the class template specialisation syntax:
First of all, notice that we precede the class name with template>?, including an empty parameter list. This is because all types
are known and no template arguments are required for this specialisation, but still, it is the specialisation of a class template,
and thus it requires to be noted as such.
But more important than this prefix, is the <...> (e.g. <char>) specilisation parameter after the class template name. This
specialisation parameter itself identifies the type for which the template class is being specialised (here, char).
When we declare specialisations for a template class, we must also define all its members, even those identical to the generic
template class, becuase there is no "inheritance" of members from the generic template to the specialisation.
*/

int main () {

    /*
    The class T defined above serves to store 2 elements of any valid type. For example, if we wanted to declare an object of
    this class to store two integer values of type int with values 115 & 36, we would write:
    */
    mypair<int> myobj (115,36);
    cout << myobj.getmax() << "\n";


    // demonstration of template specialisation
    char thechar[] = "j";
    mycontainer<int> myint (7); // invokes class template
    mycontainer<char> mychar (thechar[0]); // invokes specialised class template (for char)
    // NB thechar is a char*, thechar[0] is a char (i.e. a char[1])
    cout << myint.increase() << endl;
    cout << mychar.uppercase() << endl;

    return 0;
}
