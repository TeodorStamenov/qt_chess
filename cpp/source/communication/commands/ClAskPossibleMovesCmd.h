#pragma once

#include "communication/commands/CommandImpl.h"

class ClAskPossibleMovesCmd : public CommandImpl<ClAskPossibleMovesCmd>
{
public:
    ClAskPossibleMovesCmd();

    void init(int boardIndex);
};
