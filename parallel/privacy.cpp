/*
When threads are forked from the master thread at the beginning of a parallel region, they
all have access to what has been computed so far (this is their "shared data"). Of course,
the threads are not identical, otherwise parallelism would be pointless. Thus, each thread
has PRIVATE DATA, and know their own thread number, which identifies the thread.

In declaring a parallel region of code by a sentinel, after the directive, we can specify
a number of CLAUSES. Some particularly useful CLAUSES are to explicitly specify which
data inherited by each thread from the master thread are PRIVATE, and which data are SHARED
*/

#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

// NB is a pure function
int get_loop_count() { return 5; }

int main() {

    int i, x=10, y=0, z=10000;
    string b = "quack";
    string a = "honk";

    /*
    Here, we explicitly specify that i is PRIVATE (each thread has their own copy of it) and
    that b is SHARED (each thread accesses the same variable).
    By default, all variables are shared between the different threads, except those that are
    declared within the parallel block itself.
    Note that a PRIVATE copy is an *uninitialised* variable by the same name and type as the
    original variable, it does NOT copy the value of the variable that was in the surrounding
    context. That is, in general, at the entrance of a parallel block, a private variable becomes
    a new instance of the type, that is initialised with the default constructor (not the copy
    constructor) For primitive datatypes, the private variable is simply uninitialised.
    Note also the use of the "num_threads" CLAUSE, used to specify the exact number of threads
    to be forked from the master thread (overrides the environment variable / 
    omp_set_num_threads() function).
    */
    #pragma omp parallel for private(i,a,z) shared(b,x,y) num_threads(2)
    for (i=0;i<10;i++) {
    /* recall: a is private so is initially a new instance of string (i.e. empty).
       z is a private primitive variable so is initially unitialised */
        z = 6;
    /* The "atomic" CLAUSE specifies a single statement (not a block) that must happen completely
       or does not happen at all; no other thread can intervene during the execution of
       the statement. For example, the "atomic" clause is very useful for updating counters and
       other simple variables that are accessed by multiple threads simultaneously. */
        #pragma omp atomic
        y++;
        #pragma omp atomic
        x += y;

        b += " tweet";
        a += " tweet";
        if (i==9) {
            /* a is private, so was initialised as an empty string in the parallel region, hence
               there is no "honk" at the beginning of the string. Also, there are only 5 tweets,
               since each of the two threads adds "tweet" to its own private value for a, in a
               loop of 10 total */
            cout << "At iteration #10 a is: " << a << endl; }
    }

    /* we are in the master thread again. Because a&z were private in each of the forked threads,
       the values of a&z is the original value before forking. Because b&x&y were shared, their values
       are the result of the operations of all of the forked threads.
       Therefore:
           Note that we forked the loop of 10 into two threads, so the value of x is:
               10 + 2*(1+2+3+4+5) = 40
           The value of y was shared and incremented along all the threads, so is 10
           z is its original value declared in the serial region (=10000, not 6), as is a (="honk")
           whereas b was shared so has been modified, and retains its original "quack" declared in the
           beginning serial region (b="quack tweet tweet..."). Note that because the increment for b was
           not done in an atomic region, it doesn't have exactly 10 "tweets" due to multiple threads
           trying to access and increment the same value simultaneously */
    cout << "a is: " << a << endl;
    cout << "b is: " << b << endl;
    cout << "x is: " << x << " y is: " << y << " z is: " << z << endl;

    /* If you actually need a *copy* of the original value, then use the "firstprivate" clause.
       Another useful clause is the "default" clause, used to check whether you have remembered
       to assign all the variables used in the parallel region as either private or shared.
       We can use "default(none)" to specify that no variables can be used in the parallel region
       which have not been explicitly stated as being private or shared.
       We can also use "default(shared)" to make all variables shared by default. */
    #pragma omp parallel default(shared) firstprivate(y) num_threads(2)
    {
    // a += "squawk"; // won't compile if we include this, we haven't stated private/shared status of a
    y += 5;
    cout << "Add 5 to the copied value of y, is now: " << y << endl;
    }
    cout << "But back in the serial region, the master thread says y is back to: " << y << endl;

    /* The "lastprivate" clause defines a variable that is private, but causes the value from the
       last task to be copied back to the original value after the end of the loop/sections construct.
       In a loop (i.e. for) construct, the last value is the value assigned by the thread that handles
       the last iteration of the loop. Values assigned during other iterations are ignored.
       In a "sections" construct, the last value is the value assigned in the last section denoted
       by the "section" construct. Values assigned in other sections are ignored.
       Be careful when using "lastprivate": it cannot be used to e.g. fetch the value of a flag
       (set as a lastprivate var) assigned in an if statement of a parallel for loop ("reduction"
       must be used for this purpose).
       One valid use of lastprivate is as follows (getting a loop iteration no.) */
    int j=0;
    #pragma omp parallel for lastprivate(j)
    for(j=0;j<get_loop_count();j++) {}

    cout << "Number of loop iterations: " << j << endl;

    return 0;
}
