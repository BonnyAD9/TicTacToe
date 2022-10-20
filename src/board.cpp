#include "board.hpp"

namespace titato
{
    Board::Board() :
        _width(3),
        _height(3),
        _onTurn(1),
        _win(false),
        _playerCount(2),
        _winLength(3),
        _board(_width * _height, 0)
    { }

    Board::Board(
        int width,
        int height,
        int playerCount,
        int winLength
    ) : _width(width),
        _height(height),
        _onTurn(1),
        _win(false),
        _playerCount(playerCount),
        _winLength(winLength),
        _board(_width * _height, 0)
    { }

    int Board::GetWidth() { return _width; }
    int Board::GetHeight() { return _height; }
    int Board::GetOnTurn() { return _onTurn; }
    int Board::GetWin() { return _win; }
    int Board::Get(int x, int y) { return _At(x, y); }

    int Board::Place(int x, int y)
    {
        if (_At(x, y))
            return _win;
        _At(x, y) = _onTurn;
        _NextTurn();
        return _CheckWin();
    }

    int &Board::_At(int x, int y)
    {
        return _board[_width * y + x];
    }

    int Board::_NextTurn()
    {
        return _onTurn = _onTurn % _playerCount + 1;
    }

    int Board::_CheckWin()
    {
        int win = -1;
        for (int x = 0; x < _width; ++x)
        {
            for (int y = 0; y < _height; ++y)
            {
                if (!_At(x, y))
                {
                    win = 0;
                    continue;
                }
                if (_Check(x, y,  1, 0, _At(x, y), _winLength) ||
                    _Check(x, y,  0, 1, _At(x, y), _winLength) ||
                    _Check(x, y,  1, 1, _At(x, y), _winLength) ||
                    _Check(x, y, -1, 1, _At(x, y), _winLength))
                    return _win = _At(x, y);
            }
        }
        return _win = win;
    }

    bool Board::_Check(int x, int y, int xc, int yc, int player, int count)
    {
        if (count == 0)
            return true;
        if (x < 0 || x >= _width || y >= _width || _At(x, y) != player)
            return false;
        return _Check(x + xc, y + yc, xc, yc, player, count - 1);
    }
} // namespace titato
