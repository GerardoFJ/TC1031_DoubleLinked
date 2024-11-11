#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    std::string data;
    Node* prev;
    Node* next;

    Node(const std::string& data);
};

#endif // NODE_H
