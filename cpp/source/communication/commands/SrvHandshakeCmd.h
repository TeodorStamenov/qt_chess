#pragma once

#include "communication/commands/CommandImpl.h"

class SrvHandshakeCmd final : public CommandImpl<SrvHandshakeCmd>
{
public:
    SrvHandshakeCmd();

    virtual void handle(CommandHandlerI& handler) override;
};
