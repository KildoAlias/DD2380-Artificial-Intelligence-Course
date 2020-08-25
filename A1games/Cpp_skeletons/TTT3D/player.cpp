#include "player.hpp"
#include <cstdlib>
#include <cstdio>
#include <numeric>
#include <cmath>

namespace TICTACTOE3D

{
int gamma(const GameState &pState)
{
    int eval;
    int state;
    for (size_t cell = 0; cell < 64; cell++)
    {
        if (pState.at(cell) & CELL_X)
        {
            if (cell < 16)
            {
                eval++;
                state = false;
                while (state = true)
                {
                    if ((pState.at(cell + 1) & CELL_X) && (cell < 16))
                    {
                        eval++;
                        cell++;
                    }
                    else
                    {
                        state = false;
                    }
                }
            }
        }
    }
}
} // namespace TICTACTOE3D
int minimax(const GameState &pState, int player, int depth, int alpha, int beta)
{
    int v;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (depth == 0 || lNextStates.size() == 0)
    {
        return gamma(pState);
    }
    else if (player == 1)
    {
        v = -99999999;
        for (size_t i = 0; i < lNextStates.size(); i++)
        {
            v = std::max(v, minimax(lNextStates[i], 2, depth - 1, alpha, beta));
            alpha = std::max(alpha, v);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    else //player O
    {
        v = 99999999;
        for (size_t i = 0; i < lNextStates.size(); i++)
        {
            v = std::min(v, minimax(lNextStates[i], 1, depth - 1, alpha, beta));
            beta = std::min(beta, v);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    return v;
}

GameState Player::play(const GameState &pState, const Deadline &pDue)
{

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    int maxval = -9999999;
    int bestpos;
    int idx;
    int depth = 0;
    int alpha = -9999999;
    int beta = 9999999;

    if (lNextStates.size() == 0)
    {
        return GameState(pState, Move());
    }
    else
    {
        for (size_t i = 0; i < lNextStates.size(); i++)
        {
            bestpos = minimax(lNextStates[i], 2, depth, alpha, beta);
            if (bestpos > maxval)
            {
                maxval = bestpos;
                idx = i;
            }
        }
    }
    return lNextStates[idx];
}

} // namespace TICTACTOE3D