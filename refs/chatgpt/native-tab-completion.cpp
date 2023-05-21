#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

// Function to read a single character from the terminal
char readChar() {
    char ch;
    struct termios oldTermios, newTermios;

    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

    read(STDIN_FILENO, &ch, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);

    return ch;
}

// Function to generate suggestions based on partial input
std::string autocomplete(const std::string& partialInput) {
    // Dummy suggestions for demonstration purposes
    if (partialInput == "a")
        return "apple";
    else if (partialInput == "b")
        return "banana";
    else if (partialInput == "c")
        return "cherry";
    else if (partialInput == "g")
        return "grape";
    else if (partialInput == "o")
        return "orange";
    else
        return "";  // Empty string if no suggestions
}

int main() {
    std::string input;
    std::string suggestion;

    while (true) {
        std::cout << "> " << input;

        char ch = readChar();

        if (ch == '\n') {
            // User pressed Enter
            std::cout << std::endl;
            // Process the user's input here
            std::cout << "You entered: " << input << std::endl;
            input.clear();
        } else if (ch == '\t') {
            // User pressed Tab, generate and display suggestion
            suggestion = autocomplete(input);
            if (!suggestion.empty()) {
                input = suggestion;
                std::cout << suggestion;
            }
        } else {
            // Append character to input
            input += ch;
            std::cout << ch;
        }
    }

    return 0;
}