#include "ConsoleLogger.hpp"
#include <QDateTime>
#include <string>

ConsoleLogger::ConsoleLogger(QTextEdit& consoleLog) : consoleLog{consoleLog}
{
}

void ConsoleLogger::log(std::string message)
{
    QString timestampMessage = add_timestamp_to_message(QString::fromStdString(message));
    consoleLog.append(timestampMessage);
}

void ConsoleLogger::logError(const std::exception& e)
{
    std::string message = std::format("ERROR: {}", e.what());
    QString timestampMessage = add_timestamp_to_message(QString::fromStdString(message));
    QString line = timestampMessage.toHtmlEscaped();
    consoleLog.append("<span style='color: red;'>" + line + "</span>"); 
}

QString ConsoleLogger::add_timestamp_to_message(QString message)
{
    const QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    return QString("[%1] %2").arg(timestamp, message);
}
