#ifndef FRAMESAVER_H
#define FRAMESAVER_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "datatypes.h"
//#include "captureframehelper.h"
//#include "qmotiondetectorwrapper.h"
#include "debug.h"
/**
Сохранятель кадров - сохраняет кадры движения, если движения нет в течение timeout
значит пул кадров сбрасываеться сигналом void SaveComplete(const FrameList& frames);
**/
#include <QMutex>
class FrameSaver : public QObject
{
    Q_OBJECT
public:

    explicit FrameSaver(/*const CaptureFrameHelper *cap*/const int timeout);
    ~FrameSaver();
   // FrameList GetFrames() const;
    //время сохранения
    void Save();
    //добавить кадр вручную
    void PushFrame(const cv::Mat &frame);
    //void Start(){start();}
private slots:
    void MotionDetected(const RectList rects,const cv::Mat frame);
    void Timeout();
signals:
    void SaveComplete(const FrameList& frames);
    void SaveStart();
private:
    FrameList m_frames;
    QTimer m_timer;
    bool m_save_start;
    const int m_timeout;
    QMutex m_mutex;
protected:
    /*void run(){
        while(true){
            Debug("saver!");
        }
    }*/
};

#endif // FRAMESAVER_H
