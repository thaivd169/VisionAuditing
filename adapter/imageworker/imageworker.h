#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

#include <QObject>
#include <QPointer>
#include "domain/detection/dto.h"
#include "adapter/detection/objectdetector.h"

class ImageWorker : public QObject
{
    Q_OBJECT
public:
    explicit ImageWorker(QObject *parent = nullptr);
    ImageWorker(const ImageWorker& imageWorkder) = delete;
    ImageWorker& operator=(const ImageWorker&) = delete;

    ~ImageWorker();

signals:
    void done(const QList<DetectionDto>& dects);

public slots:
    void startSession();
    void fetchSession(const cv::Mat& frame);
    void stopSession();

private:
    QList<DetectionDto> dects;
    ObjectDetector* detector;
};

#endif // IMAGEWORKER_H
