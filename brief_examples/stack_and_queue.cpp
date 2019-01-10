/*
C++ custom implementation of Stack and Queue (Linked List based) data structures
Note that the Standard Template Library (STL) provides std::stack and std::queue templated classes
*/

#include <iostream>
using namespace std;

// struct for an entry in the linked list-derived data structures
struct Node {

    int id;
    string stringvar;
    Node *next_node;
};

// linked list data structure
class List {

    public:

    int n_entries = 0;
    Node *head = NULL;
    Node *tail = NULL;

    List() {}
    ~List() {}

    List(const List& rhs) {
        head = rhs.head; tail = rhs.tail;
        n_entries = rhs.n_entries; }

    List& operator=(const List& rhs) {
        head = rhs.head; tail = rhs.tail;
        n_entries = rhs.n_entries; }

    // for both Stack and Queue, Nodes are inserted at the tail end of the List
    void insertnode(int id, string stringvar) {
        Node *temp_node = new Node;
        temp_node->id = id;
        temp_node->stringvar = stringvar;
        temp_node->next_node = NULL;
        if (head==NULL) { // inserting first node in linked list
            head = temp_node;
            tail = temp_node;
        } else { // inserting another node in existing linked list, at tail 
            tail->next_node = temp_node;
            tail = temp_node; }
        temp_node = NULL;
        delete temp_node;
        n_entries++; }

    // insert Node at the head end rather than at the tail end
    void insertnode_athead(int id, string stringvar) {
        Node *temp_node = new Node;
        temp_node->id = id;
        temp_node->stringvar = stringvar;
        if (head==NULL) { // inserting first node in linked list
            head = temp_node;
            tail = temp_node;
        } else { // inserting another node in existing linked list, at head
            temp_node->next_node = head;
            head = temp_node; }
        temp_node = NULL;
        delete temp_node;
        n_entries++; }
};

// stack (LIFO) data structure based on linked list
/* NB Stack has no member variables, so there is nothing to do in the copy constructor or copy assignment operator to initialise
      Stack's members from the "right hand side" (rhs) object in a copy or assignment operation. However, one must ensure that
      the base class List has the opportunity to initialise its members. */
class Stack : public List {

    public:

    Stack() {}
    ~Stack() {}

    Stack(const Stack& rhs) : List(rhs) {} // call copy constructor of List base class

    Stack& operator=(const Stack& rhs) {
        List::operator=(rhs); // call copy constructor of List base class
        return *this; }

    int top() {
        if (head == NULL) {
            throw runtime_error("error in top(): the Stack is empty");
        } else {
            return head->id;
        }
    }

    // push a Node to the tail end
    void push(int id, string stringvar) {
        insertnode(id, stringvar);
    }

    // pop the tail Node
    Node *pop() {
        if (head == NULL) {
            throw runtime_error("error in pop(): the Stack is empty");
        } else {
            Node *current_node = new Node;
            Node *prev_node = new Node;
            current_node = head;
            while (current_node->next_node != NULL) {
                prev_node = current_node;
                current_node = current_node->next_node; }
            tail = prev_node;
            prev_node->next_node = NULL;
            if (current_node==head) { // popping the last node, reset head and tail Nodes to NULL
                head = NULL;
                tail = NULL; }
            prev_node = NULL;
            delete prev_node;
            n_entries--;
            return current_node;
        }
    }

    // return a copy of the tail Node
    void peek() {

    }
};

// queue (FIFO) data structure based on linked list
class Queue : public List {

    public:

    Queue() {}
    Queue(const Queue& rhs) : List(rhs) {}
    Queue& operator=(const Queue& rhs) {
        List::operator=(rhs);
        return *this; }
    ~Queue() {}

    // enqueue a Node at the tail end
    void enqueue(int id, string stringvar) {
        insertnode(id, stringvar);
    }

    // dequeue the head Node
    Node *dequeue() {
        if (head == NULL) {
            throw runtime_error("error in dequeue(): the Queue is empty");
        } else {
            Node *temp_node = new Node;
            temp_node = head;
            head = head->next_node;
            return temp_node;
        }
    }

};

int main () {

    // test implementation of Stack
    Stack stack1;
    stack1.push(1,"quack");
    stack1.push(2,"honk");
    stack1.push(3,"squawk");

    Stack stack2 = stack1; // calls copy constructor of Stack

    Stack stack3;
    stack3 = stack2; // calls operator= of Stack

    cout << "\nTESTING STACK IMPLEMENTATION:" << endl;
    Node* popped_node;
    while (stack3.head != NULL) {
        popped_node = stack3.pop();
        cout << popped_node->id << "  " << popped_node->stringvar << endl;
        if ((stack3.head != NULL)&&(stack3.tail != NULL)) {
            cout << " new head: " << stack3.head->id << "  " << stack3.head->stringvar \
                 << "\tnew tail: " << stack3.tail->id << "  " << stack3.tail->stringvar << endl; }
        delete popped_node;
    }


    // test implementation of Queue
    Queue queue1;
    queue1.enqueue(1,"quack");
    queue1.enqueue(2,"honk");
    queue1.enqueue(3,"squawk");

    cout << "\nTESTING QUEUE IMPLEMENTATION: " << endl;
    Node* deqd_node;
    while (queue1.head != NULL) {
        deqd_node = queue1.dequeue();
        cout << deqd_node->id << "  " << deqd_node->stringvar << endl;
        if ((queue1.head != NULL)&&(queue1.tail != NULL)) {
            cout << " new head: " << queue1.head->id << "  " << queue1.head->stringvar \
                 << "\tnew tail: " << queue1.tail->id << "  " << queue1.tail->stringvar << endl; }
    }

    return 0;
}
