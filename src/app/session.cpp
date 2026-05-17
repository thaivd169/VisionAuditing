#include "session.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaObject>

#include "utilities/logger.h"

Session::Session(QObject* parent)
    : QObject(parent),
{
}

Session::~Session() {
}
