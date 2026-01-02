#pragma once
#include <string>
#include <vector>
#include "tokenizer/Token.hpp"

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string& html);
};