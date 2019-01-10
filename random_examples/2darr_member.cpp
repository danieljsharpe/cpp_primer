/*
2D array of unknown size as a class variable
*/

#include <iostream>
using namespace std;

class Matrice
{
private:
    int** mMatr; // pointer to pointer
    int m, n;
public:
    Matrice(const int m1, const int n1)
    {
        m = m1;
        n = n1;
        mMatr = new int*[m]; 
        for (int i = 0; i < m; i++) {
            mMatr[i] = new int[n];
            for (int j = 0; j < n; j++) {
                mMatr[i][j] = j + (i*n); }
        }
    }

    ~Matrice()
    {
        for (int i = 0; i < m; i++) {
            delete [] mMatr[i]; }
        delete [] mMatr;
    }

    void print_elems()
    {
        // note that mMatr has the proper scope - we can access it from here!
        cout << "Printing elems:\n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << mMatr[i][j] << "\n"; }
        }
        cout << "\n";
    }
};


int main() {

    Matrice mtx1(3,2);
    mtx1.print_elems();

    return 0;
}
