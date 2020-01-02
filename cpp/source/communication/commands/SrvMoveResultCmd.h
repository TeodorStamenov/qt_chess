#pragma once

#include "communication/commands/CommandImpl.h"

class SrvMoveResultCmd : public CommandImpl<SrvMoveResultCmd>
{
public:
    SrvMoveResultCmd();

    virtual void handle(CommandHandlerI& handler) override;
};
