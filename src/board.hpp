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
        bool _CheckR(int x, int y, int player, int count);
        bool _CheckRD(int x, int y, int player, int count);
        bool _CheckD(int x, int y, int player, int count);
        std::vector<std::vector<int>> _board;
    };
} // namespace titato
