/* C++ script to demonstrate overloading of operators */

#include <iostream>
using namespace std;

/*
Classes essentially define new types to be used in C++ code. And types in C++ not only interact with code by means of
constructions and assignments, but also by means of operators. e.g. the addition operator "+" is a defined operation on
variables of fundamental types int, double etc. For other types, including derived types (classes), the meaning of operations
such as "+" may be ambiguous or undefined, e.g. a type myclass derived by the user has no defined behaviour for additions
if not explicitly provided by OPERATOR OVERLOADING (essentially overriding/defining the behaviour of an operator for a
custom type).

C++ allows most operators to be overloaded so that their behaviour can be defined for just about any type, including classes.
Here is a list of all the operators that can be overloaded:
+    -    *    /    =    <    >    +=   -=   *=   /=   <<   >>
<<=  >>=  ==   !=   <=   >=   ++   --   %    &    ^    !    |
~    &=   ^=   |=   &&   ||   %=   []   ()   ,    ->*  ->   new 
delete    new[]     delete[]

Operators are overloaded by means of operator functions, which are regular functions with special names: their name begins with
the OPERATOR keyword followed by the operator sign (e.g. "+") to be overloaded. Syntax:
type operator sign (parameters) { ... }

Consider the following example, where a class CVector is defined to be a Cartesian vector containing 2 elems, and the addition
operator ("+") is overloaded for this class to perform the addition of two Cartesian vectors (which is element-wise addition):
*/

class CVector {
    public:
    int x,y;
    CVector () {};
    CVector (int a,int b) : x(a), y(b) {} // constructor
    CVector operator+ (const CVector&); // overloaded "+" operator. This function takes a CVector (the Cartesian vector to be added
                                        // to this vector) and returns a CVector (the result of the vector addition).
};

// "+" operator overloaded as a member function
CVector CVector::operator+ (const CVector& param) {
    CVector temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return temp;
}

// "-" operator overloaded as a non-member function
// note the syntax: the operator function takes an object of the peoper class as its first arg
CVector operator- (const CVector& lhs, const CVector& rhs) {
    CVector temp;
    temp.x = lhs.x - rhs.x;
    temp.y = lhs.y - rhs.y;
    return temp;
}

int main () {
    CVector foo (3,1);
    CVector bar (1,2);
    CVector result, result2, result3;
    result = foo + bar; // the overloaded "+" operator is called implicitly with this syntax
    result2 = foo.operator+ (bar); // the function if called explicitly with this syntax (equivalent to line above)
    cout << result.x << "," << result.y << "\n";
    result3 = foo - bar;
    cout << result3.x << "," << result3.y << "\n";

    return 0;
}

/*
Note that the parameter expected for a member function overload (when called implicitly) differs depending on the nature of the
operator. Common to all binary operators (such as "+") the parameter is naturally the operand to the RHS of the operator. A
different number or ordering of parameters is required for different types of operators, see the table below:

(in each case, replace "@" by the desired operator)
Expression  Operators                            Member func            Non-member func
@a          + - * & ! ~ ++ --                    A::operator@()         operator@(A)
a@          ++ --                                A::operator@(int)      operator@(A,int)
a@b         + - * / % ^ & | < > == != <= >=      A::operator@(B)        operator@(A,B)
            << >> && || = += -= *= /= %= ^=
            &= |= <<= >>= []
a(b,c...)   ()                                   A::operator()(B,C...)  -
a->b        ->                                   A::operator->()        -
(TYPE) a    TYPE                                 A::operator TYPE()     -

Note that not all operators can be overloaded as non-member functions.
*/
