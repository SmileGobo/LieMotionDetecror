#ifndef QMOTIONDETECTORWRAPPER_H
#define QMOTIONDETECTORWRAPPER_H

#include <QObject>
#include "v_motion_detector.h"
#include <QVector>
#include <QDateTime>

typedef QVector<cv::Rect> RectList;
//class DetectionInfo;
/**
Класс обертка над классом детектором движения
Слот для обработки входных кадров void DetectingMotion(const cv::Mat& n_frame);
Сигнал в случае регистрации события:
void Detected(const RectList rects,const cv::Mat& frame);
rects - список областей, frame - кадр фиксации

**/
class QMotionDetectorWrapper : public QObject
{
    Q_OBJECT
public:
    explicit QMotionDetectorWrapper(const cv::Size& img_size);
    ~QMotionDetectorWrapper();
public slots:
    void DetectingMotion(const cv::Mat& n_frame);
signals:
    void Detected(const RectList rects,const cv::Mat frame);
private:
    double CalcDiffTimestamp();

    VMotionDetector m_detector;
    QDateTime m_start_time;

    static const double CYCLE_TIME;
   // static const double US_PER_S;
   // static const double MS_PER_S;
};

#endif // QMOTIONDETECTORWRAPPER_H
