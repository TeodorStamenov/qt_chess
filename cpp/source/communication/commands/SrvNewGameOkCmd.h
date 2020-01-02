#pragma once

#include "communication/commands/CommandImpl.h"

class SrvNewGameOkCmd : public CommandImpl<SrvNewGameOkCmd>
{
public:
    SrvNewGameOkCmd();

    virtual void handle(CommandHandlerI& handler) override;
};
