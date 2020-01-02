#include "Logger.h"
#include <QtDebug>
#include <QDir>
#include <QDateTime>
#include <utility>

#include <iostream>

namespace
{
    const QString FILE_EXT = ".log";
    const QString DATE_FMT = "ddd MMMM d yy";
    const QString SEPARATOR = ": ";
    const QString NEW_LINE = "\n";

    QString getCurrentTime()
    {
        QDateTime time = QDateTime::currentDateTime();
        return time.toString().replace(':','-');
    }

    QByteArray formatMsg(const QString& msg)
    {
        QString line;
        line.append(getCurrentTime());
        line.append(SEPARATOR);
        line.append(msg);
        line.append(NEW_LINE);
        return line.toUtf8();
    }
}

Logger::Logger()
{
    QDir dir;
    cwd = getCurrentTime();
    dir.mkdir(cwd);
}

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::log(const QString& fileName, const QString& msg)
{
    QFile file(cwd + "\\" + fileName + FILE_EXT);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        file.write(formatMsg(msg));
        file.close();
    } else {
        qDebug() << "can not open the file: " << file.fileName();
    }
}

