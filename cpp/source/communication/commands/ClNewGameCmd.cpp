#include "ClNewGameCmd.h"

ClNewGameCmd::ClNewGameCmd()
    : CommandImpl(CommandId::CLIENT_NEW_GAME)
{
}

void ClNewGameCmd::setFen(const std::string& fen)
{
    command_.set_fen(fen);
}
