/* C++ example usage of std::vector and std::array container types:
   these are generally considered superior to C++ arrays */

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include<algorithm>

using namespace std;

typedef std::vector<double> dbl_vec; // can use a TYPEDEF statement to avoid tediously repeating in all declarations

// std::vector containers holding elems of type double cannot be converted directly in the declaration in the same way as for
// std::vector<int>. This template + function overcomes that, and in general can be used to construct a vector from a C++
// static array.
template< typename T, size_t N >
std::vector<T> makeVector( const T (&data)[N] )
{
    return std::vector<T>(data, data+N);
}

void print_int_vec(const std::vector<int>& vec) {

    for (auto x: vec) { // can do loops + access elems using an iterator
        std::cout << " " << x; }
    std::cout << "\n";
}

// Note that in passing std::array to a function, we have to specify the size (unlike vec)
void print_2d_dbl_arr(const std::array<std::array<double, 3>, 2>& arr) {

    for (int i=0;i<2;i++) {
        for (int j=0;j<3;j++) {
        std::cout << " " << arr[i][j]; }
        }
    std::cout << "\n";
}

void print_1d_str_arr(const std::array<std::string, 2> arr) {

    for (const auto& x: arr) {
        std::cout << " " << x; }
    std::cout << "\n";
}


int main () {

    // DECLARATIONS AND QUEUING OPERATIONS ETC. OF std::vector
    std::vector<int> vec1 = {1,3,4,5}; // declaration of a std::vector containing integers
    // alternative declaration statement using a static array
    const double values[] = { 2.0, 1.0, 42.0, -7 };
    std::vector<double> vec_dble1 = makeVector(values);
    // or, using our typedef
    dbl_vec vec_dble2 = makeVector(values);

    /* The storage of a std::vector is handled automatically, being expanded and contracted as needed. This means
       that this container type occupies more space than static arrays, since more memory is allocated to handle
       future growth, but allows useful operations such as insertion or removal of elems.
       Access to std::vector elems can be handled via the ITERATOR member type of the std::vector container type. */
    auto it = vec1.begin(); // get the iterator for vec1 as starting at the first elem
    // Note that we can also get the reverse iterators using rbegin() & rend()
    it = vec1.insert(it,0); // the iterator is now at the beginning having inserted a zero at the front of vec1
    vec1.insert(it+2,2); // insert a 2 at the second 3rd position (since it is currently at the 1st position)
    vec1.push_back(6); // push 6 at the back of vec1
    vec1.push_back(7);
    vec1.pop_back(); // pop the 7 at the back of vec1
    it = vec1.end(); // iterator is now at the end of vec1
    const int c = 9;
    std::vector<int> vec2(3,c); // alternative declaration of a std::vector, specifying size and repeating elem
    std::vector<int> vec3(10); // can zero-initialise a vector of given size
    // an arcane way of assigning elements is to use a loop with iterators
    for (std::vector<int>::iterator it_init = vec3.begin(); it_init != vec3.end(); ++it_init) {
        *it_init = c; }
    /* add elems of the std::vector vec2 to vec1, starting from the current position in vec1 corresponding to iterator it.
       elems of vec2 are added from input_iterator_first to input_iterator_second (here, beginning to end): */
    vec1.insert(it, vec2.begin(), vec2.end());
    int arr[] = { 10, 11, 12 };
    vec1.insert(vec1.end(), arr, arr+3); // insert elems from a static array
    vec1.insert(vec1.end(), 5, 13); // insert repeats of a given elem
    /* can erase elements at a given position (or range of positions, if a second argument is provided) using iterator arg(s)
       to the ERASE() member function... */
    vec1.erase(vec1.end()-3,vec1.end()-1);
    /* dereference the iterator to get the corresponding element, e.g. removing a specified element: */
    for (auto it1 = vec1.begin(); it1 != vec1.end(); ) {
        if (*it1 == 3) {
            it1 = vec1.erase(it1);
        } else {
            ++it1;
        }
    }
    // vector::assign()

    print_int_vec(vec1);

    // ACCESSING ELEMENTS ETC.
    // access element at specified position in container using member function at()
    std::cout << "5th elem of vec1: " << vec1.at(4) << "\n";
    // use front() and back() to access first & last elems
    std::cout << "First elem of vec1: " << vec1.front() << " " << \
                 "Last elem of vec1: " << vec1.back() << "\n";
    // the std::vector container also allows a reference to the element at specified position using the [] operator syntax.
    // however, unlike at(), this operation does *not* throw an exception if the position is out of range (instead get
    // undefined behaviour)
    std::cout << "6th elem of vec1: " << vec1[5] << "\n";

    // STORAGE & MEMORY OPERATIONS ETC.
    std::cout << "Size of vec1: " << vec1.size() << "\n";
    vec3.clear(); // clear the contents of vec3
    std::cout << "vec3 is empty? " << vec3.empty() << "\n";
    // change the number of elements stored (if decreased to below the previous vector size, additional elems are simply discarded.
    // If increased to above the previous vector size, additional elems are initialised to zero, or else to the value provided as
    // an optional second argument).
    vec1.resize(20,14);
    // find max no of elems the container is able to hold
    std::cout << "Maximum size of vec1: " << vec1.max_size() << "\n";
    vec1.shrink_to_fit(); // request removal of unused capacity
    // increase the capacity of a vector to a value greater than or equal to a new specified capacity. Note that this invalidates
    // all active iterators
    vec1.reserve(25);
    std::cout << "No of elems of vec1 that can be held in currently allocated storage: " << vec1.capacity() << "\n\n\n";


    // std::array works in much the same way as std::vector, and has many of the same member functions, for instance:
    // ELEMENT ACCESS: AT, OPERATOR[], SWAP
    // ITERATORS: FRONT, BACK, BEGIN, END, RBEGIN, REND
    // CAPACITY: EMPTY, SIZE, MAX_SIZE
    // Note that because a multidimensional std::array is essentially nested 1d std::array s, iterators work slightly less
    // straightforwardly than for the 1D case
    // DECLARING A std::array CONTAINER
    // Note that multidimensional std::vector containers can be declared in the same way, but this is inadvisable because of
    // storage overhead and the allocated memory being non-contiguous
    std::array<std::array<double, 3>, 2> arr1{{ { 1., 2., 3. }, {4., 5., 6.} }}; // note extra curly braces required
    std::array<std::string, 2> arr2 = { "b", "a" }; // note that with the "=" sign we don't need the extra pair of curly braces

    // fill a std::array container (that was initialied with no specified value) with a specified value
    std::array<int,6> arr3;
    arr3.fill(5);
    // extract the ith element from an array with std::get()
    std::get<1>(arr3) = 4;
    // the algorithm::sort() function is used to sort the elements of a std::array in ascending order. Takes (first, last)
    // iterators as its args
    std::sort(arr3.begin(),arr3.end());
    // printing
    for (int& elem : arr3) { std::cout << " " << elem; }
    std::cout << "\n\n";


    print_2d_dbl_arr(arr1);
    print_1d_str_arr(arr2);

    // POINTERS WITH std::vector & std::array CONTAINERS
    /* Unlike a C-style array, the data member T that is the sole non-static member of the std::array container does NOT decay to
       T* automatically.
       It is generally inadvisable to use pointers to these container types, e.g. because you lose size information. Doing this
       often defeats the point of using a std::array in the first place!
       That said, the data() member function of std::array & std::vector container types allows direct access to the underlying
       array by returning a pointer to the underlying element storage. For non-empty containres, the returned pointer compares
       equal to the address of the first element. Now we have a raw C-like array pointer to the underlying static array, and can
       effectively use the std::array as if it were a C-like static array. */
    int* arrptr = arr3.data();
    std::cout << "2nd elem of arr3: " << *(arrptr+1) << "\nand its address: " << (&arrptr+1) << "\n";


    return 0;
}
