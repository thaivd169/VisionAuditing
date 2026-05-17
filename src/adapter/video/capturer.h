#ifndef ADAPTER_CVVIDEOCAPTURER_H
#define ADAPTER_CVVIDEOCAPTURER_H

#include <QThread>
#include <QTimer>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"


#define DEFAULT_FPS 25

class VideoCapturer : public QObject {
    Q_OBJECT
public:
    VideoCapturer(const QString &path, uint fps = DEFAULT_FPS, QObject *parent = nullptr);
    ~VideoCapturer() override;

    QTimer *readingTimer = nullptr;

signals:
    void newFrame(const cv::Mat& frame);

public slots:
    void startCapture();
    void stopCapture();
    void setPath(const QString &path);

private:
    cv::VideoCapture cap;
    QString m_path;
    bool isFrameReadable = false;

private slots:
    void readFrame();
};

#endif  // CVVIDEOCAPTURE_H
