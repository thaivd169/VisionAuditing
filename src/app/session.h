#ifndef APP_SESSION_H
#define APP_SESSION_H

#include <QObject>
#include <QThread>
#include <memory>

#include "adapter/ui/mainwindow.h"
#include "adapter/video/capturer.h"
#include "adapter/video/worker.h"

class Session : public QObject {
    Q_OBJECT
   public:
    explicit Session(QObject* parent = nullptr);
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    ~Session();

   public slots:

   private:
    void startThreads();

   private:
    std::unique_ptr<VideoCapturer> videoCapturer_;
    std::unique_ptr<ImageWorker> imageWorker_;
    MainWindow* mainWindow_;
    QThread captureThread_;
    QThread workerThread_;
};

#endif