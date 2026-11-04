#ifndef CONSOLELOGGER
#define CONSOLELOGGER

#include <QTextEdit>
#include <QString>
#include <string>


class ConsoleLogger {
    public:
        ConsoleLogger(QTextEdit& consoleLog);
        void log(std::string message);

    private:
        QTextEdit& consoleLog;
};

#endif