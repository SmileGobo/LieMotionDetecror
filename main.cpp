
#include <opencv2/imgproc/imgproc.hpp>

//#include <boost/date_time/posix_time/posix_time.hpp>

#include "v_motion_detector.h"
#include <iostream>

#include <QtCore/QCoreApplication>
#include <QDateTime>

#include "qmotiondetectorwrapper.h"
#include "frameview.h"
#include "motionlogger.h"
#include "debug.h"


#include "datatypes.h"
const int ARG_SIZE=2;



int main(int argc, char *argv[]){


/*
    if (argc!=ARG_SIZE){
        return -1;
    }   */
    QCoreApplication a(argc, argv);
    qRegisterMetaType<cv::Mat>();
    qRegisterMetaType<cv::Rect>();

    RegistryCapture *reg=RegistryCapture::GetInstance();
/** 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
захват видео можно осуществить с помощью pipe
mkfifo <имя канала> в данном случае cap_file
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! **/
    const QString FILE_NAME("./cap_file");
    CaptureFrameHelper cap_frame(FILE_NAME);
    cap_frame.Init();

    const QString CAM_NAME_ALIAS("cap1");
    reg->RegElem(&cap_frame,CAM_NAME_ALIAS);
    //cv::Size size=cap_frame.GetFrameSize();
    QMotionDetectorWrapper motion_detector(cap_frame.GetFrameSize());

    const QString DB_NAME("./data/log");
    const QString TABLE_NAME("motionview");
    MotionLogger logger(DB_NAME,TABLE_NAME);
    logger.Init();
   // std::cout<<"width:"<<size.width<<" height:"<<size.height<<std::endl;
    const int SAVE_TIMEOUT=2000;
    //FrameView view("captured!");
    FrameSaver frame_save(SAVE_TIMEOUT);

    const QString BASE_DIR_PATH("./data");
    FrameDirWriter writer(BASE_DIR_PATH);


//---------------------увязываем объекты--------------//
   // QObject::connect(&cap_frame,SIGNAL(NextFrame(cv::Mat)),&view,SLOT(RefreshFrame(cv::Mat)));

    //связываем источник кадров CaptureFrameHelper
    //с QMotionDetectorWrapper детектором движений
    //новые кадры
    QObject::connect(&cap_frame,SIGNAL(NextFrame(cv::Mat)),&motion_detector,SLOT(DetectingMotion(cv::Mat)),Qt::DirectConnection);

    //связываем детектор движения QMotionDetectorWrapper
    //c отображением
    //отладочное
    //QObject::connect(&motion_detector,SIGNAL(Detected(RectList,cv::Mat)),&view,SLOT(DrawMotion(RectList,cv::Mat)));

    //связываем детектор движения QMotionDetectorWrapper
    //с контейнером "сохранятель" кадров FrameSaver
    qRegisterMetaType<RectList>("RectList");
    QObject::connect(&motion_detector,SIGNAL(Detected(RectList,cv::Mat)),&frame_save,SLOT(MotionDetected(RectList,cv::Mat)));

    //связываем контейнер "сохранятель" кадров FrameSaver
    //с "записывателем" в заданную дирректорию FrameDirWriter
    QObject::connect(&frame_save,SIGNAL(SaveComplete(FrameList)),&writer,SLOT(Write(FrameList)));


    //связываем сохранятель FrameSaver c MotionLogger для первичной регистрации данных
    QObject::connect(&frame_save,SIGNAL(SaveStart()),&logger,SLOT(RegisterMotion()));
    QObject::connect(&writer,SIGNAL(WriteComplete(const QString&)),&logger,SLOT(Log(const QString&)));
    //начинаем работу
    cap_frame.Start();
    //frame_save.Start();
    //std::cout<<<<sdt::endl;
    Debug("that's all!");
    return a.exec();
}

/*
 *  Copyright (c) 2011 Dmitry Suvorov <D.Suvorov90@gmail.com>
 * базовый алгоритм
 */
/*

using namespace std;
static const double CYCLE_TIME = 0.02;

static const double US_PER_S=1000000.0;
static const double MS_PER_S=1000.0;

#include "debug.h"

int main( int argc, char **argv ){

    if (argc!=2){
        std::cout<<"Ошибка: мало аргументов"<<std::endl;
        return -1;
    }
   // Debug("1");
    cv::VideoCapture cap(  argv[1] );
    if( ! cap.isOpened() ){
        Debug("not captured");
        return -1;
    }
    //Debug("2");
    cv::Mat tmp_frame,gray_frame, out_frame;
    cap >> tmp_frame;

    VMotionDetector motionDetector( tmp_frame.size(), CYCLE_TIME );

    std::vector<cv::Rect> targets;
    std::vector<cv::Rect>::iterator it, endIt;

    cv::namedWindow("segmented");
    cv::namedWindow("frame");

    boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::universal_time( );
    boost::posix_time::ptime previousTime, time = startTime;
    int delay=1000/cap.get(CV_CAP_PROP_FPS);

    unsigned int frame_count=0;
    do {
        previousTime = time;
        cap >> tmp_frame;
        if (tmp_frame.empty()){
            break;
        }
        cv::cvtColor( tmp_frame, gray_frame, CV_BGR2GRAY );
        //Debug("1");
        time = boost::posix_time::microsec_clock::universal_time( );
        motionDetector.detectMovingRegions(
            gray_frame,
            ( time - startTime ).total_microseconds( ) / US_PER_S,
            targets,
            out_frame
        );
        //Debug("2");
        endIt = targets.end();
        std::cout<<"frame:"<<(frame_count++)<<"size region:"<<targets.size()<<std::endl;
        for( it = targets.begin(); it != endIt; ++it )
            cv::rectangle(tmp_frame, *it, cv::Scalar( 255, 255, 0 ) );
        Debug("3");
        cv::imshow( "segmented", out_frame );
        cv::imshow( "frame",tmp_frame );
        //Debug("4");
        time = boost::posix_time::microsec_clock::universal_time( );
        //delay = int( MS_PER_S * CYCLE_TIME - ( time - previousTime ).total_milliseconds( ) );
           // Debug("5");
    }
    while( cv::waitKey( delay) < 0 );

    return 0;
}
*/
