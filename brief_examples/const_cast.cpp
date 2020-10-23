/* const-casting in C++ (NB not recommended - if you need to use const-casting,
   then rethink your design!

   Example:
   Network *ktnptr = &const_cast<Network&>(ktn)
*/

BoxT<T> * nonConstObj = const_cast<BoxT<T> *>(constObj);

const int a = 3;
int& b = const_cast<int&>(a);

const Node *tmpnodeptr=*it_set;
epsilon = const_cast<Node*>(tmpnodeptr);
