/*
"reduction" is a special data sharing attribute clause that provides a safe way of joining work
from all threads after construct
*/

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {

    /* A simple first example:
       the "reduction" clause is a special directive that instructs the compiler to generate code
       that accumulates values from different loop iterations together in a certain manner.
       e.g. in the following, a represents a cumulative sum, so we want to add (+) the values from
       all loop iterations together */
    int a=0;
    vector<int> the_vec = {1,2,3,4,5};
    #pragma omp parallel for reduction(+:a)
    for (int i=0;i<the_vec.size();i++) a += the_vec[i];

    /* Note that here, a is NOT its original value, it retains its value from the parallel region
       because of the reduction clause, in spite of absence of the a "firstptrivate" clause */
    cout << "After cumulative sum, a is: " << a << endl;


    return 0;
}
