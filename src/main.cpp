#include <iostream>
#include <string>
#include "board.hpp"

using namespace titato;

void Game();
void WriteBoard(Board &b);
void WriteTile(int h);

int main()
{
    Game();
}

void Game()
{
    Board b{25, 25, 2, 5};
    while (!b.GetWin())
    {
        // clear the screen and set the cursor position to the top left
        std::cout << "\x1b[2J\x1b[H";
        WriteBoard(b);
        WriteTile(b.GetOnTurn());
        std::cout << std::flush;

        int x = 0;
        int y = 0;
        std::cin >> x >> y;
        if (x <= 0 || x > b.GetWidth() ||
            y <= 0 || y >= b.GetHeight())
        {
            // clear the cin errors
            std::cin.clear();

            std::string s;
            std::cin >> s;

            // rage quit option doesn't work
            if (s == "quit" || s == "rage quit")
                return;

            std::cin.ignore(50, '\n');
            continue;
        }

        b.Place(x - 1, y - 1);
    }

    // clear the screen and set the cursor position to the top left
    std::cout << "\x1b[2J\x1b[H";
    WriteBoard(b);
    WriteTile(b.GetWin());
    std::cout << " wins!" << std::endl;
}

void WriteBoard(Board &b)
{
    // write the numbers on the top
    std::cout << "   ";
    for (int i = 1; i <= b.GetWidth(); ++i)
    {
        if (i < 10)
            std::cout << ' ';
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // write the board
    for (int y = 0; y < b.GetHeight(); ++y)
    {
        // write the line number
        std::cout << y + 1 << ' ';
        if (y + 1 < 10)
            std::cout << ' ';

        // write the tiles
        for (int x = 0; x < b.GetWidth(); ++x)
            WriteTile(b.Get(x, y));

        std::cout << std::endl;
    }
}

void WriteTile(int h)
{
    switch (h)
    {
    case 0:
        //std::cout << "\x1b[90m─┼─\x1b[0m";
        std::cout << " . ";
        break;
    case 1:
        // cyan X
        std::cout << " \x1b[96mX\x1b[0m ";
        break;
    case 2:
        // red O
        std::cout << " \x1b[91mO\x1b[0m ";
        break;
    case 3:
        // yellow M
        std::cout << " \x1b[93mM\x1b[0m ";
        break;
    default:
        std::cout << " ? ";
        break;
    }
}