#include <SFML/Graphics.hpp>
#include <iostream>
#include "file_loader/FileLoader.hpp"

int main() {
    // CHECKPOINT 1
    std::cout << "[DEBUG] Program Started..." << std::endl;

    std::string htmlContent;
    try {
        // CHECKPOINT 2: Trying to load
        std::cout << "[DEBUG] Attempting to load: assets/sample_pages/index.html" << std::endl;
        htmlContent = FileLoader::loadFile("assets/sample_pages/index.html");
        
        // CHECKPOINT 3: Success
        std::cout << "[DEBUG] Load Successful! Content length: " << htmlContent.length() << std::endl;
        std::cout << "--- CONTENT START ---" << std::endl;
        std::cout << htmlContent << std::endl;
        std::cout << "--- CONTENT END ---" << std::endl;

    } catch (const std::exception& e) {
        // CHECKPOINT 4: Failure
        std::cerr << "[ERROR] FileLoader failed: " << e.what() << std::endl;
        std::cerr << "[TIP] Make sure you are running from the root folder!" << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(900, 600), "C++ Mini Browser");
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