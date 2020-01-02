#include "ClEngineMakeMoveCmd.h"

ClEngineMakeMoveCmd::ClEngineMakeMoveCmd()
    : CommandImpl(CommandId::CLIENT_ENGINE_MAKE_MOVE)
{
}

void ClEngineMakeMoveCmd::init(const std::string& move)
{
    command_.set_move(move);
}
