#ifndef VIEWS_SPLASH_CIRCLESPLASH_H
#define VIEWS_SPLASH_CIRCLESPLASH_H

#include <QMainWindow>
#include <functional>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class CircleSplash;
}
QT_END_NAMESPACE

class QGraphicsDropShadowEffect;
class QString;
class CircleSplash : public QMainWindow {
    Q_OBJECT

   public:
    typedef std::function<void()> Job;
    struct JobInfo {
        QString message;
        Job job;
        float percent;
        explicit JobInfo(const Job &job, const float &percent, const QString &message);
    };

    CircleSplash(QWidget *parent = nullptr);
    ~CircleSplash();

    void appendJobInfo(const JobInfo &jobInfo);
    void finish();

   protected:
    void showEvent(QShowEvent *event) override;

   private:
    void setPercent(const float &percent);
    void setMessage(const QString &message);
    void process();

    uint _totalPercent;
    std::vector<JobInfo> _jobAndPerVec;
    Ui::CircleSplash *_ui;
    QGraphicsDropShadowEffect *_shadow;
};
#endif  // MAINWINDOW_H
