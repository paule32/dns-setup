#ifndef UTILS_H_
#define UTILS_H_

#include <QObject>
#include <QString>
#include <QUrl>


// Workaround: As of Qt 5.4 QtQuick does not expose QUrl::fromUserInput.
class Utils : public QObject {
    Q_OBJECT
public:
    Utils(QObject* parent = 0) : QObject(parent) { }
    static QUrl fromUserInput(const QString& userInput);
};

#endif
