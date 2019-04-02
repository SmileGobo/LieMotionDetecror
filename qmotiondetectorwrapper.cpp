#include "qmotiondetectorwrapper.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "debug.h"
const double QMotionDetectorWrapper::CYCLE_TIME = 0.02;

//const double QMotionDetectorWrapper::US_PER_S=1000000.0;
//const double QMotionDetectorWrapper::MS_PER_S=1000.0;
QMotionDetectorWrapper::QMotionDetectorWrapper(const cv::Size& img_size):
    m_detector(img_size,CYCLE_TIME),
    m_start_time(QDateTime::currentDateTime()){

}


QMotionDetectorWrapper::~QMotionDetectorWrapper(){

}

void QMotionDetectorWrapper::DetectingMotion(const cv::Mat &n_frame){
    cv::Mat gray_frame,out_frame;
    cv::cvtColor( n_frame, gray_frame, CV_BGR2GRAY );
    std::vector<cv::Rect> targets;
    //Debug(QString::number(CalcDiffTimestamp()).toStdString());
    m_detector.detectMovingRegions(gray_frame,CalcDiffTimestamp(),targets,out_frame);

    if(!targets.empty()){
       // Debug(QString::number(targets.size()).toStdString());
        RectList result_targets;
        //result_targets.fromStdVector(targets);
        for(int i=0;i<targets.size();i++){
            result_targets.push_back(targets[i]);
        }
        emit Detected(result_targets,n_frame);

    }
}

double QMotionDetectorWrapper::CalcDiffTimestamp(){
    //QTime current=QTime::currentTime();
    const double US_PER_S=100000.0;
    return (QDateTime::currentDateTime().toTime_t()-m_start_time.toTime_t()/US_PER_S);
}
