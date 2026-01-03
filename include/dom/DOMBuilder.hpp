#pragma once
#include <vector>
#include <memory>
#include "dom/Node.hpp"
#include "tokenizer/Token.hpp"

class DOMBuilder {
public:
    static std::shared_ptr<Node> build(
        const std::vector<Token>& tokens
    );
};