#ifndef CONSOLELOGGER
#define CONSOLELOGGER

#include <QTextEdit>
#include <QString>
#include <string>


class ConsoleLogger {
    public:
        ConsoleLogger(QTextEdit& consoleLog);
        void log(std::string message);
        void logError(const std::exception& e);

    private:
        QString add_timestamp_to_message(QString message);

        QTextEdit& consoleLog;
};

#endif