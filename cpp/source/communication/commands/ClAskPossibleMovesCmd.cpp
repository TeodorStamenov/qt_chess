#include "ClAskPossibleMovesCmd.h"

ClAskPossibleMovesCmd::ClAskPossibleMovesCmd()
    : CommandImpl(CommandId::CLIENT_ASK_MOVES)
{
}

void ClAskPossibleMovesCmd::init(int boardIndex)
{
    command_.set_index(boardIndex);
}
