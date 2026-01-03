#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "dom/Node.hpp"

struct LinkArea {
    sf::FloatRect bounds;
    std::string target;
};

class Renderer {
public:
    Renderer(sf::Font& font);

    void render(sf::RenderWindow& window,
                const std::shared_ptr<Node>& root);

    const std::vector<LinkArea>& getLinks() const;

private:
    sf::Font& font;
    float cursorY;
    std::vector<LinkArea> links;

    void renderNode(sf::RenderWindow& window,
                    const std::shared_ptr<Node>& node,
                    bool isLink = false,
                    const std::string& href = "");
};