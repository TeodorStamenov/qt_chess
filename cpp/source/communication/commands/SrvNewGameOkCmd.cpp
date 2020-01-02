#include "SrvNewGameOkCmd.h"
#include "communication/CommandHandlerI.h"

SrvNewGameOkCmd::SrvNewGameOkCmd()
    : CommandImpl(CommandId::SERVICE_NEW_GAME_OK)
{
}

void SrvNewGameOkCmd::handle(CommandHandlerI& handler)
{
    handler.onSrvNewGameOk(command_.fen());
}
