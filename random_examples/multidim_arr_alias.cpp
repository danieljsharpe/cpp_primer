/* C++ code demonstrating use of template alias for concise declarations
   of multidimensional std::array containers
   Note: methods like std::array::size() will not return the correct value,
   and methods like std::array::fill() will not work at all */

#include <array>
#include <assert.h>
using namespace std;

template <typename T, size_t d1, size_t d2, size_t... ds>
struct GetMultiDimArray
{
    using type = std::array<typename GetMultiDimArray<T, d2, ds...>::type, d1>;
};

template <typename T, size_t d1, size_t d2>
struct GetMultiDimArray<T, d1, d2>
{
    using type = std::array<std::array<T, d2>, d1>;
};

template <typename T, size_t d1, size_t d2, size_t... ds>
using MultiDimArray = typename GetMultiDimArray<T, d1, d2, ds...>::type;

int main () {

    MultiDimArray<int, 3, 2> arr {1, 2, 3, 4, 5, 6};
    assert(arr[1][1] == 4);

    return 1;
}
