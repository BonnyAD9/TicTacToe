#include <iostream>
#include <string>
#include "board.hpp"

using namespace titato;

void Game(int width, int height, int playerCount, int winLength);
void WriteBoard(Board &b);
void WriteTile(int h);
int Error(std::string str);
void Help();

int main(int argc, char **argv)
{
    int width = 25;
    int height = 25;
    int playerCount = 2;
    int winLength = 5;

    while (*++argv)
    {
        std::string arg(*argv);

        if (arg == "-s" || arg == "--size")
        {
            if (!*++argv)
                return Error("Expected width and height after '" + arg + '\'');
            width = atoi(*argv);
            if (width <= 0)
                return Error("Width must be larger than 0");

            if (!*++argv)
                return Error("Expected both width and height after '" + arg + '\'');
            height = atoi(*argv);
            if (height <= 0)
                return Error("Height must be larger than 0");
            continue;
        }

        if (arg == "-p" || arg == "-players")
        {
            if (!*++argv)
                return Error("Expected player count after argument '" + arg + "'");
            playerCount = atoi(*argv);
            if (playerCount <= 0 || playerCount > 7)
                return Error("Number of players must be larger than 0 and less than 7");
            continue;
        }

        if (arg == "-w" || arg == "--win")
        {
            if (!*++argv)
                return Error("Expected win length after argument '" + arg + "'");
            winLength = atoi(*argv);
            if (winLength <= 0)
                return Error("Win length must be larger than 0");
            continue;
        }

        if (arg == "-h" || arg == "--help" || arg == "-?")
        {
            Help();
            return EXIT_SUCCESS;
        }

        if (arg == "-v" || arg == "--version")
        {
            std::cout << "titato v1.1.0 by BonnyAD9" << std::endl;
            return EXIT_SUCCESS;
        }

        return Error("Invalid argument '" + arg + "'");
    }

    Game(width, height, playerCount, winLength);
}

void Game(int width, int height, int playerCount, int winLength)
{
    Board b{width, height, playerCount, winLength};
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
            y <= 0 || y > b.GetHeight())
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
        // yellow H
        std::cout << " \x1b[93mH\x1b[0m ";
        break;
    case 4:
        // green A
        std::cout << " \x1b[92mA\x1b[0m ";
    case 5:
        // blue S
        std::cout << " \x1b]94S\x1b[0m ";
    case 6:
        // magenta V
        std::cout << " \x1b[95mV\x1b[0m ";
    default:
        std::cout << " ? ";
        break;
    }
}

int Error(std::string str)
{
    std::cout << "\x1b[91merror: " << str << std::endl;
    return EXIT_FAILURE;
}

void Help()
{
    std::cout
        << "titato v1.1.0 by BonnyAD9\n\n"
        << "Usage:\n"
        << "  titato [flags]\n\n"
        << "Flags:\n"
        << "  -s  --size [widht] [height]\n"
        << "    sets the board size\n\n"
        << "  -p  --players [player count]\n"
        << "    sets the player count\n\n"
        << "  -w  --win [win length]\n"
        << "    sets the minimum number of symbols one must have in row to win\n\n"
        << "  -h  --help  -?\n"
        << "    shows this help\n\n"
        << "  -v  --version\n"
        << "    shows the version number"
        << std::endl;
}