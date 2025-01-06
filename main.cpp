#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>
#include <utility>

const char PLAYER = 'O';
const char AI = 'X';
const char EMPTY = ' ';

const int SIZE = 3;
const int CELL_SIZE = 100; // Each cell's size in pixels

void init_board(char board[SIZE][SIZE]);
void draw_board(sf::RenderWindow& window, char board[SIZE][SIZE]);
bool is_move_left(char board[SIZE][SIZE]);
bool is_winner(char board[SIZE][SIZE], char player);
int evaluate(char board[SIZE][SIZE]);
int minimax(char board[SIZE][SIZE], int depth, bool is_max);
std::pair<int, int> find_best_move(char board[SIZE][SIZE]);

int main()
{
    char board[SIZE][SIZE];
    init_board(board);

    sf::RenderWindow window(sf::VideoMode(320, 320), "Tic-Tac-Toe");

    sf::Font font;
    if (!font.loadFromFile("/Users/elmar/Downloads/FilesBefore25december/arial/ARIAL.TTF")) // Replace with a valid font path
    {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        draw_board(window, board);

        // Handle mouse click (Player's move)
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int row = event.mouseButton.y / CELL_SIZE;
                int col = event.mouseButton.x / CELL_SIZE;

                if (row < SIZE && col < SIZE && board[row][col] == EMPTY)
                {
                    board[row][col] = PLAYER;

                    // Check if the player wins
                    if (is_winner(board, PLAYER))
                    {
                        draw_board(window, board);
                        text.setString("You win!");
                        window.draw(text);
                        window.display();
                        sf::sleep(sf::seconds(2));
                        break;
                    }

                    // Check if it's a draw
                    if (!is_move_left(board))
                    {
                        draw_board(window, board);
                        text.setString("It's a draw!");
                        window.draw(text);
                        window.display();
                        sf::sleep(sf::seconds(2));
                        break;
                    }

                    // AI's move
                    std::pair<int, int> best_move = find_best_move(board);
                    board[best_move.first][best_move.second] = AI;

                    // Check if the AI wins
                    if (is_winner(board, AI))
                    {
                        draw_board(window, board);
                        text.setString("AI wins!");
                        window.draw(text);
                        window.display();
                        sf::sleep(sf::seconds(2));
                        break;
                    }

                    // Check if it's a draw
                    if (!is_move_left(board))
                    {
                        draw_board(window, board);
                        text.setString("It's a draw!");
                        window.draw(text);
                        window.display();
                        sf::sleep(sf::seconds(2));
                        break;
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}

void init_board(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = EMPTY;
        }
    }
}

void draw_board(sf::RenderWindow& window, char board[SIZE][SIZE])
{
    // Draw grid
    sf::RectangleShape line(sf::Vector2f(CELL_SIZE * SIZE, 2));
    line.setFillColor(sf::Color::Black);

    for (int i = 1; i < SIZE; i++)
    {
        // Draw horizontal lines
        line.setSize(sf::Vector2f(CELL_SIZE * SIZE, 2));
        line.setPosition(0, i * CELL_SIZE);
        window.draw(line);

        // Draw vertical lines
        line.setSize(sf::Vector2f(2, CELL_SIZE * SIZE));
        line.setPosition(i * CELL_SIZE, 0);
        window.draw(line);
    }

    // Draw X's and O's
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == PLAYER) // Draw O
            {
                sf::CircleShape circle(35);
                circle.setPosition(j * CELL_SIZE + 15, i * CELL_SIZE + 15);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOutlineColor(sf::Color::Blue);
                circle.setOutlineThickness(3);
                window.draw(circle);
            }
            else if (board[i][j] == AI) // Draw X
            {
                // First line of X
                sf::RectangleShape line1(sf::Vector2f(70, 3));
                line1.setPosition(j * CELL_SIZE + 15, i * CELL_SIZE + 15);
                line1.setRotation(45);
                line1.setFillColor(sf::Color::Red);
                window.draw(line1);

                // Second line of X
                sf::RectangleShape line2(sf::Vector2f(70, 3));
                line2.setPosition(j * CELL_SIZE + 85, i * CELL_SIZE + 15);
                line2.setRotation(135);
                line2.setFillColor(sf::Color::Red);
                window.draw(line2);
            }
        }
    }
}

bool is_move_left(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == EMPTY)
                return true;
        }
    }
    return false;
}

bool is_winner(char board[SIZE][SIZE], char player)
{
    // Check rows
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }

    // Check columns
    for (int i = 0; i < SIZE; i++)
    {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

int evaluate(char board[SIZE][SIZE])
{
    if (is_winner(board, AI))
        return 10;
    if (is_winner(board, PLAYER))
        return -10;
    return 0;
}

int minimax(char board[SIZE][SIZE], int depth, bool is_max)
{
    int score = evaluate(board);

    // Terminal states
    if (score == 10 || score == -10)
        return score;
    if (!is_move_left(board))
        return 0;

    if (is_max)
    {
        int best = std::numeric_limits<int>::min();

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = AI;
                    best = std::max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    else
    {
        int best = std::numeric_limits<int>::max();

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = PLAYER;
                    best = std::min(best, minimax(board, depth + 1, true)); // Fixed to std::min
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

std::pair<int, int> find_best_move(char board[SIZE][SIZE])
{
    int best_value = std::numeric_limits<int>::min();
    std::pair<int, int> best_move = std::make_pair(-1, -1);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = AI;

                int move_value = minimax(board, 0, false);

                board[i][j] = EMPTY;

                if (move_value > best_value)
                {
                    best_move = std::make_pair(i, j);
                    best_value = move_value;
                }
            }
        }
    }

    return best_move;
}
