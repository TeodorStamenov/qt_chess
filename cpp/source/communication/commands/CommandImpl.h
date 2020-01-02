#pragma once

#include "communication/commands/CommandI.h"
#include "communication/commands/CommandIds.h"
#include "communication/commands/ProtoCommands.h"
#include "communication/Buffer.h"

#include <QString>


template<class BaseCommand>
class CommandImpl : public CommandI
{
    using ProtoCommand = typename Proto<BaseCommand>::ProtoCommandType;

public:
    virtual void handle(CommandHandlerI&) override {}

    CommandImpl(const CommandId id)
    {
        command_.set_id(id);
    }

    void serialize(Buffer& buf) const
    {
        command_.SerializeToArray(buf.write(), static_cast<int>(command_.ByteSizeLong()));
    }

    void deserialize(Buffer& buf)
    {
        command_.ParseFromArray(buf.read(), buf.size());
    }

    size_t getSize() const
    {
        return command_.ByteSizeLong();
    }

    const QString name() const
    {
        return QString::fromUtf8(command_.GetTypeName().c_str());
    }

protected:
    ProtoCommand command_;
};
