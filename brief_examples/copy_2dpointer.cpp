/* Using std::copy to copy a 2d array via pointers */

#include <iostream>
using namespace std;

int main () {

    // ONE DIMENSIONAL CASE
    std::cout << "Example: 1D array\n\n";

    const int cols = 3;
    const int rows = 4;
    double * foo = new double[cols];
    double * bar = new double[cols];
    double * baz = new double[cols];

    int i, j;
    for (i=0;i<cols;i++) {
        *(foo+i) = double(i); }

    std::copy(foo,foo+cols,bar);
    for (i=0;i<cols;i++) {
        std::cout << *(bar+i) << " "; }
    std::cout << "\n\n";

    // alternative
    std::copy(&foo[0],&foo[0]+cols,&baz[0]);
    for (i=0;i<cols;i++) {
        std::cout << baz[i] << " "; }
    std::cout << "\n\n";

    delete [] foo;
    delete [] bar;
    delete [] baz;


    // TWO DIMENSIONAL CASE
    std::cout << "Example: 2D array\n\n";

    double (*ham)[cols] = new double[rows][cols]; // only works if cols is const
    double (*spam)[cols] = new double[rows][cols]; 

    for (i=0;i<rows;i++) {
        for (j=0;j<cols;j++) {
            ham[i][j] = double(j) + (double(cols)*double(i));
        }
    }

    std::copy(&ham[0][0],&ham[0][0]+(rows*cols),&spam[0][0]);
    for (i=0;i<rows;i++) {
        for (j=0;j<cols;j++) {
            std::cout << spam[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    delete [] ham;
    delete [] spam;

    // Note: the same std::copy syntax as above, for the 1D and 2D array case, can be used
    // for the case of arrays declared as arrays (and not as pointers to arrays)

    /* The above strictly deals with pointers to a 2D array. It is the correct way to create
       a double[rows][cols] array and where all the memory is contiguous. If cols is not
       a const, then our only other option is to create a dynamic 2D array that is essentially
       an array of pointers to (1D) arrays. Note that this is more expensive in memory, and
       more complicated to cleanup, because a memory block is allocated to each row (i.e.
       memory is *not* contiguous. */
    std::cout << "Example: '2D array' (non-contiguous)\n";

    double ** eggs = new double*[rows];
    for (i=0;i<rows;i++) {
        eggs[i] = new double[cols]; }

    for (i=0;i<rows;i++) {
        std::copy(ham[i],ham[i]+cols,eggs[i]); }

    for (i=0;i<rows;i++) {
        for (j=0;j<cols;j++) {
            std::cout << eggs[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    for (i=0;i<rows;i++) {
        delete [] eggs[i]; }
    delete [] eggs;

    return 0;
}
