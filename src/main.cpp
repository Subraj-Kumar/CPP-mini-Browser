#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

// Include our modular headers
#include "file_loader/FileLoader.hpp"
#include "tokenizer/Tokenizer.hpp"
#include "dom/DOMBuilder.hpp"
#include "dom/Node.hpp"

// Recursive function to print the DOM Tree to the terminal with indentation
void printDOM(const std::shared_ptr<Node>& node, int depth = 0) {
    // Create indentation based on depth
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";

    if (node->type == NodeType::Element) {
        std::cout << "<" << node->value << ">" << std::endl;
    } else {
        std::cout << "\"" << node->value << "\"" << std::endl;
    }

    // Recursively print all children
    for (const auto& child : node->children) {
        printDOM(child, depth + 1);
    }
}

int main() {
    // 1. Load the HTML file
    std::string htmlContent;
    try {
        htmlContent = FileLoader::loadFile("assets/sample_pages/index.html");
        std::cout << "[SUCCESS] File loaded." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return -1;
    }

    // 2. Tokenize the HTML string
    auto tokens = Tokenizer::tokenize(htmlContent);
    std::cout << "[SUCCESS] Tokens generated." << std::endl;

    // 3. Build the DOM Tree from the tokens
    auto domTree = DOMBuilder::build(tokens);
    std::cout << "[SUCCESS] DOM Tree built." << std::endl;

    // 4. Visualize the Tree in the terminal
    std::cout << "\n--- DOM Tree Structure ---" << std::endl;
    printDOM(domTree);
    std::cout << "--------------------------\n" << std::endl;

    // 5. Setup SFML Window
    sf::RenderWindow window(sf::VideoMode(900, 600), "C++ Mini Browser - Day 4");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}