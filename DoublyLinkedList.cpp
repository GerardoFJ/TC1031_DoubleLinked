/*
    Act 1.3 - Comprehensive Activity of Basic Concepts and Fundamental Algorithms 
    Created by Ricardo Gaspar Ochoa, Gilberto Malagamba Montejo and Gerardo Fregoso Jimenez on 10/11/24.
    This code filters logs from a file based on IP addresses and saves them to another file.
*/
#include "DoublyLinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

// Constructor: Initializes an empty doubly linked list with no head or tail.
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Destructor: Deallocates all nodes in the list to prevent memory leaks.
DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        delete current;   // Delete the current node and move to the next node
        current = nextNode;
    }
}

// Appends a new node with the given data to the end of the doubly linked list.
void DoublyLinkedList::append(const std::string& data) {
    Node* newNode = new Node(data);  // Create a new node with the provided data
    if (!head) {
        head = tail = newNode;   // If the list is empty, set both head and tail to the new node
    } else {
        tail->next = newNode;    // Attach the new node to the end of the list
        newNode->prev = tail;    // Set the previous pointer of the new node to the old tail
        tail = newNode;          // Update the tail pointer to the new node
    }
}

// Splits a string into a vector of tokens based on spaces.
std::vector<std::string> split_str(const std::string& s) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    char delimiter = ' ';
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);  // Add each token (sub-string) to the vector
    }
    return tokens;
}

// Compares two IP addresses (or parts of them), used for sorting purposes.
bool DoublyLinkedList::compareIPs(const std::string& string1, const std::string& string2, int only_ip = 1) {
    std::string ip1 = string1;
    std::string ip2 = string2;

    // Extracts the last part of the IP addresses based on the "only_ip" parameter
    if (only_ip == 1) {
        std::vector<std::string> sorted_ip1 = split_str(string1);
        std::vector<std::string> sorted_ip2 = split_str(string2);
        ip1 = sorted_ip1[3];
        ip2 = sorted_ip2[3];
    }
    else if (only_ip == 2) {
        std::vector<std::string> sorted_ip1 = split_str(string1);
        ip1 = sorted_ip1[3];
    }
    else if (only_ip == 3) {
        std::vector<std::string> sorted_ip2 = split_str(string2);
        ip2 = sorted_ip2[3];
    }

    // Converts the string parts into integers and compares them lexicographically
    std::istringstream ipStream1(ip1), ipStream2(ip2);
    int a, b, c, d, e, f, g, h;
    ipStream1 >> a; ipStream1.ignore();
    ipStream1 >> b; ipStream1.ignore();
    ipStream1 >> c; ipStream1.ignore();
    ipStream1 >> d; ipStream1.ignore();
    ipStream2 >> e; ipStream2.ignore();
    ipStream2 >> f; ipStream2.ignore();
    ipStream2 >> g; ipStream2.ignore();
    ipStream2 >> h; ipStream2.ignore();

    // Lexicographical comparison of the IP components
    return std::tie(a, b, c, d) < std::tie(e, f, g, h);
}

// Merges two sorted sublists into one sorted list.
Node* DoublyLinkedList::merge(Node* first, Node* second) {
    if (!first) return second;   // If the first list is empty, return the second list
    if (!second) return first;   // If the second list is empty, return the first list

    // Recursively merge the two lists based on IP comparison
    if (compareIPs(first->data, second->data)) {
        first->next = merge(first->next, second);  // Merge the remaining part of the first list with the second list
        first->next->prev = first;  // Set the previous pointer of the new node to the current node
        first->prev = nullptr;      // Set the previous pointer of the current node to null
        return first;
    } else {
        second->next = merge(first, second->next);  // Merge the remaining part of the second list with the first list
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

// Splits the linked list into two halves (used for merge sort).
Node* DoublyLinkedList::split(Node* head) {
    Node* fast = head;
    Node* slow = head;
    while (fast->next && fast->next->next) {  // Move fast pointer two steps and slow pointer one step
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = nullptr;  // Split the list into two halves
    return temp;
}

// Recursively sorts the linked list using merge sort.
Node* DoublyLinkedList::mergeSort(Node* node) {
    if (!node || !node->next) return node;  // Base case: if the list is empty or has a single node, it's already sorted

    Node* second = split(node);  // Split the list into two halves

    node = mergeSort(node);      // Recursively sort the first half
    second = mergeSort(second);  // Recursively sort the second half

    return merge(node, second);  // Merge the two sorted halves
}

// Sorts the entire linked list using merge sort.
void DoublyLinkedList::sort() {
    head = mergeSort(head);  // Sort the list starting from the head

    // Update the tail pointer after sorting the list
    tail = head;
    while (tail && tail->next) {
        tail = tail->next;  // Traverse to the last node to update the tail
    }
}

// Finds the node that corresponds to or comes after the specified startIP.
Node* DoublyLinkedList::findStartNode(const std::string& startIP) {
    Node* current = head;
    while (current && compareIPs(current->data, startIP, 2)) {
        current = current->next;  // Move to the next node if the current node's IP is less than startIP
    }
    return current;
}

// Displays all logs in the range between the startIP and endIP (inclusive).
void DoublyLinkedList::displayInRange(const std::string& startIP, const std::string& endIP) {
    Node* current = findStartNode(startIP); 
    while (current && compareIPs(current->data, endIP, 2)) {
        std::cout << current->data << std::endl;  // Print the log
        current = current->next;  // Move to the next node
    }
}

// Saves the logs in the specified IP range to a file.
void DoublyLinkedList::saveToFile(const std::string& filename, const std::string& startIP, const std::string& endIP) {
    std::ofstream outFile(filename);
    Node* current = findStartNode(startIP);
    while (current && compareIPs(current->data, endIP, 2)) {
        outFile << current->data << std::endl;  // Write the log to the file
        current = current->next;  // Move to the next node
    }
    outFile.close();  // Close the file
}
