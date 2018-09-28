/* Using std::copy to copy a 2d array */

#include <iostream>
using namespace std;

int main () {

    const int rows = 3;
    const int columns = 3;
    int myint[rows][columns]={{1,2,3},{4,5,6},{7,8,9}};
    int favint[rows][columns];
    std::copy(&myint[0][0], &myint[0][0]+rows*columns,&favint[0][0]);

    int i;
    for (i=0;i<3;i++) {
        std::cout << favint[i][0] << " " << favint[i][1] << " " << favint[i][2] << "\n"; }

    return 0;
}
