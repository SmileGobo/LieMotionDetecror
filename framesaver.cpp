#include "framesaver.h"
#include "debug.h"

#include <QMutexLocker>
#include <QCoreApplication>
FrameSaver::FrameSaver(/*const CaptureFrameHelper* cap*/const int timeout):
        QObject(0),m_timer(),m_save_start(false),m_timeout(timeout){
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(Timeout()));
     m_timer.start(m_timeout);
    //connect(cap,SIGNAL(NextFrame(cv::Mat)),this,SLOT(SaveFrame(cv::Mat)));
}
/*
void FrameSaver::SaveFrame(const cv::Mat &frame){
    if(m_save_start){
       PushFrame(frame);
    }
}*/
//кто хотел тот получил
void FrameSaver::Timeout(){
    //qApp->processEvents();
    QMutexLocker locker(&m_mutex);
    if (m_save_start){
        emit SaveComplete(m_frames);
        //---debug--//
        //std::cout<<m_frames.size()<<std::endl;
        Debug("Timeout!");
        m_frames.clear();
        m_save_start=false;
        Debug("------SaveFrame Stoped");
    }
    Debug("timer");
}
/*
FrameList FrameSaver::GetFrames() const{
    return m_frames;
}*/
FrameSaver::~FrameSaver(){}

void FrameSaver::MotionDetected(const RectList rects,const cv::Mat frame){
    QMutexLocker locker(&m_mutex);
    //m_mutex.lock();;
    if(!m_save_start){
        m_save_start=true;
        emit SaveStart();
        Debug("------SaveFrame Started");
    }
    //m_mutex.unlock();
    Debug("Motion detected! Frame Saver");
   // ProcessImg(frame);
    PushFrame(frame);
    //m_timer.stop();
}

/*
void FrameSaver::StopSave(){
    m_save_start=false;
    emit SaveComplete(m_frames);
}
*/
void FrameSaver::PushFrame(const cv::Mat &frame){
    m_frames.push_back(frame.clone());
}
