#pragma once

#include "communication/commands/CommandImpl.h"

class ClNewGameCmd : public CommandImpl<ClNewGameCmd>
{
public:
    ClNewGameCmd();

    void setFen(const std::string& fen);
};
