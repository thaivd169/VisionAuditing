#include "mainwindow.h"
#include <QImage>
#include "./ui_mainwindow.h"
#include "opencv2/opencv.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _videoCapturer(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    captureFromStream("rtsp://thaivd:vuducthai169@10.0.80.252:554/Streaming/Channels/101");
    startThreads();
    emit startCapture();
}

MainWindow::~MainWindow()
{
    _captureThread.wait();
    _captureThread.quit();
    delete ui;
}

void MainWindow::captureFromStream(const QString &url) {
    _videoCapturer = new VideoCapturer(url);
    _videoCapturer->moveToThread(&_captureThread);
    connect(&_captureThread, &QThread::finished, _videoCapturer, &VideoCapturer::deleteLater);
    connect(this, &MainWindow::startCapture, _videoCapturer, &VideoCapturer::startCapture);
    connect(this, &MainWindow::stopCapture, _videoCapturer, &VideoCapturer::stopCapture);
    connect(_videoCapturer, &VideoCapturer::newFrame, this, &MainWindow::newMainFrame);
}

void MainWindow::startThreads() {
    // Start Threads
    _captureThread.start();
}

void MainWindow::newMainFrame(const cv::Mat& mainFrame) {
    cv::Mat mainStreamFrame = mainFrame.clone();
    displayFrame(mainStreamFrame);
}

QImage convertMat2QImage(const cv::Mat &inMat) {
    switch (inMat.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_ARGB32);

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3: {
        QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888);

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1: {
        static QVector<QRgb> sColorTable;

        // only create our color table once
        if (sColorTable.isEmpty()) {
            for (int i = 0; i < 256; ++i)
                sColorTable.push_back(qRgb(i, i, i));
        }

        QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8);

        image.setColorTable(sColorTable);

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

void MainWindow::displayFrame(cv::Mat& frame) {
    const int defaultFrameWidth = 1366;
    const int defaultFrameHeight = 768;
    cv::resize(frame, frame, cv::Size(defaultFrameWidth, defaultFrameHeight));
    ui->lblVideoStream->setFixedSize(defaultFrameWidth, defaultFrameHeight);
    QImage image = convertMat2QImage(frame);
    ui->lblVideoStream->setPixmap(QPixmap::fromImage(image));
    ui->lblVideoStream->adjustSize();
}
