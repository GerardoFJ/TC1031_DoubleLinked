#include "Node.h"

// Constructor for the Node class that initializes a node with given data
Node::Node(const std::string& data) : data(data), prev(nullptr), next(nullptr) {}
