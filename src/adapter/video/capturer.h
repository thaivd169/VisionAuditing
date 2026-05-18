#ifndef ADAPTER_VIDEO_VIDEOCAPTURER_H
#define ADAPTER_VIDEO_VIDEOCAPTURER_H

#include <QThread>
#include <QTimer>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#define DEFAULT_FPS 25

class VideoCapturer : public QObject {
    Q_OBJECT
   public:
    VideoCapturer(const QString& path, uint fps = DEFAULT_FPS, QObject* parent = nullptr);
    ~VideoCapturer() override;

   signals:
    void newFrame(const cv::Mat& frame);

   public slots:
    void startCapture();
    void stopCapture();
    void setPath(const QString& path);

   private slots:
    void readFrame();

   private:
    QTimer* readingTimer = nullptr;
    cv::VideoCapture cap;
    QString m_path;
    bool isFrameReadable = false;
};

#endif  // ADAPTER_VIDEO_VIDEOCAPTURER_H
