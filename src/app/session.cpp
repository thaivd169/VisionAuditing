#include "session.h"

#include <QDebug>

#include "domain/services/idetector.h"
#include "domain/services/itracker.h"
#include "infra/detector/yolor.h"
#include "infra/mot/tracker.h"

Session::Session(QObject* parent)
    : QObject(parent),
      videoCapturer_(nullptr),
      imageWorker_(nullptr),
      mainWindow_(new MainWindow(nullptr)) {
    // Register custom type for signal-slot communication
    qRegisterMetaType<cv::Mat>("cv::Mat");

    // Initialize VideoCapturer
    videoCapturer_ = std::make_unique<VideoCapturer>("rtsp://thaivd:vuducthai169@10.0.30.252:554/Streaming/Channels/101");
    videoCapturer_->moveToThread(&captureThread_);
    connect(&captureThread_, &QThread::finished, videoCapturer_.get(), &VideoCapturer::deleteLater);
    connect(&captureThread_, &QThread::started, videoCapturer_.get(), &VideoCapturer::startCapture);
    connect(videoCapturer_.get(), &VideoCapturer::newFrame, mainWindow_, &MainWindow::newMainFrame);
    // Initialize ImageWorker
    std::unique_ptr<IDetector> detector = std::make_unique<Yolor>();
    std::unique_ptr<ITracker> tracker = std::make_unique<Tracker>();
    imageWorker_ = std::make_unique<ImageWorker>(std::move(detector), std::move(tracker));
    imageWorker_->moveToThread(&workerThread_);
    connect(&workerThread_, &QThread::finished, imageWorker_.get(), &ImageWorker::deleteLater);
    connect(videoCapturer_.get(), &VideoCapturer::newFrame, imageWorker_.get(), &ImageWorker::fetch);
    connect(imageWorker_.get(), &ImageWorker::done, mainWindow_, &MainWindow::imageWorkerDone);

    startThreads();
    mainWindow_->show();
}

void Session::startThreads() {
    captureThread_.start();
    workerThread_.start();
}

Session::~Session() {
    captureThread_.quit();
    captureThread_.wait();

    workerThread_.quit();
    workerThread_.wait();
}
