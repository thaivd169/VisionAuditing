#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <opencv2/core/mat.hpp>

#include "domain/value_objects/track.h"

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

    public slots:
     void newMainFrame(const cv::Mat& frame);
     void imageWorkerDone(const QList<Track>& tracks);

   private:
    Ui::MainWindow* ui;
    QList<Track> dects_;
    void displayFrame(cv::Mat& frame);
    void drawOsd(cv::Mat& frame);
};
#endif  // MAINWINDOW_H
