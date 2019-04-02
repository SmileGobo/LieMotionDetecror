#ifndef CAPTUREFRAMEHELPER_H
#define CAPTUREFRAMEHELPER_H

#include <QThread>
#include <QVector>
#include <QString>
#include <QMutex>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//typedef QVector<cv::Mat> FrameList;
/***
Класс для захвата новых кадров согласно фрейм рейту (кадры в секунду)
Генерирует сигнал по приходу кадра void NextFrame(const cv::Mat &new_frame);
***/
#include "exception.h"

class CaptureFrameHelper : public QThread
{
Q_OBJECT
public:
    explicit CaptureFrameHelper(const QString &cap_name,QObject *parent = 0);
    ~CaptureFrameHelper();
    //потребует добавления сиснхронизации
    //cv::Mat GetFrame();
    cv::Size GetFrameSize();
    void Init();

signals:
    void NextFrame(const cv::Mat &new_frame);
protected:
    void run();
public slots:
    void Start(const qint32 wait_us=0);
    void Stop(const qint32 wait_us=0);

private slots:

private:
    cv::VideoCapture *m_cap;
    //FrameList m_frame_list;
    cv::Mat m_cur_frame;

    const QString m_CAP_NAME;
    //mutable QMutex m_mutex;
    //volatile bool m_flag_new_frame;
    volatile bool m_flag_stop;
};

#endif // CAPTUREFRAMEHELPER_H
