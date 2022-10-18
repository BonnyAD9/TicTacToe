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
    while (!b.Win())
    {
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
            std::string s;
            std::cin.clear();
            std::cin >> s;
            if (s == "quit" || s == "rage quit")
                return;
            std::cin.ignore(50, '\n');
            continue;
        }
        b.Place(x - 1, y - 1);
    }
    std::cout << "\x1b[2J\x1b[H";
    WriteBoard(b);
    WriteTile(b.Win());
    std::cout << " wins!" << std::endl;
}

void WriteBoard(Board &b)
{
    std::cout << "   ";
    for (int i = 1; i <= b.GetWidth(); ++i)
    {
        auto s = std::to_string(i);
        if (s.length() < 2)
            std::cout << ' ';
        std::cout << s << ' ';
        std::cout << std::flush;
    }
    std::cout << std::endl;

    for (int y = 0; y < b.GetHeight(); ++y)
    {
        auto s = std::to_string(y + 1);
        std::cout << s << ' ';
        if (s.length() < 2)
            std::cout << ' ';

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
        std::cout << " \x1b[96mX\x1b[0m ";
        break;
    case 2:
        std::cout << " \x1b[91mO\x1b[0m ";
        break;
    case 3:
        std::cout << " \x1b[93mM\x1b[0m ";
        break;
    default:
        std::cout << "? ";
        break;
    }
}