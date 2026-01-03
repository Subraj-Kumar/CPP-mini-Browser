#pragma once
#include <string>
#include <vector>
#include <memory>

enum class NodeType {
    Element,
    Text
};

struct Node {
    NodeType type;
    std::string value;     // tag name OR text
    std::string href;      // only used for <a>
    std::vector<std::shared_ptr<Node>> children;

    Node(NodeType t, const std::string& val)
        : type(t), value(val) {}
};