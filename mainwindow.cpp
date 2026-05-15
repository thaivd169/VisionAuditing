#include "mainwindow.h"

#include <QImage>
#include <algorithm>

#include "./ui_mainwindow.h"
#include "opencv2/opencv.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      _videoCapturer(nullptr),
      _imageWorker(nullptr),
      ui(new Ui::MainWindow) {
    ui->setupUi(this);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<BarcodeDto>();
    qRegisterMetaType<QList<BarcodeDto>>();
    initVideoCapturer("rtsp://thaivd:vuducthai169@10.0.80.252:554/Streaming/Channels/101");
    initImageWorker();

    startThreads();

    emit startCapture();
}

MainWindow::~MainWindow() {
    _captureThread.wait();
    _captureThread.quit();

    _imageProcessThread.wait();
    _imageProcessThread.quit();

    delete ui;
}

void MainWindow::initVideoCapturer(const QString& url) {
    _videoCapturer = new VideoCapturer(url);
    _videoCapturer->moveToThread(&_captureThread);
    connect(&_captureThread, &QThread::finished, _videoCapturer, &VideoCapturer::deleteLater);
    connect(this, &MainWindow::startCapture, _videoCapturer, &VideoCapturer::startCapture);
    connect(this, &MainWindow::stopCapture, _videoCapturer, &VideoCapturer::stopCapture);
    connect(_videoCapturer, &VideoCapturer::newFrame, this, &MainWindow::newMainFrame);
}

void MainWindow::initImageWorker() {
    _imageWorker = new ImageWorker();
    _imageWorker->moveToThread(&_imageProcessThread);
    connect(&_imageProcessThread, &QThread::finished, _imageWorker, &ImageWorker::deleteLater);
    connect(&_imageProcessThread, &QThread::finished, _imageWorker, &ImageWorker::stopSession);
    connect(&_imageProcessThread, &QThread::started, _imageWorker, &ImageWorker::startSession);
    connect(_videoCapturer, &VideoCapturer::newFrame, _imageWorker, &ImageWorker::fetchSession);
    connect(_imageWorker, &ImageWorker::done, this, &MainWindow::imageWorkerDone);
    connect(_imageWorker, &ImageWorker::barcodeDetected, this, &MainWindow::onBarcodeDetected);
}

void MainWindow::startThreads() {
    // Start Threads
    _captureThread.start();
    _imageProcessThread.start();
}

void MainWindow::newMainFrame(const cv::Mat& mainFrame) {
    cv::Mat mainStreamFrame = mainFrame.clone();
    drawOsd(mainStreamFrame);
    displayFrame(mainStreamFrame);
}

void MainWindow::imageWorkerDone(const QList<TrackDto>& tracks) {
    _dects = tracks;
}

void MainWindow::onBarcodeDetected(const QList<BarcodeDto>& barcodes) {
    for (const auto& incoming : barcodes) {
        auto it = std::find_if(_barcodes.begin(), _barcodes.end(),
                               [&](const BarcodeDto& b) { return b.getId() == incoming.getId(); });
        if (it != _barcodes.end())
            *it = incoming;
        else
            _barcodes.append(incoming);
    }
    QString info;
    for (const auto& bc : _barcodes) {
        info += QString("[%1] %2\n%3\n")
                    .arg(bc.getId())
                    .arg(QString::fromStdString(bc.getText()))
                    .arg(QString::fromStdString(bc.getType()));
    }
    ui->lblBarcodeInfo->setText(info.trimmed());
}

QImage convertMat2QImage(const cv::Mat& inMat) {
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

void MainWindow::drawOsd(cv::Mat& frame) {
    if (_dects.empty()) {
        return;
    }

    // Build id → barcode lookup
    auto findBarcode = [&](size_t id) -> const BarcodeDto* {
        for (const auto& bc : _barcodes) {
            if (bc.getId() == id) return &bc;
        }
        return nullptr;
    };

    for (const auto& dect : _dects) {
        const auto& xtl = dect.getBBox().getXtl();
        const auto& ytl = dect.getBBox().getYtl();
        const auto& width = dect.getBBox().getWidth();
        const auto& height = dect.getBBox().getHeight();
        const int thickness = 2;
        const int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        const double fontScale = 0.6;
        const int textThickness = 1;

        const BarcodeDto* bc = findBarcode(dect.getId());
        const cv::Scalar color = bc ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255);

        cv::rectangle(frame,
                      cv::Point(xtl, ytl),
                      cv::Point(xtl + width, ytl + height),
                      color, thickness, cv::LINE_AA);

        std::string trackLabel = "ID:" + std::to_string(dect.getId()) + " " +
                                 std::to_string(static_cast<int>(dect.getConfidenceScore() * 100)) + "%";

        int baseline = 0;
        cv::Size trackTextSize = cv::getTextSize(trackLabel, fontFace, fontScale, textThickness, &baseline);
        int textY = ytl - 5 > 0 ? static_cast<int>(ytl) - 5 : static_cast<int>(ytl) + trackTextSize.height + 5;

        if (bc) {
            std::string bcLabel = "[" + bc->getType() + "] " + bc->getText();
            cv::Size bcTextSize = cv::getTextSize(bcLabel, fontFace, fontScale, textThickness, &baseline);
            cv::putText(frame, bcLabel,
                        cv::Point(static_cast<int>(xtl), textY - trackTextSize.height - 4),
                        fontFace, fontScale, color, textThickness, cv::LINE_AA);
        }

        cv::putText(frame, trackLabel,
                    cv::Point(static_cast<int>(xtl), textY),
                    fontFace, fontScale, color, textThickness, cv::LINE_AA);
    }
}
