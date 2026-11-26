
#include "ProcessCommandLine.hpp"

#include <iostream>
#include <string>
#include <vector>

bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFile, std::string& outputFile,
                        bool& encrypt, std::string& cipherkey)
{
    // Status flag to indicate whether or not the parsing was successful
    bool processStatus{true};

    // Process the arguments - ignore zeroth element, as we know this to be
    // the program name and don't need to worry about it
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            // Set the indicator and terminate the loop
            helpRequested = true;
            break;
        } else if (cmdLineArgs[i] == "--version") {
            // Set the indicator and terminate the loop
            versionRequested = true;
            break;
        } else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                processStatus = false;
                break;
            } else {
                inputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;

                processStatus = false;
                break;
            } else {
                outputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "--encrypt") {
            // Select encryption mode
            encrypt = true;
        } else if (cmdLineArgs[i] == "--decrypt") {
            // Select decryption mode
            encrypt = false;
        } else if (cmdLineArgs[i] == "--key") {
            // Handle cipher key option
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] --key requires a key argument"
                          << std::endl;

                processStatus = false;
                break;
            } else {
                // Got key, so assign value and advance past it
                cipherkey = cmdLineArgs[i + 1];
                ++i;
            }

        } else {
            // Handle unknown command-line argument
            std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                      << "'\n";

            processStatus = false;
            break;
        }
    }
    return processStatus;
}