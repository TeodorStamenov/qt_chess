#ifndef COMMANDCREATOR_H
#define COMMANDCREATOR_H

#include "communication/commands/CommandI.h"


class CommandCreator
{
public:
    CommandCreator();

    CommandPtr createCommand(const Buffer& buf);
};

#endif // COMMANDCREATOR_H
