#include "dom/DOMBuilder.hpp"
#include <stack>
#include <iostream>

std::shared_ptr<Node> DOMBuilder::build(const std::vector<Token>& tokens) {
    // 1. Create a root document node
    auto root = std::make_shared<Node>(NodeType::Element, "document");
    std::stack<std::shared_ptr<Node>> nodeStack;
    nodeStack.push(root);

    for (const auto& token : tokens) {
        if (token.type == TokenType::TagOpen) {
            std::string rawContent = token.value;
            std::string tagName;
            std::string hrefValue = "";

            // 2. Logic to separate Tag Name from Attributes (like href)
            size_t firstSpace = rawContent.find(' ');
            if (firstSpace != std::string::npos) {
                // We found a space, e.g., "a href=..."
                tagName = rawContent.substr(0, firstSpace);
                
                // Look for href="something"
                size_t hrefPos = rawContent.find("href=");
                if (hrefPos != std::string::npos) {
                    size_t startQuote = rawContent.find('"', hrefPos);
                    size_t endQuote = rawContent.find('"', startQuote + 1);
                    if (startQuote != std::string::npos && endQuote != std::string::npos) {
                        hrefValue = rawContent.substr(startQuote + 1, endQuote - startQuote - 1);
                    }
                }
            } else {
                // No spaces, just a simple tag like "h1" or "p"
                tagName = rawContent;
            }

            // 3. Create the node and assign properties
            auto element = std::make_shared<Node>(NodeType::Element, tagName);
            element->href = hrefValue; // Now the node "knows" where it points!

            nodeStack.top()->children.push_back(element);
            nodeStack.push(element);
        }
        else if (token.type == TokenType::TagClose) {
            // Pop the stack to go back to the parent node
            if (nodeStack.size() > 1) {
                nodeStack.pop();
            }
        }
        else if (token.type == TokenType::Text) {
            // Create a text node and add to the current parent
            auto textNode = std::make_shared<Node>(NodeType::Text, token.value);
            nodeStack.top()->children.push_back(textNode);
        }
    }

    return root;
}