#include "captureframehelper.h"
#include <QMutexLocker>
#include "debug.h"
#include <QCoreApplication>


CaptureFrameHelper::CaptureFrameHelper(const QString& cap_name,QObject *parent) :
    QThread(parent),m_CAP_NAME(cap_name)
{
    m_flag_stop=false;
   // m_flag_new_frame=false;
    m_cap=NULL;
}
CaptureFrameHelper::~CaptureFrameHelper(){
    if (m_cap!=NULL)
    delete m_cap;
}

void CaptureFrameHelper::Init(){
    m_cap=new cv::VideoCapture(m_CAP_NAME.toStdString());
    if( ! m_cap->isOpened() ){
        std::string msg="can't open"+m_CAP_NAME.toStdString();
        throw Exception(msg);
    }

}
/*
cv::Mat CaptureFrameHelper::GetNextFrame(){
    //не отдавать данные
    //пока не обновиться кадр
    while(!m_flag_new_frame)
    m_flag_new_frame=false;
    QMutexLocker locker(&m_mutex);
    return m_cur_frame;
}*/
void CaptureFrameHelper::run(){
    int delay=1000/m_cap->get(CV_CAP_PROP_FPS);
    while(!m_flag_stop){

        //m_mutex.lock();
        //Debug("111\n");
        (*m_cap) >> m_cur_frame;
        //m_mutex.unlock();
        emit NextFrame(m_cur_frame);
       // qApp->processEvents();
        usleep(delay);

    }
}

void CaptureFrameHelper::Start(const qint32 wait_us){
    //QMutexLocker locker(&m_mutex);
    //Init();
    usleep(wait_us);
    m_flag_stop=false;
    start(QThread::NormalPriority);
}

void CaptureFrameHelper::Stop(const qint32 wait_us){
    //QMutexLocker locker(&m_mutex);
    usleep(wait_us);
    m_flag_stop=true;
}
cv::Size CaptureFrameHelper::GetFrameSize(){
    double width,height;
    width=m_cap->get(CV_CAP_PROP_FRAME_WIDTH);
    height=m_cap->get(CV_CAP_PROP_FRAME_HEIGHT);
    return cv::Size (width,height);
}

/*
cv::Mat  CaptureFrameHelper::GetFrame(){
    cv::Mat ret_val;
     (*m_cap) >> ret_val;
    return ret_val;
}*/
