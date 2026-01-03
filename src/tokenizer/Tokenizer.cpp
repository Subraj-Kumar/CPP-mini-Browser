#include "tokenizer/Tokenizer.hpp"
#include <cctype>

std::vector<Token> Tokenizer::tokenize(const std::string& html) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < html.size()) {
        // --- TAG HANDLING ---
        if (html[i] == '<') {
            size_t closePos = html.find('>', i);
            if (closePos == std::string::npos) break;

            // This grabs EVERYTHING inside the < >, including "a href='page2.html'"
            std::string tagContent = html.substr(i + 1, closePos - i - 1);

            if (!tagContent.empty() && tagContent[0] == '/') {
                tokens.push_back({TokenType::TagClose, tagContent.substr(1)});
            } else {
                // For Day 6, we pass the whole string "a href=..." as the value
                tokens.push_back({TokenType::TagOpen, tagContent});
            }

            i = closePos + 1;
        }
        // --- TEXT HANDLING ---
        else {
            size_t nextTag = html.find('<', i);
            std::string text = html.substr(i, nextTag - i);

            // Simple whitespace trim (Crucial for clean rendering)
            bool hasActualText = false;
            for (char c : text) {
                if (!std::isspace(c)) {
                    hasActualText = true;
                    break;
                }
            }

            if (hasActualText) {
                tokens.push_back({TokenType::Text, text});
            }

            if (nextTag == std::string::npos) break;
            i = nextTag;
        }
    }

    return tokens;
}