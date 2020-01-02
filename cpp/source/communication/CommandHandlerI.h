#pragma once

#include "utils/PossibleMoves.h"

#include <string>


class CommandHandlerI
{
public:
    virtual ~CommandHandlerI() = default;

    virtual void onSrvHandshake() = 0;

    virtual void onSrvNewGameOk(const std::string& fen) = 0;

    virtual void onSrvPossibleMoves(const int index, const PossibleMoves& moves) = 0;

    virtual void onSrvMoveResult(const int res
                               , const int fromIndex
                               , const int toIndex
                               , const std::string& fen
                               , const std::string& color
                               , const std::string& capture
                               , const std::string& flags
                               , const std::string& oppCheck
                               , const int oppKingPos) = 0;
};
