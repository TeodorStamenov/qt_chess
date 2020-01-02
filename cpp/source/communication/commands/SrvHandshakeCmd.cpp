#include "SrvHandshakeCmd.h"
#include "communication/CommandHandlerI.h"

SrvHandshakeCmd::SrvHandshakeCmd()
    : CommandImpl(CommandId::SERVICE_HANDSHAKE)
{
}

void SrvHandshakeCmd::handle(CommandHandlerI& handler)
{
    handler.onSrvHandshake();
}
