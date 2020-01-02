#pragma once

#include "communication/commands/CommandImpl.h"

class ClMakeMoveCmd final : public CommandImpl<ClMakeMoveCmd>
{
public:
    ClMakeMoveCmd();

    void init(int fromIndex, int toIndex);
};
