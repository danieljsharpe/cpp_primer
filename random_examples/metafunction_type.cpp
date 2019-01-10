/* C++ code using metafunction to define a type, e.g. for less verbose
   declaration of a 2D std::array.
   This is a robust alternative to template aliases, when that method is
   not supported by the compiler */

#include <iostream>
#include <array>

using namespace std;

template<class T, std::size_t RowsN, std::size_t ColumnsN>
struct Matrix
{
    typedef std::array<std::array<T, ColumnsN>, RowsN> type; // row major

private:
    Matrix(); // prevent accidental construction of the metafunction itself
};

int main()
{
    Matrix<int, 3, 4>::type matrix;
}
