#include "ConsoleLogger.hpp"
#include <QDateTime>
#include <string>

ConsoleLogger::ConsoleLogger(QTextEdit& consoleLog) : consoleLog{consoleLog}
{
}

void ConsoleLogger::log(std::string message)
{
    const QString timestamp =QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    consoleLog.append(QString("[%1] %2").arg(timestamp, QString::fromStdString(message)));
}