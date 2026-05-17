#include "circlesplash.h"

#include <QColor>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QString>
#include <QTimer>

#include "ui_circlesplash.h"

CircleSplash::CircleSplash(QWidget *parent)
    : QMainWindow(parent),
      _ui(new Ui::CircleSplash),
      _shadow(new QGraphicsDropShadowEffect(this)),
      _totalPercent(0) {
    _ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);     // Remove title bar
    setAttribute(Qt::WA_TranslucentBackground);  // Set background to transparent
    _shadow->setBlurRadius(20);
    _shadow->setXOffset(0);
    _shadow->setYOffset(0);
    _shadow->setColor(QColor(0, 0, 0, 100));
    _ui->fBackground->setGraphicsEffect(_shadow);
    setPercent(_totalPercent);
}

CircleSplash::~CircleSplash() {
    if (_shadow) delete _shadow;
    if (_ui) delete _ui;
}

void CircleSplash::setPercent(const float &p) {
    const float percent = p < 0.0f ? 0.0f : (p > 100.0f ? 100.0f : p);
    const QString styleSheet = R"###(
        QFrame {
            border-radius: 150px; 
            background-color: qconicalgradient(cx:0.5, cy:0.5, angle:90,
            stop:%1 rgba(98, 160, 234, 0),
            stop:%2 rgba(145, 65, 172, 255));
        })###";
    const float plainStop = (100.0f - percent) / 100.0f;
    const float blurFactor = 0.08f;
    float blurStop;
    if (plainStop == 0.0f) {
        blurStop = plainStop;
    } else {
        blurStop = plainStop - blurFactor;
    }
    if (_ui) {
        _ui->fProgress->setStyleSheet(
            styleSheet.arg(QString::number(blurStop), QString::number(plainStop)));
    }
}

void CircleSplash::setMessage(const QString &message) {
    if (_ui) {
        _ui->lblMessage->setText(message);
    }
}

void CircleSplash::appendJobInfo(const JobInfo &jobInfo) {
    _jobAndPerVec.push_back(jobInfo);
}

void CircleSplash::finish() {
    close();
}

void CircleSplash::showEvent(QShowEvent *event) {
    // Chờ 1s để màn hình splash hoàn toàn hiển thị
    QTimer::singleShot(1000, [this]() {
        process();
    });
}

void CircleSplash::process() {
    for (auto &jobAndPer : _jobAndPerVec) {
        if (jobAndPer.job) {
            setMessage(jobAndPer.message);
            jobAndPer.job();
            jobAndPer.job = nullptr;
            _totalPercent += jobAndPer.percent;
            setPercent(_totalPercent);
        } else {
            continue;
        }
    }
}

CircleSplash::JobInfo::JobInfo(const Job &job, const float &percent, const QString &message)
    : job(job), percent(percent), message(message) {
}
