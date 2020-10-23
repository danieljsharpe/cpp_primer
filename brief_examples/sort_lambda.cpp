/*
Using a lambda function to sort a vector in C++
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {

    vector<pair<int,int>> myvec = {make_pair(7,5),make_pair(1,8),make_pair(6,4),make_pair(9,1)};

    // sort according to second members of pairs, in ascending order
    sort(myvec.begin(),myvec.end(),[](pair<int,int> pair1, pair<int,int> pair2) { return (pair1.second < pair2.second); });

    for (const auto& elem: myvec) {
        cout << "   first: " << elem.first << "  second: " << elem.second << endl; }

    return 0;
}
