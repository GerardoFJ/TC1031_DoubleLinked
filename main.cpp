#include <iostream>
#include <fstream>
#include <string>
#include "DoublyLinkedList.h"

int main() {
    DoublyLinkedList logList;
    std::ifstream file("bitacora.txt");
    std::string line;

    while (std::getline(file, line)) {
        // std::cout << line << std::endl;
        logList.append(line);
    }
    file.close();
    logList.sort();

    std::string startIP, endIP;
    std::cout << "Enter the starting IP: ";
    std::cin >> startIP;
    std::cout << "Enter the ending IP: ";
    std::cin >> endIP;

    std::cout << "Logs in the range:" << std::endl;
    logList.displayInRange(startIP, endIP);

    logList.saveToFile("Filtered.txt", startIP, endIP);

    std::cout << "Filtered logs have been saved to Filtered.txt." << std::endl;
    return 0;
}
