#include <map>
#include <iostream>
#include <random>
#include <string>
#include <iomanip>

const int PAGE_SIZE = 1024;
const int FRAME_SIZE = 1024;
const int NUM_PAGES = 128;

bool validateHexInput(std::string input) {
    bool valid = true;

    for (int i = 0; i < input.size(); ++i) {
        if (!isxdigit(input.at(i))) {
            valid = false;
            break;
        }
    }

    return valid;

}

int main() {


    std::map<int, int> pageFrameTable; // create the page/frame table

    // Map each entry in the page/frame table to a memory address
    for (int i = 0; i < NUM_PAGES; ++i) {
        pageFrameTable.emplace(i, (rand())); // This maps each entry in the page/frame table to a (random) memory frame
    }

    int logicalAddress;
    std::string input;

    do {

        // Have the user enter logical addresses
        std::cout << "Enter a logical address (If you wish to quit, enter -1):\n0x";
        std::getline(std::cin, input);

        if (input == "-1") {
            break;
        }

        if (!validateHexInput(input)) {
            std::cerr << "Invalid input, please try again." << std::endl << std::endl;
            continue;
        }

        int logicalAddress = std::stoi(input, 0, 16);


        int pageNumber = logicalAddress / PAGE_SIZE; // Calculate the page number
        int offset = logicalAddress % PAGE_SIZE; // Calculate the offset from the page

        if (pageNumber > NUM_PAGES) {
            std::cerr << "Page fault, loading page to from secondary storage...";
            pageFrameTable.emplace(pageNumber, (rand()));// Loads new page with new (random) frame number from memory
        }

        int frameNumber = pageFrameTable.at(pageNumber); // Get the frame number associate with the page number from the page/frame table
        int physicalAddress = frameNumber * FRAME_SIZE + offset; // Calculate the physical address with the frame number, size, and offset

        std::cout << std::endl << "Logical Address: 0x" << std::hex << logicalAddress << " ==> Page Number: 0x" << std::hex << pageNumber << ", Offset: 0x" << std::hex << offset << ", Physical Address: 0x" << std::hex << physicalAddress << std::endl << std::endl;
        // Print the page number, offset, and physical address


    } while (input != "-1");  


}