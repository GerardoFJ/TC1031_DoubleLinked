#ifndef NODE_H
#define NODE_H

#include <string>

// Declaration of the Node class, representing a node in a doubly linked list
class Node {
public:
    std::string data;    // Public member to store the data of the node, using std::string
    Node* prev;          // Pointer to the previous node in the list (nullptr if it's the first node)
    Node* next;          // Pointer to the next node in the list (nullptr if it's the last node)

    // Constructor that initializes a Node with a given data string
    Node(const std::string& data);
};

#endif