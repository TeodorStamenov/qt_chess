#pragma once

#include "communication/commands/CommandImpl.h"

class SrvPossibleMovesCmd : public CommandImpl<SrvPossibleMovesCmd>
{
public:
    SrvPossibleMovesCmd();

    virtual void handle(CommandHandlerI& handler) override;
};
