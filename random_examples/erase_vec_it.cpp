/* erase elements of a vector that meet a condition, while you are iterating over the vector in a loop */

#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

int main () {

    vector<int> vec { 3, 8, 13, 16, 2, 5, 17, 4, 11, 12 };
    vector<int>::iterator it_vec = vec.begin();
    int thresh=10;

    cout << "initial vector:" << endl;
    for (auto elem: vec) { cout << "  " << elem; }
    cout << endl;

    while (it_vec!=vec.end()) {
        if (*it_vec < thresh) {
            it_vec = vec.erase(it_vec); // erase() deletes the element and returns an iterator to the next pos
                                        // Warning - very slow! (O(n^2), very bad for large vectors)
        }
        else { it_vec++; }
    }

    cout << "final vector:" << endl;
    for (auto elem: vec) { cout << "  " << elem; }
    cout << endl;

    return 0;
}
