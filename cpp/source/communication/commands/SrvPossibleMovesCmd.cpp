#include "SrvPossibleMovesCmd.h"
#include "communication/CommandHandlerI.h"

SrvPossibleMovesCmd::SrvPossibleMovesCmd()
    : CommandImpl(CommandId::SERVICE_POSSIBLE_MOVES)
{
}

void SrvPossibleMovesCmd::handle(CommandHandlerI& handler)
{
    auto& protoArray = command_.moves();
    PossibleMoves moves(protoArray.begin(), protoArray.end());
    handler.onSrvPossibleMoves(command_.index(), moves);
}
