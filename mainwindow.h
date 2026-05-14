#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "adapter/videocapturer/videocapturer.h"
#include "adapter/imageworker/imageworker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void startCapture();
    void stopCapture();

private slots:
    void newMainFrame(const cv::Mat& frame);
    void imageWorkerDone(const QList<DetectionDto>& dects);

private:
    Ui::MainWindow *ui;
    VideoCapturer *_videoCapturer;
    ImageWorker* _imageWorker;
    QThread _captureThread;
    QThread _imageProcessThread;

    QList<DetectionDto> _dects;

    void initVideoCapturer(const QString &url);
    void initImageWorker();

    void startThreads();
    void displayFrame(cv::Mat &frame);
    void drawOsd(cv::Mat &frame);
};
#endif // MAINWINDOW_H
