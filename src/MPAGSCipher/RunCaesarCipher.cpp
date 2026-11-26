
#include "RunCaesarCipher.hpp"

#include <cstddef>
#include <string>

std::string runCaesarCipher(const std::string& inputText, const std::size_t key,
                            const bool encrypt)
{
    // Create the alphabet container and output string
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::string outputText{""};

    // Determine the size of the alphabet
    const std::size_t alphabetSize{alphabet.size()};

    // Ensure that the shift is within the alphabet size
    const std::size_t shift{key % alphabetSize};

    // Loop over the input text
    for (const char inputChar : inputText) {
        // Find the corresponding position in the alphabet
        for (std::size_t i{0}; i < alphabetSize; ++i) {
            if (inputChar == alphabet[i]) {
                // Initialise the new position
                std::size_t newPosition{0};

                // Apply the shift, handling wrap-around
                if (encrypt) {
                    newPosition = (i + shift) % alphabetSize;
                } else {
                    newPosition = (i + alphabetSize - shift) % alphabetSize;
                }

                // Determine the new character and add it
                // to the output string
                outputText += alphabet[newPosition];

                // Character has been found, so exit inner loop
                break;
            }
        }
    }

    // Return the encrypted/decrypted output string
    return outputText;
}
