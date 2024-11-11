#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>
#include "Node.h"
#include <vector>

class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void append(const std::string& data);
    void sort();
    void displayInRange(const std::string& startIP, const std::string& endIP);
    void saveToFile(const std::string& filename, const std::string& startIP, const std::string& endIP);

private:
    Node* head;
    Node* tail;

    bool compareIPs(const std::string& ip1, const std::string& ip2, int only_ip);
    Node* findStartNode(const std::string& startIP);
    std::vector<std::string> split(const std::string& s);
    Node* split(Node* head);
    Node* merge(Node* first, Node* second);
    Node* mergeSort(Node* node);
};

#endif // DOUBLYLINKEDLIST_H
