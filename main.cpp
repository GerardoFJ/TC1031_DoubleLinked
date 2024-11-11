#include <iostream>
#include <fstream>
#include <string>
#include "DoublyLinkedList.h"

int main() {
    DoublyLinkedList logList;    // Create an instance of DoublyLinkedList to store log entries

    std::ifstream file("bitacora.txt");  // Open the file "bitacora.txt" for reading
    std::string line;                    // Variable to store each line read from the file

    // Read each line from the file and add it to the doubly linked list
    while (std::getline(file, line)) {
        logList.append(line);             // Append the line to the doubly linked list
    }
    file.close();                         // Close the input file after reading all lines

    logList.sort();                       // Sort the list of logs based on IP addresses

    // Prompt the user for the IP range
    std::string startIP, endIP;
    std::cout << "Enter the starting IP: ";
    std::cin >> startIP;                  // Read the starting IP from user input
    std::cout << "Enter the ending IP: ";
    std::cin >> endIP;                    // Read the ending IP from user input

    // Display the logs that fall within the specified IP range
    std::cout << "Logs in the range:" << std::endl;
    logList.displayInRange(startIP, endIP);

    // Save the filtered logs to a file named "Filtered.txt"
    logList.saveToFile("Filtered.txt", startIP, endIP);

    // Inform the user that the filtered logs have been saved
    std::cout << "Filtered logs have been saved to Filtered.txt." << std::endl;
    return 0;
}
