#include "videocapturer.h"

#include <QDebug>
#include <QObject>

VideoCapturer::VideoCapturer(const QString &path, uint fps, QObject *parent) {
    setPath(path);
    readingTimer = new QTimer(this);
    readingTimer->setInterval(1000 / fps);
}

VideoCapturer::~VideoCapturer() {
    stopCapture();
}

void VideoCapturer::setPath(const QString &path) {
    m_path = path;
}

void VideoCapturer::startCapture() {
    if (cap.isOpened()) {
        stopCapture();
    }
    // set `output-corrupt=false` cho avdec_h265` nếu muốn đọc barcode/OCR khó, chữ cực nhỏ`
    if (cap.open(QString("rtspsrc location=%1 latency=200 ! "
                         "rtph265depay ! h265parse ! "
                         "queue max-size-buffers=1 leaky=downstream ! avdec_h265 output-corrupt=false ! videoconvert ! "
                         "appsink drop=true sync=false")
                     .arg(m_path)
                     .toUtf8()
                     .constData(),
                 cv::CAP_GSTREAMER)) {
        isFrameReadable = true;
        connect(readingTimer, &QTimer::timeout, this, &VideoCapturer::readFrame);
        readingTimer->start();
        qDebug() << "Open rtsp stream by Gstreamer";
    } else if (!m_path.contains("rtsp:") && cap.open(m_path.toUtf8().constData())) {
        isFrameReadable = true;
        connect(readingTimer, &QTimer::timeout, this, &VideoCapturer::readFrame);
        qDebug() << "Open rtsp stream by the default";
    } else {
        isFrameReadable = false;
        qDebug() << "Open rtsp stream failed";
    }
}

void VideoCapturer::stopCapture() {
    isFrameReadable = false;
    disconnect(readingTimer, &QTimer::timeout, this, &VideoCapturer::readFrame);
    if (cap.isOpened()) {
        cap.release();
    }
}

void VideoCapturer::readFrame() {
    cv::Mat frame;
    if (isFrameReadable && cap.read(frame)) {
        emit newFrame(frame);
    } else {
        stopCapture();
    }
}
