#include <SFML/Graphics.hpp>
#include <iostream>

const int windowSize = 600;
const int gridSize = windowSize / 3;
sf::RectangleShape grid[3][3];
char board[3][3];
bool isXturn = true;

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j].setSize(sf::Vector2f(gridSize, gridSize));
            grid[i][j].setPosition(i * gridSize, j * gridSize);
            grid[i][j].setOutlineThickness(2);
            grid[i][j].setOutlineColor(sf::Color::Black);
            board[i][j] = ' ';
        }
    }
}

void drawGrid(sf::RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            window.draw(grid[i][j]);
            if (board[i][j] == 'X' || board[i][j] == 'O') {
                sf::Font font;
                if (!font.loadFromFile("arial.ttf")) {
                    std::cerr << "Error loading font\n";
                    exit(1);
                }
                sf::Text text(board[i][j], font, 100);
                text.setPosition(i * gridSize + gridSize / 4, j * gridSize);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
            }
        }
    }
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Tic Tac Toe");
    initializeBoard();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / gridSize;
                int y = event.mouseButton.y / gridSize;
                if (board[x][y] == ' ') {
                    board[x][y] = isXturn ? 'X' : 'O';
                    if (checkWin(board[x][y])) {
                        std::cout << (isXturn ? "X" : "O") << " wins!\n";
                        window.close();
                    }
                    isXturn = !isXturn;
                }
            }
        }
        window.clear(sf::Color::White);
        drawGrid(window);
        window.display();
    }
    return 0;
}
