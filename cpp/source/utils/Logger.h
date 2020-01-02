#ifndef LOGGER_H
#define LOGGER_H

#include <QDir>

class Logger
{
public:
    static Logger& instance();

private:
    Logger();

public:
    void log(const QString& fileName, const QString& msg);

private:
    QString cwd;
};

#endif // LOGGER_H
