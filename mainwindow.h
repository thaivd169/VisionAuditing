#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "adapter/imageworker/imageworker.h"
#include "adapter/videocapturer/videocapturer.h"
#include "domain/barcode/dto.h"
#include "domain/mot/dto.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

   signals:
    void startCapture();
    void stopCapture();

   private slots:
    void newMainFrame(const cv::Mat& frame);
    void imageWorkerDone(const QList<TrackDto>& tracks);
    void onBarcodeDetected(const QList<BarcodeDto>& barcodes);

   private:
    Ui::MainWindow* ui;
    VideoCapturer* _videoCapturer;
    ImageWorker* _imageWorker;
    QThread _captureThread;
    QThread _imageProcessThread;

    QList<TrackDto> _dects;
    QList<BarcodeDto> _barcodes;

    void initVideoCapturer(const QString& url);
    void initImageWorker();

    void startThreads();
    void displayFrame(cv::Mat& frame);
    void drawOsd(cv::Mat& frame);
};
#endif  // MAINWINDOW_H
