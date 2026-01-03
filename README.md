# C++ Mini Browser Engine

A lightweight, custom browser engine built from the ground up in C++17. This project implements the core stages of a modern browser pipeline: loading, tokenization, parsing, and rendering.

## 🚀 Overview
Rather than using existing browser engines, this project explores the internal mechanics of web browsers. It transforms raw HTML strings into a visual interactive experience using a custom-built rendering pipeline.

## 🛠 Architecture & Pipeline
The engine follows a linear data flow:
1. **File Loader**: Reads local HTML resources from the disk.
2. **Lexical Analysis (Tokenizer)**: Converts raw strings into a stream of Tag and Text tokens.
3. **Syntax Analysis (DOM Builder)**: Uses a **Stack-based Parser** to transform tokens into a hierarchical Document Object Model (DOM) tree.
4. **Layout & Paint (Renderer)**: Traverses the DOM tree using **Depth-First Search (DFS)** and draws text to an SFML window using a vertical flow layout.



## 📋 Features
- **Custom HTML Parser**: Supports `<html>`, `<body>`, `<h1>`, `<p>`, and `<a>`.
- **Navigation Engine**: Functional `<a>` links and a **Navigation Stack** for back-history (Backspace).
- **Event Handling**: Coordinate-based "hit-testing" for interactive link elements.
- **Resource Management**: Dynamic font loading and automated asset deployment via CMake.

## 💻 Tech Stack
- **Language**: C++17 (Smart pointers, STL containers, Lambdas)
- **Graphics**: SFML (Simple and Fast Multimedia Library)
- **Build System**: CMake

## 🚀 How to Build & Run
1. Ensure SFML is installed via MSYS2 (`mingw-w64-ucrt-x86_64-sfml`).
2. Create a build directory: `mkdir build && cd build`
3. Configure: `cmake ..`
4. Compile: `mingw32-make`
5. Run: `./browser.exe`

## 🧠 Key Learnings
- **Tree Structures**: Managed complex parent-child relationships in the DOM.
- **Memory Management**: Used `std::shared_ptr` to prevent memory leaks in the recursive tree structure.
- **Separation of Concerns**: Decoupled the logic (Parser) from the visual representation (Renderer).