#ifndef MAIN_SESSION_H
#define MAIN_SESSION_H

#include <QObject>
#include <QThread>

class Session : public QObject {
    Q_OBJECT
   public:
    explicit Session(QObject* parent = nullptr);
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    ~Session();

   public slots:

   private:
};

#endif