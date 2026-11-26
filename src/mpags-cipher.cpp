
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"
#include "TransformChar.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
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
    std::string cipherkey{""};

    // Process command line arguments
    const bool cmdLineStatus{
        processCommandLine(cmdLineArgs, helpRequested, versionRequested,
                           inputFile, outputFile, encrypt, cipherkey)};

    // Check that the command-line processing was successful
    if (!cmdLineStatus) {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] "
            << "[-i <file>] [-o <file>] "
            << "[--encrypt/--decrypt] [--key <key>]\n\n"

            << "Encrypts/Decrypts input alphanumeric text "
            << "using classical ciphers\n\n"

            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"

            << "  --encrypt        Encrypt the input text (default)\n\n"

            << "  --decrypt        Decrypt the input text\n\n"

            << "  --key KEY        Specify the cipher key (0-25)\n\n"

            << std::endl;

        return 0;
    }

    // Handle version, if requested
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Convert the cipher key from a string to an integer
    std::size_t key{0};

    try {
        std::size_t position{0};

        const unsigned long convertedKey{std::stoul(cipherkey, &position)};

        // Check that the key is a valid integer between 0 and 25
        if (cipherkey.empty() ||
            cipherkey.find_first_not_of("0123456789") != std::string::npos ||
            position != cipherkey.size() || convertedKey > 25) {
            std::cerr << "[error] Caesar cipher key must be "
                      << "an integer between 0 and 25\n";
            return 1;
        }

        key = static_cast<std::size_t>(convertedKey);

    } catch (const std::exception&) {
        std::cerr << "[error] Invalid or missing cipher key\n";
        return 1;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
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

    // Run the Caesar cipher on the transliterated text
    const std::string outputText{runCaesarCipher(inputText, key, encrypt)};

    // Write the encrypted/decrypted text to a file or stdout
    if (!outputFile.empty()) {
        // Open the output file
        std::ofstream outFile{outputFile};

        // Check that the file opened correctly
        if (!outFile.good()) {
            std::cerr << "[error] Unable to open output file: " << outputFile
                      << std::endl;
            return 1;
        }

        // Write the cipher output to the output file
        outFile << outputText << std::endl;

    } else {
        // Print the cipher output to the screen
        std::cout << outputText << std::endl;
    }

    // Return zero to indicate successful execution
    return 0;
}