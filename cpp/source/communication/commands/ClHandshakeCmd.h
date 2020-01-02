#pragma once

#include "communication/commands/CommandImpl.h"

class ClHandshakeCmd final : public CommandImpl<ClHandshakeCmd>
{
public:
    ClHandshakeCmd();
};
