/*
Fork-join in a fundamental paradigm in parallel computing. Computations create opportunities for parallelism
by branching at certain points that are specified by annotations in the program text.
Each branching point FORKS the control flow of the computation into two or more logical threads. When control
reaches the branching point, the branches start running. When all branches complete, the control JOINS back
to unify the flows from the branches.
Results computed by the branches are typically read from memory and merged at the JOIN point. Parallel regions
can fork and join recursively in the same manner that divide and conquer programs split and joinr recursively.
In this sense, fork-join is the "divide and conquer" of parallel computing.

Here we use the OpenMP library to write a very simple PARALLEL FOR loop, showcasing some basic features of OpenMP.

Compile with:
g++ -std=c++11 -o fork_join fork_join.cpp -fopenmp
*/

#include <iostream>
#include <vector>
#include <omp.h> // OpenMP library for parallel computing

using namespace std;

int main () {

    // get the maximum number of threads availabe
    // NB this can be set as an environment variable as follows:
    // export OMP_NUM_THREADS=<no. of threads to use>
    const int max_no_threads = omp_get_max_threads();

    omp_set_num_threads(max_no_threads); // set the number of processors to run on

    cout << "I am going to run on " << max_no_threads << " threads" << endl;

    // we are going to use this vector to count the number of times we have seen a thread in the parallel for loop
    vector<int> thread_count(max_no_threads);

    /*
    In C++, declaring sections of the code to be ran in parallel is achieved through DIRECTIVES,
    via the PRAGMA mechanism. A PRAGMA is an annotation for the benefit of the compiler, that is
    otherwise not part of the language.
    Let us illustrate this with an example; a PARALLEL FOR loop.
    Here: - "#pragma omp" is a SENTINEL to indicate to the compiler that an OpenMP directive is to follow
          - "parallel for" is the directive
          - we have ommitted the subsequent (optional) clauses with values
    */
    #pragma omp parallel
    {
        /* At this point, we have forked and are running in parallel. If there are no curly braces,
           then the line immediately following the "#pragma omp..." line is ran in parallel.
           Otherwise, the content of the braces is ran in parallel.
           This block of code will be run by multiple threads */
        if (omp_get_thread_num()==0) {
            cout << "This is thread no. " << omp_get_thread_num() << " speaking. We are running a total of " \
                 << omp_get_num_threads() << " threads" << endl;
        }
    }
    #pragma omp parallel
    {
        // this for loop is, since it is directly after a pragma sentinel, ran in parallel!
        #pragma omp for
        for (int i=0;i<3*max_no_threads;i++) {
            // every thread should appear three times
            cout << "I'm doing a parallel for loop! Thread no.: " << omp_get_thread_num() << endl;
            thread_count[omp_get_thread_num()]++; // increment the counter, we have seen this thread
        }
    }

    cout << "\nNumber of times we saw each thread in the parallel for loop:" << endl;
    int i=0;
    for (auto count: thread_count) {
        cout << "thread no.: " << i << " count: " << count << endl;
        i++;
    }

    /* Outside of the curly braces associated with the "#pragma omp" sentinel, the branches that
       were forked have joined, and we are running in serial again (so no. of threads should be 1) */
    cout << "Now running on " << omp_get_num_threads() << " threads (serial)" << endl;

    vector<int> thread_count2(max_no_threads);

    // We can use the "parallel for" directive to run a parallel for loop more concisely. 
    #pragma omp parallel for
    for (int i=0;i<3*max_no_threads;i++) {
        thread_count2[omp_get_thread_num()]++;
    }

    cout << "\nNumber of times we saw each thread in the second parallel for loop:" << endl;
    i=0;
    for (auto count: thread_count2) {
        cout << "thread no.: " << i << " count: " << count << endl;
        i++;
    }

    return 0;
}
