#include "Buffer.h"

#include<iterator>

namespace
{
    const int CMD_TYPE_IN_BUFFER = 1;
}

Buffer::Buffer(const size_t size)
{
    size_ = size;
}

char* Buffer::write()
{
    bytes_.resize(size_);
    return bytes_.data();
}

char* Buffer::read()
{
    return bytes_.data();
}

int Buffer::size() const
{
    return static_cast<int>(size_);
}

std::uint8_t Buffer::cmdType() const
{
    return static_cast<std::uint8_t>(bytes_.at(CMD_TYPE_IN_BUFFER));
}

void Buffer::fromByteArr(const QByteArray &arr)
{
    bytes_.clear();
    std::move(arr.begin(), arr.end(), std::back_inserter(bytes_));
}

QByteArray Buffer::toByteArr()
{
    QByteArray arr(bytes_.data(), static_cast<int>(bytes_.size()));
    return arr;
}
