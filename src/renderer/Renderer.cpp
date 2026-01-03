#include "renderer/Renderer.hpp"
#include <sstream>
#include <vector>

Renderer::Renderer(sf::Font& f)
    : font(f), cursorY(20.f) {}

const std::vector<LinkArea>& Renderer::getLinks() const {
    return links;
}

void Renderer::render(sf::RenderWindow& window, const std::shared_ptr<Node>& root) {
    cursorY = 20.f; // Start at the top with padding
    links.clear();  // Clear clickable areas for the new frame

    for (const auto& child : root->children) {
        renderNode(window, child);
    }
}

void Renderer::renderNode(sf::RenderWindow& window, const std::shared_ptr<Node>& node, bool isLink, const std::string& href) {
    if (node->type == NodeType::Element) {
        // Track if we are inside an <h1> or <a> for styling
        int headingLevel = (node->value == "h1") ? 1 : 0;
        bool currentlyALink = isLink || (node->value == "a");
        std::string currentHref = (node->value == "a") ? node->href : href;

        for (const auto& child : node->children) {
            renderNode(window, child, currentlyALink, currentHref);
        }

        // Add vertical spacing after block elements (h1, p)
        if (node->value == "h1" || node->value == "p" || node->value == "a") {
            cursorY += 15.f;
        }
    } 
    else if (node->type == NodeType::Text) {
        sf::Text text;
        text.setFont(font);
        
        // --- Styling ---
        // Links are blue/underlined, normal text is black
        if (isLink) {
            text.setFillColor(sf::Color::Blue);
            text.setStyle(sf::Text::Underlined);
            text.setCharacterSize(20);
        } else {
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(22);
        }

        // --- Word Wrapping Logic ---
        std::string fullText = node->value;
        std::stringstream ss(fullText);
        std::string word;
        std::string currentLine;
        float maxWidth = 850.f; // 900px window minus 50px margin
        float startX = 25.f;

        while (ss >> word) {
            std::string testLine = currentLine + word + " ";
            text.setString(testLine);

            // If the line exceeds maxWidth, draw currentLine and start a new line
            if (text.getGlobalBounds().width > maxWidth && !currentLine.empty()) {
                text.setString(currentLine);
                text.setPosition(startX, cursorY);
                window.draw(text);
                
                // If it's a link, save this specific line's bounds as clickable
                if (isLink) {
                    links.push_back({ text.getGlobalBounds(), href });
                }

                cursorY += text.getCharacterSize() + 8.f;
                currentLine = word + " ";
            } else {
                currentLine = testLine;
            }
        }

        // Draw the final line of the text block
        text.setString(currentLine);
        text.setPosition(startX, cursorY);
        window.draw(text);

        if (isLink) {
            links.push_back({ text.getGlobalBounds(), href });
        }

        // Move cursor down for the next element
        cursorY += text.getCharacterSize() + 5.f;
    }
}