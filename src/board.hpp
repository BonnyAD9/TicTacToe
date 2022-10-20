#pragma once
#include <vector>

namespace titato
{
    class Board
    {
    public:
        Board();
        Board(int width, int height, int playerCount, int winLength);
        int GetWidth();
        int GetHeight();
        int GetOnTurn();
        int GetWin();
        int Place(int x, int y);
        int Get(int x, int y);
    private:
        int _width;
        int _height;
        int _onTurn;
        int _win;
        int _playerCount;
        int _winLength;
        int &_At(int x, int y);
        int _NextTurn();
        int _CheckWin();
        bool _Check(int x, int y, int xc, int yc, int player, int count);
        std::vector<int> _board;
    };
} // namespace titato
