#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "dom/Node.hpp"

class Renderer {
public:
    Renderer(sf::Font& font);
    void render(
        sf::RenderWindow& window,
        const std::shared_ptr<Node>& root
    );

private:
    sf::Font& font;
    float cursorY;

    void renderNode(
        sf::RenderWindow& window,
        const std::shared_ptr<Node>& node,
        int headingLevel = 0
    );
};