#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Include our modular headers
#include "file_loader/FileLoader.hpp"
#include "tokenizer/Tokenizer.hpp"

int main() {
    // 1. Load the HTML file
    std::string htmlContent;
    try {
        // Run from root folder so this path works!
        htmlContent = FileLoader::loadFile("assets/sample_pages/index.html");
        std::cout << "[SUCCESS] HTML file loaded." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return -1; // Exit if we can't load the file
    }

    // 2. Tokenize the HTML
    // This turns a long string into a List of structured Tokens
    std::vector<Token> tokens = Tokenizer::tokenize(htmlContent);

    // 3. Print Tokens to Terminal (Verification Step)
    std::cout << "\n--- Generated Tokens ---" << std::endl;
    for (const auto& token : tokens) {
        if (token.type == TokenType::TagOpen) {
            std::cout << "TAG_OPEN : <" << token.value << ">" << std::endl;
        } 
        else if (token.type == TokenType::TagClose) {
            std::cout << "TAG_CLOSE: </" << token.value << ">" << std::endl;
        } 
        else if (token.type == TokenType::Text) {
            std::cout << "TEXT      : \"" << token.value << "\"" << std::endl;
        }
    }
    std::cout << "------------------------\n" << std::endl;

    // 4. Setup SFML Window (Still blank for now, rendering comes in Day 5)
    sf::RenderWindow window(sf::VideoMode(900, 600), "C++ Mini Browser - Day 3");
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