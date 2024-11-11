#include "DoublyLinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void DoublyLinkedList::append(const std::string& data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

std::vector<std::string> split_str(const std::string& s) {
    // std::cout << "splitting" << std::endl;
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    char delimiter = ' ';
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
        // std::cout << token << std::endl;
    }
    return tokens;
}

bool DoublyLinkedList::compareIPs(const std::string& string1, const std::string& string2, int only_ip = 1) {
    std::string ip2 = string2;
    std::string ip1 = string1;
    if(only_ip == 1){
        std::vector<std::string> sorted_ip1 = split_str(string1);
        std::vector<std::string> sorted_ip2 = split_str(string2);
        ip1 = sorted_ip1[3];
        ip2 = sorted_ip2[3];

    }
    else if (only_ip == 2){
        std::vector<std::string> sorted_ip1 = split_str(string1);
        ip1 = sorted_ip1[3];
    }
    else if (only_ip == 3){
        std::vector<std::string> sorted_ip2 = split_str(string2);
        ip2 = sorted_ip2[3];
    }
    std::istringstream ipStream1(ip1) , ipStream2(ip2);
    int a, b, c, d, e, f, g, h;
    
    ipStream1 >> a; ipStream1.ignore();
    ipStream1 >> b; ipStream1.ignore();
    ipStream1 >> c; ipStream1.ignore();
    ipStream1 >> d; ipStream1.ignore();


    ipStream2 >> e; ipStream2.ignore();
    ipStream2 >> f; ipStream2.ignore();
    ipStream2 >> g; ipStream2.ignore();
    ipStream2 >> h; ipStream2.ignore();

    return std::tie(a, b, c, d) < std::tie(e, f, g, h);
}
Node* DoublyLinkedList::merge(Node* first, Node* second) {
    if (!first) return second;
    if (!second) return first;

    if (compareIPs(first->data, second->data)) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = nullptr;
        return first;
    } else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

Node* DoublyLinkedList::split(Node* head) {
    Node* fast = head;
    Node* slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node* DoublyLinkedList::mergeSort(Node* node) {
    if (!node || !node->next) return node;

    Node* second = split(node);

    node = mergeSort(node);
    second = mergeSort(second);

    return merge(node, second);
}

void DoublyLinkedList::sort() {
    head = mergeSort(head);

    // Update the tail pointer after sorting
    tail = head;
    while (tail && tail->next) {
        tail = tail->next;
    }
}

Node* DoublyLinkedList::findStartNode(const std::string& startIP) {
    Node* current = head;
    while (current && compareIPs(current->data, startIP, 2)) {
        current = current->next;
    }
    return current;
}

void DoublyLinkedList::displayInRange(const std::string& startIP, const std::string& endIP) {
    Node* current = findStartNode(startIP);
    while (current && compareIPs(current->data, endIP, 2)) {
        std::cout << current->data << std::endl;
        current = current->next;
    }
}

void DoublyLinkedList::saveToFile(const std::string& filename, const std::string& startIP, const std::string& endIP) {
    std::ofstream outFile(filename);
    Node* current = findStartNode(startIP);
    while (current && compareIPs(current->data, endIP,2)) {
        outFile << current->data << std::endl;
        current = current->next;
    }
    outFile.close();
}
