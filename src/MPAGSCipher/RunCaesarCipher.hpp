
#ifndef RUNCAESARCIPHER_HPP
#define RUNCAESARCIPHER_HPP

#include <cstddef>
#include <string>

std::string runCaesarCipher(const std::string& inputText, const std::size_t key,
                            const bool encrypt);

#endif
