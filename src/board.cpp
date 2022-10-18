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
        _board(_width)
    {
        for (auto &l : _board)
            l = std::vector<int>(_height);
    }

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
        _board(_width)
    {
        for (auto &l : _board)
            l = std::vector<int>(_height);
    }

    int Board::GetWidth() { return _width; }
    int Board::GetHeight() { return _height; }
    int Board::GetOnTurn() { return _onTurn; }
    int Board::Win() { return _win; }
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
        return _board[x][y];
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
                if (
                    _CheckR(x, y, _At(x, y), _winLength) ||
                    _CheckRD(x, y, _At(x, y), _winLength) ||
                    _CheckD(x, y, _At(x, y), _winLength)
                )
                    return _win = _At(x, y);
            }
        }
        return _win = win;
    }

    bool Board::_CheckR(int x, int y, int player, int count)
    {
        if (count == 0)
            return true;
        if (x >= _width || _At(x, y) != player)
            return false;
        return _CheckR(x + 1, y, player, count - 1);
    }

    bool Board::_CheckRD(int x, int y, int player, int count)
    {
        if (count == 0)
            return true;
        if (x >= _width || y >= _height || _At(x, y) != player)
            return false;
        return _CheckRD(x + 1, y + 1, player, count - 1);
    }

    bool Board::_CheckD(int x, int y, int player, int count)
    {
        if (count == 0)
            return true;
        if (y >= _height || _At(x, y) != player)
            return false;
        return _CheckD(x, y + 1, player, count - 1);
    }
} // namespace titato
