#include "SrvMoveResultCmd.h"
#include "communication/CommandHandlerI.h"

SrvMoveResultCmd::SrvMoveResultCmd()
    : CommandImpl(CommandId::SERVICE_MOVE_RESULT)
{
}

void SrvMoveResultCmd::handle(CommandHandlerI& handler)
{
    handler.onSrvMoveResult(command_.result()
                          , command_.fromindex()
                          , command_.toindex()
                          , command_.color()
                          , command_.fen()
                          , command_.capture()
                          , command_.flags()
                          , command_.oppcheck()
                          , command_.oppkingpos());
}
