#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "adapter/videocapturer/videocapturer.h"

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

private:
    Ui::MainWindow *ui;
    VideoCapturer *_videoCapturer;
    QThread _captureThread;      // Receive image input from VEE device

    void captureFromStream(const QString &url);
    void startThreads();
    void displayFrame(cv::Mat &frame);
};
#endif // MAINWINDOW_H
