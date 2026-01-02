#include "tokenizer/Tokenizer.hpp"
#include <cctype>

std::vector<Token> Tokenizer::tokenize(const std::string& html) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < html.size()) {
        // TAG
        if (html[i] == '<') {
            size_t closePos = html.find('>', i);
            if (closePos == std::string::npos)
                break;

            std::string tag = html.substr(i + 1, closePos - i - 1);

            if (!tag.empty() && tag[0] == '/') {
                tokens.push_back({TokenType::TagClose, tag.substr(1)});
            } else {
                tokens.push_back({TokenType::TagOpen, tag});
            }

            i = closePos + 1;
        }
        // TEXT
        else {
            size_t nextTag = html.find('<', i);
            std::string text = html.substr(i, nextTag - i);

            // Trim whitespace-only text
            bool hasText = false;
            for (char c : text) {
                if (!std::isspace(c)) {
                    hasText = true;
                    break;
                }
            }

            if (hasText) {
                tokens.push_back({TokenType::Text, text});
            }

            if (nextTag == std::string::npos)
                break;

            i = nextTag;
        }
    }

    return tokens;
}