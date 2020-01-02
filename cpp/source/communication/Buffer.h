#ifndef BUFFER_H
#define BUFFER_H

#include <QByteArray>
#include <memory>
#include <vector>

class Buffer
{
public:
    explicit Buffer(const size_t size);

    char* write();
    char* read();

    int size() const;

    void fromByteArr(const QByteArray& arr);
    QByteArray toByteArr();

    std::uint8_t cmdType() const;

private:
    std::vector<char> bytes_;
    std::size_t size_;
};

#endif // BUFFER_H
