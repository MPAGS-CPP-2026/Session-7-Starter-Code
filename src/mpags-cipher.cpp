
#include "ProcessCommandLine.hpp"
#include "TransformChar.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    bool encrypt{true};

    // Process command line arguments
    const bool cmdLineStatus{processCommandLine(cmdLineArgs, helpRequested,
                                                versionRequested, inputFile,
                                                outputFile, encrypt)};

    // Any failure in the argument processing means we can't continue
    // Use a non-zero return value to indicate failure
    if (!cmdLineStatus) {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  --encrypt         Encrypt the input text (default)\n\n"
            << "  --decrypt         Decrypt the input text\n"
            << std::endl;

        return 0;
    }

    // Handle version, if requested
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Exercise 7.1
    if (!inputFile.empty()) {
        // Open the input file
        std::ifstream inFile{inputFile};

        // Check that the file opened correctly
        if (!inFile.good()) {
            std::cerr << "[error] Unable to open input file: " << inputFile
                      << std::endl;
            return 1;
        }

        // Loop over each character from the input file
        while (inFile >> inputChar) {
            inputText += transformChar(inputChar);
        }

    } else {
        // Loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    // Write the transliterated text to a file or stdout
    if (!outputFile.empty()) {
        // Open the output file
        std::ofstream outFile{outputFile};

        // Check that the file opened correctly
        if (!outFile.good()) {
            std::cerr << "[error] Unable to open output file: " << outputFile
                      << std::endl;
            return 1;
        }

        // Write the processed text to the output file
        outFile << inputText << std::endl;

    } else {
        // Print the transliterated text to the screen
        std::cout << inputText << std::endl;
    }

    // Return zero to indicate successful execution
    return 0;
}