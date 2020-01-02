#pragma once

#include <memory>

class CommandHandlerI;
class Buffer;
class QString;

class CommandI
{
public:
    virtual ~CommandI() = default;

    virtual void serialize(Buffer& buf) const = 0;
    virtual void deserialize(Buffer& buf) = 0;

    virtual void handle(CommandHandlerI& handler) = 0;

    virtual size_t getSize() const = 0;

    virtual const QString name() const = 0;
};

using CommandPtr = std::unique_ptr<CommandI>;
