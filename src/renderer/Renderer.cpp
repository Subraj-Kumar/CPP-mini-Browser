#include "renderer/Renderer.hpp"

Renderer::Renderer(sf::Font& f)
    : font(f), cursorY(20.f) {}

void Renderer::render(
    sf::RenderWindow& window,
    const std::shared_ptr<Node>& root
) {
    cursorY = 20.f;
    for (const auto& child : root->children) {
        renderNode(window, child);
    }
}

void Renderer::renderNode(
    sf::RenderWindow& window,
    const std::shared_ptr<Node>& node,
    int headingLevel
) {
    if (node->type == NodeType::Element) {
        int newHeading = headingLevel;

        if (node->value == "h1")
            newHeading = 1;
        else if (node->value == "p" || node->value == "a")
            newHeading = 0;

        for (const auto& child : node->children) {
            renderNode(window, child, newHeading);
        }

        cursorY += 10.f; // spacing after block
    }
    else if (node->type == NodeType::Text) {
        sf::Text text;
        text.setFont(font);
        text.setString(node->value);

        if (headingLevel == 1)
            text.setCharacterSize(32);
        else
            text.setCharacterSize(20);

        text.setFillColor(sf::Color::Black);
        text.setPosition(20.f, cursorY);

        cursorY += text.getCharacterSize() + 10.f;
        window.draw(text);
    }
}