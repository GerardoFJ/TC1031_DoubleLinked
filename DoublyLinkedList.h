#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>
#include "Node.h"
#include <vector>

class DoublyLinkedList {
public:
    // Constructor for the DoublyLinkedList class, initializes the list to empty
    DoublyLinkedList();

    // Destructor to clean up the memory allocated for nodes in the linked list
    ~DoublyLinkedList();

    // Adds a new node with the given data to the end of the list
    void append(const std::string& data);

    // Sorts the list in ascending order based on IP addresses
    void sort();

    // Displays logs that fall within the specified IP range (startIP to endIP)
    void displayInRange(const std::string& startIP, const std::string& endIP);

    // Saves logs in the specified IP range to a file with the given filename
    void saveToFile(const std::string& filename, const std::string& startIP, const std::string& endIP);

private:
    Node* head;   // Pointer to the first node in the list (head)
    Node* tail;   // Pointer to the last node in the list (tail)

    // Helper function that compares two IP addresses, returns true if ip1 < ip2
    bool compareIPs(const std::string& ip1, const std::string& ip2, int only_ip);

    // Finds the starting node in the list that is at or after the specified startIP
    Node* findStartNode(const std::string& startIP);

    // Splits a string into parts based on delimiters (e.g., splitting an IP address into octets)
    std::vector<std::string> split(const std::string& s);

    // Splits the linked list into two halves and returns the second half
    Node* split(Node* head);

    // Merges two sorted halves of the linked list into one sorted list
    Node* merge(Node* first, Node* second);

    // Recursively sorts the linked list using merge sort
    Node* mergeSort(Node* node);
};

#endif // DOUBLYLINKEDLIST_H
