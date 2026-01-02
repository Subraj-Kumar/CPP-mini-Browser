#pragma once
#include <string>

enum class TokenType {
    TagOpen,
    TagClose,
    Text
};

struct Token {
    TokenType type;
    std::string value;
};