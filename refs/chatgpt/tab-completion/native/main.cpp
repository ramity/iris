#include <iostream>
#include <string>

// Function to generate suggestions based on partial input
std::string autocomplete(const std::string& input) {
    // Dummy suggestions for demonstration purposes
    const std::string suggestions[] = {"apple", "banana", "cherry", "grape", "orange"};
    
    for (const std::string& suggestion : suggestions) {
        if (suggestion.rfind(input, 0) == 0) {
            return suggestion;
        }
    }
    
    return input; // No matching suggestion found, return input as is
}

int main() {
    std::string input;
    std::string suggestion;
    
    while (true) {
        std::cout << "\r> " << input << std::flush;
        std::getline(std::cin, input);

        if (input.empty()) continue;
        if (input == "exit") break;
        if (input.back() == '\t') {
            // User pressed Tab, generate and display suggestion
            suggestion = autocomplete(input);
            if (!suggestion.empty()) {
                input = suggestion;
            }
        }

        // Check for tab completion
        // if (input.back() == '\t') {
        //     input.pop_back(); // Remove the tab character
        //     std::string completedInput = autocomplete(input);
        //     std::cout << "Completed input: " << completedInput << std::endl;
        // } else {
        //     // Process the user's input here
        //     std::cout << "You entered: " << input << std::endl;
        // }
    }
    
    return 0;
}
