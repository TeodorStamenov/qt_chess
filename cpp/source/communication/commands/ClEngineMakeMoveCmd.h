#pragma once

#include "communication/commands/CommandImpl.h"

class ClEngineMakeMoveCmd final : public CommandImpl<ClEngineMakeMoveCmd>
{
public:
    ClEngineMakeMoveCmd();

    void init(const std::string& move);
};
