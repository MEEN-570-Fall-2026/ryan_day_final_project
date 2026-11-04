#ifndef CONSOLELOGGER
#define CONSOLELOGGER

#include <QPlainTextEdit>
#include <QString>


class ConsoleLogger {
    public:
        ConsoleLogger(QPlainTextEdit& consoleLog);

    private:
        QPlainTextEdit& consoleLog;
};

#endif