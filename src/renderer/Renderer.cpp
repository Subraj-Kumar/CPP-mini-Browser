#include "renderer/Renderer.hpp"

Renderer::Renderer(sf::Font& f)
    : font(f), cursorY(20.f) {}

// This returns the list of clickable areas so main.cpp can check for mouse clicks
const std::vector<LinkArea>& Renderer::getLinks() const {
    return links;
}

void Renderer::render(sf::RenderWindow& window, const std::shared_ptr<Node>& root) {
    cursorY = 20.f; // Reset scroll to top every frame
    links.clear();  // Clear old clickable areas before recalculating

    // We start rendering from the children of the 'document' root
    for (const auto& child : root->children) {
        renderNode(window, child);
    }
}

void Renderer::renderNode(sf::RenderWindow& window, const std::shared_ptr<Node>& node, bool isLink, const std::string& href) {
    if (node->type == NodeType::Element) {
        // 1. Check if this tag changes the style (h1 vs p vs a)
        bool currentlyALink = isLink || (node->value == "a");
        std::string currentHref = href;
        if (node->value == "a") {
            currentHref = node->href;
        }

        // 2. Recursively render children (this handles nested tags)
        for (const auto& child : node->children) {
            renderNode(window, child, currentlyALink, currentHref);
        }

        // 3. Add a little "block" spacing after an element (like a <p> or <h1> does)
        cursorY += 10.f;
    } 
    else if (node->type == NodeType::Text) {
        // 4. Actually draw the text to the SFML window
        sf::Text text;
        text.setFont(font);
        text.setString(node->value);
        text.setCharacterSize(20);
        text.setPosition(20.f, cursorY);

        // 5. Apply "CSS" (Blue for links, Black for normal text)
        if (isLink) {
            text.setFillColor(sf::Color::Blue);
            text.setStyle(sf::Text::Underlined);
        } else {
            text.setFillColor(sf::Color::Black);
            text.setStyle(sf::Text::Regular);
        }

        window.draw(text);

        // 6. If it's a link, save its position so we can click it later
        if (isLink) {
            links.push_back({ text.getGlobalBounds(), href });
        }

        // 7. Move the cursor down so the next line of text is below this one
        cursorY += text.getCharacterSize() + 10.f;
    }
}