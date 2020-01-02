#include "CommandCreator.h"
#include "communication/commands/CommandIds.h"
#include "communication/commands/SrvHandshakeCmd.h"
#include "communication/commands/SrvNewGameOkCmd.h"
#include "communication/commands/SrvPossibleMovesCmd.h"
#include "communication/commands/SrvMoveResultCmd.h"
#include "communication/Buffer.h"


CommandCreator::CommandCreator()
{
}

CommandPtr CommandCreator::createCommand(const Buffer &buf)
{
    CommandPtr cmd;
    CommandId type = static_cast<CommandId>(buf.cmdType());

    switch(type)
    {
        case CommandId::SERVICE_HANDSHAKE:
            cmd = std::make_unique<SrvHandshakeCmd>();
            break;
        case CommandId::SERVICE_NEW_GAME_OK:
            cmd = std::make_unique<SrvNewGameOkCmd>();
            break;
        case SERVICE_POSSIBLE_MOVES:
            cmd = std::make_unique<SrvPossibleMovesCmd>();
            break;
        case SERVICE_MOVE_RESULT:
            cmd = std::make_unique<SrvMoveResultCmd>();
            break;
        default:
            break;
    }

    return cmd;
}
