#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <memory>
#include <string>

// Include our custom modules
#include "file_loader/FileLoader.hpp"
#include "tokenizer/Tokenizer.hpp"
#include "dom/DOMBuilder.hpp"
#include "renderer/Renderer.hpp"

int main() {
    // 1. Initialize the SFML Window
    sf::RenderWindow window(sf::VideoMode(900, 600), "C++ Mini Browser - Final Version");
    window.setFramerateLimit(60);

    // 2. Load the Font
    sf::Font font;
    // Ensure this path matches your assets folder structure
    if (!font.loadFromFile("assets/fonts/font.ttf")) {
        std::cerr << "[ERROR] Could not load font. Ensure font is in assets/fonts/" << std::endl;
        // Don't return -1 yet, try a fallback if needed, or just warn.
    }

    // 3. Browser State & Navigation History
    std::stack<std::string> history;
    std::string currentPage = "assets/sample_pages/index.html";

    // Lambda to handle the full pipeline of loading a new page
    auto loadPage = [&](const std::string& path) {
        try {
            std::cout << "[NAVIGATING] Loading: " << path << std::endl;
            std::string html = FileLoader::loadFile(path);
            auto tokens = Tokenizer::tokenize(html);
            return DOMBuilder::build(tokens);
        } catch (const std::exception& e) {
            std::cerr << "[BROWSER ERROR] " << e.what() << std::endl;
            // Return an "Error Page" DOM node if the file isn't found
            auto errorNode = std::make_shared<Node>(NodeType::Element, "body");
            errorNode->children.push_back(std::make_shared<Node>(NodeType::Text, "404 - Page Not Found"));
            return errorNode;
        }
    };

    // Initial page load
    auto domTree = loadPage(currentPage);
    Renderer renderer(font);

    // 4. The Main Event Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle Window Close
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle Mouse Click (Link Navigation)
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                
                for (const auto& link : renderer.getLinks()) {
                    if (link.bounds.contains(mousePos)) {
                        history.push(currentPage); // Store current page in history
                        currentPage = "assets/sample_pages/" + link.target;
                        domTree = loadPage(currentPage);
                        break; 
                    }
                }
            }

            // Handle Keyboard (Backspace for Back Navigation)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
                if (!history.empty()) {
                    currentPage = history.top();
                    history.pop();
                    domTree = loadPage(currentPage);
                }
            }
        }

        // 5. The Rendering Phase
        window.clear(sf::Color::White); // Clean white background

        // The renderer walks the DOM and draws it to the screen
        renderer.render(window, domTree);

        window.display();
    }

    return 0;
}