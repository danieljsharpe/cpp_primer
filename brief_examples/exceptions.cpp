/* Brief C++ code to illustrate the use of throwing and catching exceptions */

#include <iostream>
#include <exception>
using namespace std;


int main () {

    bool daniel_handsome, daniel_clever;

    daniel_handsome = false;
    daniel_clever = false;

    for (int i=0;i<3;i++) { // NB After an exception has been handled, exception resumes after the TRY-CATCH block, not after the
                        // original THROW statement!
    try {
        if (not daniel_handsome) {
            std::cout << "Manually throwing error with identifier 10\n";
            throw 10;}
        if (not daniel_clever) {
            std::cout << "Manually throwing error with identifier ur_wrong\n";
            throw "ur_wrong"; }
    std::cout << "Manually throwing error with identifier 3.\n";
    throw 3.;
    }
    /* The exception handler function for a specific TRY block appears immediately after that block. Such functions take a single
       argument. Exceptions are identified by their type. Handler functions taking different types as their argument can be
       chained after a try block. A thrown exception is caught only by the matching handler (if such a handler exists). A handler
       taking an ellipsis as its argument will catch any exception of any type - it can be used to catch all exceptions not
       caught by other handlers. */
    catch (int e) { // an exception handler function
        std::cout << "Exception identifier " << e << " caught\n";
        daniel_handsome = true;
    }
    catch (const char * e) {
        std::cout << "Exception identifier " << e << " caught\n";
        daniel_clever = true;
    }
    catch (...) {
        std::cout << "Default exception being handled by the default handler\n";
    }
    }
    std::cout << "Daniel is handsome?\t" << daniel_handsome << "\n";
    std::cout << "Daniel is clever?\t" << daniel_clever << "\n";

    // STANDARD EXCEPTIONS
    /* The c++ standard library provides a base class specifically designed to declare objects to be
       thrown as exceptions. This class has a virtual member function called WHAT that returns a
       null-terminated character sequence (of type char *) and that can be overwritten in derived
       classes to contain some sort of description of the exception */

    class myexception: public exception
    {
        virtual const char* what() const throw()
        {
            return "A description of my exception";
        }
    } myexc;

    try {
        throw myexc; }
    catch (exception& exc) {
        std::cout << exc.what() << "\n";
    }
    /* Note that we have placed a handler that catches exception objects by reference
       (notice the "&" after the type declaration of the argument to the handler)
       therefore this handler also catches classes derived from exception, like the myexc
       object of type myexception*/

    /* Components of the c++ standard library throw exceptions that are derived from the
       exceptions class of <exceptions>. There are six:
       BAD_ALLOC, BAD_CAST, BAD_EXCEPTION, BAD_TYPEID, BAD_FUNCTION_CALL, BAD_WEAK_PTR
       in addition to two generic exception types that can be inherited by custom
       exceptions to report errors:
       LOGIC_ERROR, RUNTIME_ERROR
       These standard exceptions can be checked and accounted for by handler functions
       taking objects of the exception base class as their argument, or the argument may
       be the derived class, and are important e.g. in checking for memory allocation */

    try {
        int* myarray = new int[1000000000000000000]; // far too big! (throws a bad_alloc)
    }
    catch (std::bad_alloc & ba) {
        std::cout << "Caught a bad_alloc exception: " << ba.what() << "\n";
    }
    catch (exception& e) {
        std::cout << "Caught a standard exception: " << e.what() << "\n";
    }

    return 1;
}
