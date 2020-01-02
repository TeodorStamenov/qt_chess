#include "ClMakeMoveCmd.h"

ClMakeMoveCmd::ClMakeMoveCmd()
    : CommandImpl(CommandId::CLIENT_MAKE_MOVE)
{
}

void ClMakeMoveCmd::init(int fromIndex, int toIndex)
{
    command_.set_fromindex(fromIndex);
    command_.set_toindex(toIndex);
}
