#include "dom/DOMBuilder.hpp"
#include <stack>

std::shared_ptr<Node> DOMBuilder::build(
    const std::vector<Token>& tokens
) {
    auto root = std::make_shared<Node>(NodeType::Element, "document");
    std::stack<std::shared_ptr<Node>> nodeStack;
    nodeStack.push(root);

    for (const auto& token : tokens) {
        if (token.type == TokenType::TagOpen) {
            auto element = std::make_shared<Node>(
                NodeType::Element, token.value
            );
            nodeStack.top()->children.push_back(element);
            nodeStack.push(element);
        }
        else if (token.type == TokenType::TagClose) {
            if (!nodeStack.empty())
                nodeStack.pop();
        }
        else if (token.type == TokenType::Text) {
            auto textNode = std::make_shared<Node>(
                NodeType::Text, token.value
            );
            nodeStack.top()->children.push_back(textNode);
        }
    }

    return root;
}