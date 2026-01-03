#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// Include our modular headers
#include "file_loader/FileLoader.hpp"
#include "tokenizer/Tokenizer.hpp"
#include "dom/DOMBuilder.hpp"
#include "renderer/Renderer.hpp"

int main() {
    // 1. Setup SFML Window
    sf::RenderWindow window(sf::VideoMode(900, 600), "C++ Mini Browser - Day 5");
    window.setFramerateLimit(60);

    // 2. Load Font (Make sure the path and filename match your assets folder!)
    sf::Font font;
    // Note: If you renamed your font to font.ttf, use that here.
    if (!font.loadFromFile("assets/fonts/font.ttf")) {
        std::cerr << "[ERROR] Could not load font from assets/fonts/Roboto-Regular.ttf" << std::endl;
        return -1;
    }

    // 3. The Browser Pipeline
    std::string htmlContent;
    try {
        // Load the initial page
        htmlContent = FileLoader::loadFile("assets/sample_pages/index.html");
        std::cout << "[SUCCESS] HTML Loaded." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return -1;
    }

    // Convert string -> tokens -> DOM tree
    auto tokens = Tokenizer::tokenize(htmlContent);
    auto domTree = DOMBuilder::build(tokens);
    
    // 4. Initialize the Renderer
    Renderer renderer(font);

    // 5. Main Event Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Rendering Phase ---
        window.clear(sf::Color::White); // Standard browser background

        // Draw the DOM tree to the window
        renderer.render(window, domTree);

        window.display();
    }

    return 0;
}